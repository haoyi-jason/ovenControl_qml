#ifndef CMDINTERFACE_H
#define CMDINTERFACE_H

#include <QObject>
#include "binparser.h"

class controlPoint:public QObject
{
    Q_OBJECT
    Q_PROPERTY(int v1 READ v1 WRITE setV1 NOTIFY v1Changed)
    Q_PROPERTY(int v2 READ v2 WRITE setV2 NOTIFY v2Changed)
public:
    explicit controlPoint(int v1,int v2):m_v1(v1),m_v2(v2){}
    int v1() const {return m_v1;}
    int v2() const {return m_v2;}
    void setV1(int v){m_v1 = v;}
    void setV2(int v){m_v2 = v;}
signals:
    void v1Changed();
    void v2Changed();
private:
    int m_v1,m_v2;
};

class recepe_t:public QObject
{
    Q_OBJECT
    Q_PROPERTY(int oh READ oh WRITE setOh NOTIFY ohChanged)
    Q_PROPERTY(int lh READ lh WRITE setLh NOTIFY lhChanged)
    Q_PROPERTY(int baketime READ baketime WRITE setBaketime NOTIFY baketimeChanged)
public:
    recepe_t(int oh, int lh, int baketime):m_oh(oh),m_lh(lh),m_time(baketime){}
    int oh() const {return m_oh;}
    int lh() const {return m_lh;}
    int baketime() const {return m_time;}
    void setOh(int v){m_oh = v;}
    void setLh(int v){m_lh = v;}
    void setBaketime(int v){m_time = v;}
//    void addValveControl(controlPoint &cp){
//        m_valveControl.append(new controlPoint(cp.v1(),cp.v2()));
//    }
//    void addSteamControl(controlPoint &cp){
//        m_steamControl.append(new controlPoint(cp.v1(),cp.v2()));
//    }

signals:
    void ohChanged();
    void lhChanged();
    void baketimeChanged();

private:
    int m_oh;
    int m_lh;
    int m_time;
    QList<controlPoint*> m_valveControl;
    QList<controlPoint*> m_steamControl;

};

class cmdInterface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool power READ power WRITE setPower NOTIFY powerChanged)
    Q_PROPERTY(bool Start READ Start WRITE setStart NOTIFY StartChanged)
    Q_PROPERTY(bool green READ green WRITE setGreen NOTIFY greenChanged)
    Q_PROPERTY(bool autoStart READ autoStart WRITE setAutoStart NOTIFY autoStartChanged)
    Q_PROPERTY(bool fan READ fan WRITE setFan NOTIFY fanChanged)
    Q_PROPERTY(bool valve READ valve WRITE setValve NOTIFY valveChanged)
    Q_PROPERTY(bool light READ light WRITE setLight NOTIFY lightChanged)
    Q_PROPERTY(int oh READ oh WRITE setOh NOTIFY ohChanged)
    Q_PROPERTY(int  lh READ lh WRITE setLh NOTIFY lhChanged)
    Q_PROPERTY(int bakeTime READ bakeTime WRITE setBakeTime NOTIFY bakeTimeChanged)
    //recepe related
    Q_PROPERTY(int recepeOh READ recepeOh WRITE setRecepeOh NOTIFY recepeOhChanged)
    Q_PROPERTY(int recepeLh READ recepeLh WRITE setRecepeLh NOTIFY recepeLhChanged)
    Q_PROPERTY(int recepeTime READ recepeTime WRITE setRecepeTime NOTIFY recepeTimeChanged)

public:
    explicit cmdInterface(QObject *parent = nullptr);
    bool power() const {return m_power;}
    bool Start() const {return m_start;}
    bool green() const {return m_green;}
    bool autoStart() const {return m_autostart;}
    bool fan() const {return m_fan;}
    bool valve() const {return m_valve;}
    bool light() const {return m_light;}
    int oh() const {return m_oh;}
    int lh() const {return m_lh;}
    int bakeTime() const {return m_time;}

    void setPower(bool v){m_power = v;}
    void setStart(bool v){m_start = v;}
    void setGreen(bool v){m_green = v;}
    void setAutoStart(bool v){m_autostart = v;}
    void setFan(bool v){m_fan=v;}
    void setValve(bool v){m_valve = v;}
    void setLight(bool v){m_light = v;}
    void setOh(int v){m_oh = v;}
    void setLh(int v){m_lh = v;}
    void setBakeTime(int v){m_time = v;}


    int recepeOh() const{if(m_actRecepe) return m_actRecepe->oh();}
    int recepeLh() const{if(m_actRecepe) return m_actRecepe->lh();}
    int recepeTime() const{if(m_actRecepe) return m_actRecepe->baketime();}

    void setRecepeOh(int v){if(m_actRecepe) m_actRecepe->setOh(v);}
    void setRecepeLh(int v){if(m_actRecepe) m_actRecepe->setLh(v);}
    void setRecepeTime(int v){if(m_actRecepe) m_actRecepe->setBaketime(v);}

    Q_INVOKABLE void addRecepe();
    Q_INVOKABLE void loadRecepe(int id);
    Q_INVOKABLE void addRecepeSteam(int v1, int v2);
    Q_INVOKABLE void rmvRecepeSteam(int id);
    Q_INVOKABLE void addRecepeValve(int v1, int v2);
    Q_INVOKABLE void rmvRecepeValve(int id);


signals:
    void powerChanged();
    void StartChanged();
    void greenChanged();
    void autoStartChanged();
    void fanChanged();
    void valveChanged();
    void lightChanged();
    void ohChanged();
    void lhChanged();
    void bakeTimeChanged();

    void recepeOhChanged();
    void recepeLhChanged();
    void recepeTimeChanged();
public slots:

private:
    bool m_power;
    bool m_start;
    bool m_green;
    bool m_autostart;
    bool m_fan;
    bool m_valve;
    bool m_light;
    int m_oh;
    int m_lh;
    int m_time;
    QList<recepe_t*> m_recepe;
    recepe_t* m_actRecepe;

};

#endif // CMDINTERFACE_H
