#ifndef OVENCONTROLLER_H
#define OVENCONTROLLER_H

#include <QObject>
#include <QtCore>
#include <QDebug>
#include "binparser.h"

class QSerialPort;



class timeValue
{
public:
    timeValue(int t, int v)
        :m_time(t),
        m_value(v){}
    int timeVal() const{return m_time;}
    int value() const{return m_value;}
    void setTime(int v) {m_time = v;}
    void setValue(int v) {m_value = v;}

private:
    int m_time;
    int m_value;
};

class recepe:public QObject{
    Q_OBJECT
    Q_PROPERTY(int uhTemp READ uhTemp WRITE setUhTemp NOTIFY uhTempChanged)
    Q_PROPERTY(int lhTemp READ lhTemp WRITE setLhTemp NOTIFY lhTempChanged)
    Q_PROPERTY(int bakeTime READ bakeTime WRITE setBakeTime NOTIFY bakeTimeChanged)
    Q_PROPERTY(QString imgurl READ imgurl WRITE setImgurl NOTIFY imgurlChanged)
public:
    explicit recepe(QObject *parent = nullptr){};

    int uhTemp() const {return m_tempUh;}
    int lhTemp() const {return m_tempLh;}
    int bakeTime() const {return m_bakeTime;}
    void setUhTemp(int v){m_tempUh = v;emit uhTempChanged();}
    void setLhTemp(int v){m_tempLh = v;}
    void setBakeTime(int v){m_bakeTime = v;}
    int steamCount(){return steamOp.size();}
    int valveCount(){return valveOp.size();}
    QString imgurl() const{return m_imgurl;}
    void setImgurl(QString v){m_imgurl = v;}

    Q_INVOKABLE void addSteam(timeValue v){
        steamOp.append(new timeValue(v.timeVal(),v.value()));
    }
    Q_INVOKABLE void setSteam(int id,timeValue v){
        if(id < steamOp.size()){
            steamOp.at(id)->setTime(v.timeVal());
            steamOp.at(id)->setValue(v.value());
        }
    }
    Q_INVOKABLE timeValue *getSteam(int id){
        if(id < steamOp.size())
            return steamOp.at(id);
        return nullptr;
    }

    Q_INVOKABLE void addValve(timeValue v){
        valveOp.append(new timeValue(v.timeVal(),v.value()));
    }
    Q_INVOKABLE void setValve(int id,timeValue v){
        if(id < valveOp.size()){
            valveOp.at(id)->setTime(v.timeVal());
            valveOp.at(id)->setValue(v.value());
        }
}
    Q_INVOKABLE timeValue *getValve(int id){
        if(id < valveOp.size())
            return valveOp.at(id);
        return nullptr;
    }

Q_SIGNALS:
    void uhTempChanged();
    void lhTempChanged();
    void bakeTimeChanged();
    void imgurlChanged();

private:

    int m_tempUh;
    int m_tempLh;
    int m_bakeTime;
    QList<timeValue*> steamOp;
    QList<timeValue*> valveOp;
    QString m_imgurl;

};
Q_DECLARE_METATYPE(recepe*)

class ovenController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString runTime READ runTime  NOTIFY runTimeChanged)
    Q_PROPERTY(QString finishTime READ finishTime NOTIFY finishTimeChanged)
//    Q_PROPERTY(QString temp_oh READ temp_oh NOTIFY temp_ohChanged)
//    Q_PROPERTY(QString temp_oh READ temp_lh NOTIFY temp_lhChanged)
//    Q_PROPERTY(QString temp_oh READ temp_st NOTIFY temp_stChanged)

    Q_PROPERTY(QVariantMap activeRecepe READ activeRecepe WRITE setActiveRecepe NOTIFY activeRecepeChanged)
public:
    enum oven_command_mask{
        MASK_CMD=0x80,
        MASK_CMD_RET_OK=0x10,
        MASK_CMD_RET_ERR=0x20,
        MASK_CMD_RET_BUSY=0x30,
        MASK_CMD_DATA = 0x40,
        MASK_CMD_RET_CFG=0x50
    };
    enum oven_command_cmd1
    {
        CMD1_NONE,
        CMD1_CONTROL,
        CMD1_SETUP,
    };
    enum oven_command_cmd2{
        CMD2_NONE,
        CMD2_SETUP_RELAY,
        CMD2_SETUP_FAN,
        CMD2_SETUP_HEATER,
        CMD2_SETUP_STEAM,
        CMD2_SETUP_SENSOR,
        CMD2_SETUP_SYSINFO,
        CMD2_CRITICAL_DEFAULT
    };
    enum oven_data{
        DATA_NONE,
        DATA_RELAY,
        DATA_FAN,
        DATA_HEATER,
        DATA_STEAM,
        DATA_TEMP,
        DATA_STATE=0x0e
    };
    struct ctrl_value{
        qint16 sp;
        qint16 pv;
    };

    explicit ovenController(QObject *parent = nullptr);
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void steam();
    Q_INVOKABLE void light(bool on);
    Q_INVOKABLE void valve(bool on);
    Q_INVOKABLE void fan(bool on);

    Q_INVOKABLE bool relay(int id){return m_relay[id].sp==0?false:true;}
    Q_INVOKABLE void setRelay(int id, int v);
    Q_INVOKABLE void setTemperature(int id,int v){m_heater[id].sp=(qint16)v;}
    Q_INVOKABLE int temperature(int id){return m_heater[id].pv;}
    Q_INVOKABLE QVariant currentRecepe() const {
        QVariant v;
        v.setValue(static_cast<recepe*>(currRecepe));
        return v;
    }

    QVariantMap activeRecepe() const;
    void setActiveRecepe(QVariantMap v);

    Q_INVOKABLE void setActiveRecepe(int id){
        if(id < m_recepes.size())
            m_activeRecepe = m_recepes.at(id);
        else
            m_activeRecepe = nullptr;
    }

    QString runTime() const {return m_remainTime;}
    QString finishTime() const {return m_finishTime;}


signals:
    void updateTemperature(int id);
    void updateRelay(int id);
    void updateFan(int id);
    void updateState();
    void updateSteam();
    void runTimeChanged();
    void finishTimeChanged();
    void activeRecepeChanged();

public slots:
    void resolvePacket(bool state, binPacket::cmd_header_t header, QByteArray b);
private slots:
    void pollController();
    void serialRead();
    void parseWorker();
    void handleRecepeRunTimeout();
private:
    void loadParameter();
    void initDatabase();

private:
    bool m_running;
    bool m_light;
    bool m_valve;
    bool m_fan;
    QSerialPort *m_serialPort;
    QByteArray m_data;
    QTimer *m_timer;
    QTimer *m_recepeTimer;
    QDateTime m_startTime;
    // oven parameter
    ctrl_value m_heater[4];
    ctrl_value m_relay[9];
    ctrl_value m_fans[3];
    ctrl_value m_temperature[4];
    ctrl_value m_steam;
    ctrl_value m_valves[3];
    bool m_waitCmdResp;
    recepe *currRecepe;
    recepe *m_activeRecepe;
    QList<recepe*> m_recepes;
    QString m_remainTime;
    QString m_finishTime;
};

#endif // OVENCONTROLLER_H
