#include "ovencontroller.h"
#include <QSerialPort>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

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


    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&ovenController::pollController);
    connect(m_serialPort,&QSerialPort::readyRead,this,&ovenController::serialRead);
    initDatabase();
    loadParameter();

    m_timer->start(1000);

    currRecepe = new recepe();
    currRecepe->setUhTemp(200);
    m_activeRecepe = currRecepe;
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
        QSqlQuery query;
        QStringList ls = db.tables();
        for(int i=0;i<ls.size();i++){
            qDebug()<<"Table:"<<ls.at(i);
        }
//        query.prepare("SELECT * FROM oven_db");
//        while(query.next()){
//            if(query.value("type").toString() == "table"){
//                qDebug()<<"Table:"<<query.value("name");
//            }
//        }
        db.close();
    }
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
//    quint8 cmd = (quint8)(MASK_CMD | CMD1_SETUP);
//    binPacket b(cmd,CMD2_SETUP_RELAY,relay);

//    if(m_serialPort->isOpen()){
//        //qDebug()<<"Send to com:";//<<b.packet();
//        m_serialPort->write(b.packet());
//    }

    currRecepe->setUhTemp(currRecepe->uhTemp()+1);
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
    quint8 mask = header.type & 0xf0;
    if(mask == MASK_CMD_DATA){
        quint8 cmd = header.type & 0xf;
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
                m_temperature[i].pv = b.at(i);
                emit updateTemperature(i);
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
    res.insert("oh",m_activeRecepe->uhTemp());
    res.insert("lh",m_activeRecepe->lhTemp());
    res.insert("time",m_activeRecepe->bakeTime());
    res.insert("nofSteam",m_activeRecepe->steamCount());
    res.insert("nofValve",m_activeRecepe->valveCount());
    return res;
}
void ovenController::setActiveRecepe(QVariantMap v){
    m_activeRecepe->setUhTemp(v.value("oh").toInt());
    m_activeRecepe->setLhTemp(v.value("lh").toInt());
    m_activeRecepe->setBakeTime(v.value("time").toInt());
    emit activeRecepeChanged();
    qDebug()<<"UH:"<<m_activeRecepe->uhTemp();
}

