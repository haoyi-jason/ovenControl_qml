#ifndef OVENCONTROLLER_H
#define OVENCONTROLLER_H

#include <QObject>
#include <QtCore>
#include <QDebug>
#include "binparser.h"
using namespace std;

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

class recepe{
    Q_GADGET
    Q_PROPERTY(int id READ id WRITE setId)
    Q_PROPERTY(int uhTemp READ uhTemp WRITE setUhTemp  )
    Q_PROPERTY(int lhTemp READ lhTemp WRITE setLhTemp  )
    Q_PROPERTY(int bakeTime READ bakeTime WRITE setBakeTime  )
    Q_PROPERTY(QString imgurl READ imgurl WRITE setImgurl  )
    Q_PROPERTY(QString name READ name WRITE setName  )
    Q_PROPERTY(int v1_on READ v1_on WRITE setV1_on  )
    Q_PROPERTY(int v1_off READ v1_off WRITE setV1_on  )
    Q_PROPERTY(int v2_on READ v2_on WRITE setV2_on  )
    Q_PROPERTY(int v2_off READ v2_off WRITE setV2_off  )
    Q_PROPERTY(int s1_time READ s1_time WRITE setS1_time  )
    Q_PROPERTY(int s1_quantity READ s1_quantity WRITE setS1_quantity  )
    Q_PROPERTY(int s2_time READ s2_time WRITE setS2_time  )
    Q_PROPERTY(int s2_quantity READ s2_quantity WRITE setS2_quantity  )
public:
    recepe(){}
    int uhTemp() const {return m_tempUh;}
    int lhTemp() const {return m_tempLh;}
    int bakeTime() const {return m_bakeTime;}
    void setUhTemp(const int& v){m_tempUh = v; }
    void setLhTemp(const int& v){m_tempLh = v;}
    void setBakeTime(int v){m_bakeTime = v;}
    QString imgurl() const{return m_imgurl;}
    void setImgurl(QString v){m_imgurl = v;}
    QString name() const {return m_name;}
    void setName(QString v){m_name = v;}

    int v1_on() const{return m_valveOn[0];}
    int v2_on() const{return m_valveOn[1];}
    int v1_off() const{return m_valveOff[0];}
    int v2_off() const{return m_valveOff[1];}
    void setV1_on(int v){m_valveOn[0] = v;}
    void setV2_on(int v){m_valveOn[1] = v;}
    void setV1_off(int v){m_valveOff[0] = v;}
    void setV2_off(int v){m_valveOff[1] = v;}

    int s1_time() const{return m_steamOn[0];}
    int s2_time() const{return m_steamOn[1];}
    int s1_quantity() const{return m_steamQuantity[0];}
    int s2_quantity() const{return m_steamQuantity[1];}
    void setS1_time(int v){m_steamOn[0] = v;}
    void setS2_time(int v){m_steamOn[1] = v;}
    void setS1_quantity(int v){m_steamQuantity[0] = v;}
    void setS2_quantity(int v){m_steamQuantity[1] = v;}

    int id() const{return m_id;}
    void setId(int v){m_id = v;}

private:

    int m_tempUh;
    int m_tempLh;
    int m_bakeTime;
    QString m_imgurl;
    QString m_name;

    int m_valveOn[2];
    int m_valveOff[2];
    int m_steamOn[2];
    int m_steamQuantity[2];
    int m_id;

};

Q_DECLARE_METATYPE(recepe)

struct ovenConfig{
    Q_GADGET
public:
    int m_maxTemp, m_minTemp;
    int m_sensorType;
    int m_defaultRecepe;
    int m_steamCountPerLitre,m_defaultSteamMl;
    bool m_astEnSun,m_astEnMon,m_astEnTue,m_astEnWen,m_astEnThu,m_astEnFri,m_astEnSat;
    QTime m_astSun,m_astMon,m_astTue,m_astWen,m_astThu,m_astFri,m_astSat;
    int m_steamTempHi,m_steamTempLow;
    Q_PROPERTY(int maxTemp MEMBER m_maxTemp)
    Q_PROPERTY(int minTemp MEMBER m_minTemp)
    Q_PROPERTY(int sensorType MEMBER m_sensorType)
    Q_PROPERTY(int defaultRecepe MEMBER m_defaultRecepe)
    Q_PROPERTY(int countPerLitre MEMBER m_steamCountPerLitre)
    Q_PROPERTY(int defaultSteamMl MEMBER m_defaultSteamMl)
    Q_PROPERTY(bool astEnMon MEMBER m_astEnMon)
    Q_PROPERTY(bool astEnTue MEMBER m_astEnTue)
    Q_PROPERTY(bool astEnWen MEMBER m_astEnWen)
    Q_PROPERTY(bool astEnThu MEMBER m_astEnThu)
    Q_PROPERTY(bool astEnFri MEMBER m_astEnFri)
    Q_PROPERTY(bool astEnSat MEMBER m_astEnSat)
    Q_PROPERTY(bool astEnSun MEMBER m_astEnSun)
    Q_PROPERTY(QTime astMon MEMBER m_astMon)
    Q_PROPERTY(QTime astTue MEMBER m_astTue)
    Q_PROPERTY(QTime astWen MEMBER m_astWen)
    Q_PROPERTY(QTime astThu MEMBER m_astThu)
    Q_PROPERTY(QTime astFri MEMBER m_astFri)
    Q_PROPERTY(QTime astSat MEMBER m_astSat)
    Q_PROPERTY(QTime astSun MEMBER m_astSun)
    Q_PROPERTY(int steamHigh MEMBER m_steamTempHi)
    Q_PROPERTY(int steamLow MEMBER m_steamTempLow)
};
Q_DECLARE_METATYPE(ovenConfig)

class ovenController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap ovenVars READ ovenVars WRITE setOvenVars NOTIFY ovenVarsChanged)
    Q_PROPERTY(QString runTime READ runTime  NOTIFY runTimeChanged)
    Q_PROPERTY(QString finishTime READ finishTime NOTIFY finishTimeChanged)
    Q_PROPERTY(qint16 temp_oh READ temp_oh NOTIFY temp_ohChanged)
    Q_PROPERTY(qint16 temp_lh READ temp_lh NOTIFY temp_lhChanged)
    Q_PROPERTY(qint16 temp_sh READ temp_sh NOTIFY temp_shChanged)
    Q_PROPERTY(int activeR READ activeR WRITE setActiveR NOTIFY activeRChanged)

    Q_PROPERTY(QVariantMap activeRecepe READ activeRecepe WRITE setActiveRecepe NOTIFY activeRecepeChanged)
    //Q_PROPERTY(QVariantMap recepeData READ recepeData WRITE setRecepeData NOTIFY recepeDataChanged)
    Q_PROPERTY(QString rtc READ rtc NOTIFY rtcChanged)

    Q_PROPERTY(QAbstractItemModel* recepeModel READ recepeModel)
    Q_PROPERTY(recepe actRecepe READ actRecepe WRITE setActRecepe NOTIFY actRecepeChanged)
    Q_PROPERTY(bool celius READ celius)
    Q_PROPERTY(ovenConfig ovenCfg READ ovenCfg WRITE setOvenCfg NOTIFY ovenCfgChanged)
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
        CMD2_SETUP_READTEMP,
        CMD2_SETUP_SYSINFO,
        CMD2_CRITICAL_DEFAULT
    };
    enum oven_data{
        DATA_NONE,
        DATA_RELAY,
        DATA_FAN,
        DATA_HEATER,
        DATA_STEAM,
        DATA_SENSOR,
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

    QVariantMap ovenVars();
    void setOvenVars(QVariantMap v);
    qint16 temp_oh() const {return m_temperature[0].pv;}
    qint16 temp_lh() const {return m_temperature[1].pv;}
    qint16 temp_sh() const {return m_temperature[2].pv;}

    QString rtc() const{return QTime::currentTime().toString("HH:mm:ss");}

    Q_INVOKABLE void nextRecepe();
    Q_INVOKABLE void prevRecepe();

    Q_INVOKABLE QVariant getOvenVarsByName(QString name);
    Q_INVOKABLE void setOvenVarsByName(QString name , QVariant v);

    Q_INVOKABLE QVariantMap recepeData(int id) const;
    Q_INVOKABLE void setRecepeData(int id , QVariantMap v);
    Q_INVOKABLE int recepeCount() const;

    int activeR() const {return m_actRecepeid;}
    void setActiveR(int id){m_actRecepeid = id;emit activeRChanged();}

    QAbstractItemModel *recepeModel() const{

        recepe r = qvariant_cast<recepe>(m_recepeModel->data(m_recepeModel->index(0,0),Qt::EditRole));
        qDebug()<<"access model:"<<r.uhTemp();

        return m_recepeModel;
    }
    Q_SLOT void addRecepe(const int &id, const int& uhTemp, const int& lhTemp, const int& stTemp,
                          const int &baketime, const QString &name, const QString& imgurl, const int &s1_time, const int &s1_qty, const int &s2_time, const int &s2_qty, const int &v1_on, const int &v1_off, const int &v2_on, const int &v2_off);

    recepe actRecepe() const{return *m_activeRecepe;}
    void setActRecepe(recepe v){m_activeRecepe = &v;}
    bool celius() const{return m_celius;}
    ovenConfig ovenCfg() const{return m_ovenVar;}
    void setOvenCfg(ovenConfig v){m_ovenVar = v;}
signals:
    void updateTemperature(int id);
    void updateRelay(int id);
    void updateFan(int id);
    void updateState();
    void updateSteam();
    void runTimeChanged();
    void finishTimeChanged();
    void activeRecepeChanged();
    void ovenVarsChanged();
    void temp_ohChanged();
    void temp_lhChanged();
    void temp_shChanged();
    void rtcChanged();
    void activeRChanged();
    void actRecepeChanged();
    void ovenCfgChanged();

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
    void saveRecord(int id);

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
    int m_actRecepeid, m_currRecepeid;
    int m_remainSeconds;
    QAbstractItemModel *m_recepeModel;
    bool m_celius;
    ovenConfig m_ovenVar;
};

#endif // OVENCONTROLLER_H
