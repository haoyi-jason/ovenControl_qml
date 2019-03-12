#include "ovencontroller.h"
#include <QSerialPort>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QStandardItemModel>

ovenController::ovenController(QObject *parent) : QObject(parent)
  ,m_running(false)
  ,m_light(false)
  ,m_valve(false)
  ,m_fan(false)
{
    m_serialPort = new QSerialPort;

    m_serialPort->setPortName("COM17");
    m_serialPort->setBaudRate(9600);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);
    m_serialPort->open(QIODevice::ReadWrite);
    m_recepeModel = new QStandardItemModel(this);
    m_recepeModel->insertColumn(0);

    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&ovenController::pollController);
    connect(m_serialPort,&QSerialPort::readyRead,this,&ovenController::serialRead);
    initDatabase();
    loadParameter();
    m_remainSeconds = m_activeRecepe->bakeTime();

    m_timer->start(1000);
    m_remainTime = "20 MIN";
    m_finishTime = "15:30";

    m_ovenVar.m_maxTemp = 500;



//    qDebug()<<"recepeModel row count:"<<m_recepeModel->rowCount();
}

void ovenController::addRecepe(const int &id,const int& uhTemp, const int& lhTemp, const int& stTemp,
                               const int &baketime, const QString &name, const QString& imgurl,
                               const int &s1_time, const int &s1_qty,const int &s2_time, const int& s2_qty,
                               const int &v1_on, const int& v1_off, const int& v2_on, const int& v2_off)
{
    const int newRow = m_recepeModel->rowCount();
    qDebug()<<"addRecepe:"<<newRow;
    recepe r;
    r.setId(id);
    r.setUhTemp(uhTemp);
    r.setLhTemp(lhTemp);
    r.setBakeTime(baketime);
    r.setName(name);
    r.setImgurl(imgurl);

    r.setV1_on(v1_on);
    r.setV1_off(v1_off);
    r.setV2_on(v2_on);
    r.setV2_off(v2_off);
    r.setS1_time(s1_time);
    r.setS1_quantity(s1_qty);
    r.setS2_time(s2_time);
    r.setS2_quantity(s2_qty);
    m_recepeModel->insertRow(newRow);
    m_recepeModel->setData(m_recepeModel->index(newRow,0),QVariant::fromValue(r),Qt::EditRole);

    m_celius = true;
}

void ovenController::saveRecord(int id)
{
    const QString DRIVER("QSQLITE");
    QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
    db.setDatabaseName("./db/oven_db.db");
    if(!db.open()){
        qDebug()<<"Db open error:"<<db.lastError();
        return;
    }
    QSqlTableModel model;
    model.setTable("recepe");
    model.select();
    QSqlRecord r;
    if(id == -1){// new record
        model.insertRecord(-1,r);
    }else{
        r = model.record(id);
    }
    r.setValue("name",m_recepes.at(id)->name());
    r.setValue("oh_temp",m_recepes.at(id)->name());
    r.setValue("lh_temp",m_recepes.at(id)->name());
    r.setValue("bake_time_sec",m_recepes.at(id)->name());
    r.setValue("imgurl",m_recepes.at(id)->name());
    r.setValue("v1_on",m_recepes.at(id)->name());
    r.setValue("v2_on",m_recepes.at(id)->name());
    r.setValue("v1_off",m_recepes.at(id)->name());
    r.setValue("v2_off",m_recepes.at(id)->name());
    r.setValue("s1_time",m_recepes.at(id)->name());
    r.setValue("s2_time",m_recepes.at(id)->name());
    r.setValue("s1_quantity",m_recepes.at(id)->name());
    r.setValue("s2_quantity",m_recepes.at(id)->name());
}
void ovenController::initDatabase()
{
    const QString DRIVER("QSQLITE");
    if(QSqlDatabase::isDriverAvailable(DRIVER)){
        qDebug()<<"SQLITE exist!";
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
        db.setDatabaseName("./db/oven_db.db");
        if(!db.open()){
            qDebug()<<"Db open error:"<<db.lastError();
        }

        // list table
        QSqlQuery query("",db);
        QStringList ls = db.tables();
//        for(int i=0;i<ls.size();i++){
//            qDebug()<<"Table:"<<ls.at(i);
//        }

        // read recepe
        QSqlTableModel model;
        model.setTable("recepe");
        model.select();
        QSqlRecord r;
        query.prepare("SELECT * FROM recepe");
        query.exec();
        int i=1;
        while (query.next()) {
        //for(int i=0;i<model.)
            //qDebug()<<"Enter recepe";
            recepe *r = new recepe;
            r->setId(i++);
            r->setName(query.value("name").toString());
            r->setUhTemp(query.value("oh_temp").toInt());
            r->setLhTemp(query.value("lh_temp").toInt());
            r->setBakeTime(query.value("bake_time_sec").toInt());
            r->setImgurl(query.value("imgurl").toString());
            r->setV1_on(query.value("v1_on").toInt());
            r->setV2_on(query.value("v2_on").toInt());
            r->setV1_off(query.value("v1_off").toInt());
            r->setV2_off(query.value("v2_off").toInt());
            r->setS1_time(query.value("s1_time").toInt());
            r->setS2_time(query.value("s2_time").toInt());
            r->setS1_quantity(query.value("s1_quantity").toInt());
            r->setS2_quantity(query.value("s2_quantity").toInt());

            m_recepes.append(r);
            addRecepe(i,
                      query.value("oh_temp").toInt(),
                      query.value("lh_temp").toInt(),
                      250,
                      query.value("bake_time_sec").toInt(),
                      query.value("name").toString(),
                      query.value("imgurl").toString(),
                      query.value("v1_on").toInt(),
                      query.value("v1_off").toInt(),
                      query.value("v2_on").toInt(),
                      query.value("v2_off").toInt(),
                      query.value("s1_time").toInt(),
                      query.value("s1_quantity").toInt(),
                      query.value("s2_time").toInt(),
                      query.value("s2_quantity").toInt());
        }
        db.close();
    }
    m_currRecepeid = m_actRecepeid = 0;
    if(m_recepes.size() > 0){
        m_activeRecepe = currRecepe = m_recepes.at(0);
    }
    qDebug()<<"Nof Recepes in database:"<<m_recepes.size();
}
void ovenController::loadParameter()
{
//todo: load from config file
    for(int i=0;i<4;i++){
        m_heater[i].sp = 200;
    }

    for(int i=0;i<9;i++){
        m_relay[i].sp = 0;
    }

    for(int i=0;i<3;i++){
        m_fans[i].sp = 0;
    }
}

void ovenController::pollController()
{
//    //qDebug()<<"Oven Poll";
//    // test for relay command
//    QByteArray relay;
//    for(int i=0;i<9;i++)
//        relay.append((m_relay[i].sp==0)?0:1);

//    //qDebug()<<"Oven Poll:1";
    quint8 cmd = (quint8)(MASK_CMD | CMD1_SETUP);
    binPacket b(cmd,CMD2_SETUP_READTEMP);

    if(m_serialPort->isOpen()){
        //qDebug()<<"Send to com:";//<<b.packet();
        m_serialPort->write(b.packet());
    }

    //currRecepe->setUhTemp(currRecepe->uhTemp()+1);
    emit rtcChanged();
}

void ovenController::serialRead()
{
    if(m_serialPort && m_serialPort->bytesAvailable()>0){
        QByteArray recv = m_serialPort->readAll();
        m_data.append(recv);
        //parseWorker();
        binPacket *binp = new binPacket();
        connect(binp,&binPacket::packetValid,this,&ovenController::resolvePacket);
        binp->validPacket(m_data);
        qDebug()<<"Incoming packet, parsing";
    }
}

void ovenController::parseWorker()
{

}

void ovenController::resolvePacket(bool state, binPacket::cmd_header_t header, QByteArray b)
{
    qDebug()<<"Paring packet down, result:"<<state <<" packet size:"<<header.len;
    if(!state) return;
    qDebug()<<"Packet header:"<<header.type<<":"<<header.pid;
    QDataStream ds(b);
    ds.setByteOrder(QDataStream::LittleEndian);
    double dv;
    quint8 mask = header.type & 0xf0;
    if(mask == MASK_CMD_DATA){
        quint8 cmd = header.pid & 0xf;
        switch(cmd){
        case DATA_FAN:
            for(int i=0;i<3;i++){
                m_fans[i].pv = b.at(i);
                if(m_fans[i].pv != m_fans[i].sp){
                    emit updateFan(i);
                }
            }
            break;
        case DATA_RELAY:
            for(int i=0;i<9;i++){
                m_relay[i].pv = b.at(i);
                if(m_relay[i].pv != m_relay[i].sp){
                    qDebug()<<"Update relay";
                    emit updateRelay(i);
                }
            }
            break;
        case DATA_STEAM:
            m_steam.pv = b.at(0);
            emit updateSteam();
            break;
        case DATA_HEATER:
            for(int i=0;i<3;i++){
                m_heater[i].pv = b.at(i*2+1);
                m_heater[i].sp = b.at(i*2);
            }
            break;
        case DATA_TEMP:

            for(int i=0;i<4;i++){
                //m_temperature[i].pv = b.at(i);
                //emit updateTemperature(i);
                ds >> dv;
                m_temperature[i].pv = (qint16)dv;
                qDebug()<<"Temp:" << dv;
            }
            break;
        case DATA_STATE:
            emit updateState();
            break;
        }
    }

    // remove data in m_data
    m_data.remove(0,header.len);
    if(m_data.size() >=8){
        binPacket *binp = new binPacket();
        connect(binp,&binPacket::packetValid,this,&ovenController::resolvePacket);
        binp->validPacket(m_data);
    }
}

void ovenController::start()
{

}
void ovenController::stop()
{

}
void ovenController::pause()
{

}
void ovenController::light(bool on)
{
    m_relay[0].sp = on?1:0;
}

void ovenController::steam()
{
//    QByteArray v;
//    v.append(0x20);
//    v.append(0x0);
//    quint8 cmd = (quint8)(MASK_CMD | CMD1_SETUP);
//    binPacket b(cmd,CMD2_SETUP_STEAM,v);

//    if(m_serialPort->isOpen()){
//        m_serialPort->write(b.packet());
//    }
}

void ovenController::valve(bool on)
{
    m_valves[0].sp = on?1:0;
}

void ovenController::fan(bool on)
{
    m_fans[0].sp = on?1:0;
}

void ovenController::setRelay(int id, int v)
{
    m_relay[id].sp = (qint16)v;
    QByteArray relay;
    for(int i=0;i<9;i++)
        relay.append((m_relay[i].sp==0)?0:1);
    quint8 cmd = (quint8)(MASK_CMD | CMD1_SETUP);
    binPacket b(cmd,CMD2_SETUP_RELAY,relay);

    if(m_serialPort->isOpen()){
        m_serialPort->write(b.packet());
    }
}

void ovenController::handleRecepeRunTimeout()
{

}

QVariantMap ovenController::activeRecepe() const{
    QVariantMap res;
    QString s;
    //qDebug()<<"Request active recepe:"<<m_actRecepeid;

    res.insert("dbid",m_activeRecepe->id());
    res.insert("id",m_actRecepeid);
    res.insert("uh",m_activeRecepe->uhTemp());
    res.insert("lh",m_activeRecepe->lhTemp());
    res.insert("time",m_activeRecepe->bakeTime());
    res.insert("v1_on",m_activeRecepe->v1_on());
    res.insert("v2_on",m_activeRecepe->v2_on());
    res.insert("v1_off",m_activeRecepe->v1_off());
    res.insert("v2_off",m_activeRecepe->v2_off());
    res.insert("s1_time",m_activeRecepe->s1_time());
    res.insert("s2_time",m_activeRecepe->s2_time());
    res.insert("s1_qty",m_activeRecepe->s1_quantity());
    res.insert("s2_qty",m_activeRecepe->s2_quantity());
    res.insert("imgurl",m_activeRecepe->imgurl());
    res.insert("name",m_activeRecepe->name());
    return res;
}


void ovenController::setActiveRecepe(QVariantMap v){

    int dbid = v.value("dbid").toInt();
    m_activeRecepe->setUhTemp(v.value("uh").toInt());
    m_activeRecepe->setLhTemp(v.value("lh").toInt());
    m_activeRecepe->setBakeTime(v.value("time").toInt());
    m_activeRecepe->setV1_on(v.value("v1_on").toInt());
    m_activeRecepe->setV2_on(v.value("v2_on").toInt());
    m_activeRecepe->setV1_off(v.value("v1_off").toInt());
    m_activeRecepe->setV2_off(v.value("v2_off").toInt());
    m_activeRecepe->setS1_time(v.value("s1_time").toInt());
    m_activeRecepe->setS2_time(v.value("s2_time").toInt());
    m_activeRecepe->setS1_quantity(v.value("s1_qty").toInt());
    m_activeRecepe->setS2_quantity(v.value("s2_qty").toInt());
    m_activeRecepe->setImgurl(v.value("imgurl").toString());
    m_activeRecepe->setName(v.value("name").toString());

    //emit activeRecepeChanged();
    //qDebug()<<"UH:"<<m_activeRecepe->uhTemp();
    saveRecord(dbid);
}

QVariantMap ovenController::recepeData(int id) const
{
    QVariantMap res;
    QString s;
    recepe *r = m_recepes.at(id);
    qDebug()<<"Request recepe id:"<<id;

    res.insert("dbid",r->id());
    res.insert("id",id);
    res.insert("uh",r->uhTemp());
    res.insert("lh",r->lhTemp());
    res.insert("time",r->bakeTime());
    res.insert("v1_on",r->v1_on());
    res.insert("v2_on",r->v2_on());
    res.insert("v1_off",r->v1_off());
    res.insert("v2_off",r->v2_off());
    res.insert("s1_time",r->s1_time());
    res.insert("s2_time",r->s2_time());
    res.insert("s1_qty",r->s1_quantity());
    res.insert("s2_qty",r->s2_quantity());
    res.insert("imgurl",r->imgurl());
    res.insert("name",r->name());
    return res;
}


void ovenController::setRecepeData(int id,QVariantMap v){

    int dbid = v.value("dbid").toInt();
    recepe *r = m_recepes.at(id);
    r->setUhTemp(v.value("uh").toInt());
    r->setLhTemp(v.value("lh").toInt());
    r->setBakeTime(v.value("time").toInt());
    r->setV1_on(v.value("v1_on").toInt());
    r->setV2_on(v.value("v2_on").toInt());
    r->setV1_off(v.value("v1_off").toInt());
    r->setV2_off(v.value("v2_off").toInt());
    r->setS1_time(v.value("s1_time").toInt());
    r->setS2_time(v.value("s2_time").toInt());
    r->setS1_quantity(v.value("s1_qty").toInt());
    r->setS2_quantity(v.value("s2_qty").toInt());
    r->setImgurl(v.value("imgurl").toString());
    r->setName(v.value("name").toString());

    //emit activeRecepeChanged();
    //qDebug()<<"UH:"<<m_activeRecepe->uhTemp();
    saveRecord(dbid);
}

int ovenController::recepeCount() const
{
    qDebug()<<"query recepe count:"<<m_recepes.size();
    return m_recepes.size();
}


QVariantMap ovenController::ovenVars()
{
    //qDebug()<<"Request oven vars";
    QVariantMap res;
    res.insert("uh",m_temperature[0].pv);
    res.insert("lh",m_temperature[1].pv);
    res.insert("sh",m_temperature[2].pv);
    res.insert("t_remain_min",m_remainSeconds/60);
    res.insert("t_remain_sec",m_remainSeconds - (m_remainSeconds/60)*60);
    res.insert("t_finish",m_finishTime);
    //qDebug()<<"Time to bake:"<<m_remainSeconds;

    return res;
}

QVariant ovenController::getOvenVarsByName(QString name)
{

}

void ovenController::setOvenVarsByName(QString name, QVariant v)
{

}

void ovenController::setOvenVars(QVariantMap v)
{

}

void ovenController::nextRecepe()
{
    m_actRecepeid++;
    if(m_actRecepeid<m_recepes.size()){
        m_activeRecepe = m_recepes.at(m_actRecepeid);
        //emit activeRecepeChanged();
        emit actRecepeChanged();
    }else{
        m_actRecepeid--;
    }
    m_remainSeconds = m_activeRecepe->bakeTime();
    //qDebug()<<"next recepe:"<<m_actRecepeid;
    qDebug()<<"Time to bake:"<<m_remainSeconds;
}

void ovenController::prevRecepe()
{
    m_actRecepeid--;
    if(m_actRecepeid>=0){
        m_activeRecepe = m_recepes.at(m_actRecepeid);
        //emit activeRecepeChanged();
        emit actRecepeChanged();
    }else{
        m_actRecepeid++;
    }
    m_remainSeconds = m_activeRecepe->bakeTime();
    //qDebug()<<"prev recepe:"<<m_actRecepeid;
    qDebug()<<"Oh Temp:"<<m_activeRecepe->uhTemp();
}
