#ifndef BINPARSER_H
#define BINPARSER_H

#include <QObject>
#include <QDataStream>
#include <QDebug>
class binPacket:public QObject{
    Q_OBJECT
public:
    const quint8 MAGIC1 = 0xab;
    const quint8 MAGIC2 = 0xba;
    typedef struct{
        quint8 magic1;
        quint8 magic2;
        quint8 type;
        quint8 pid;
        quint16 len;
        quint16 crc;
    }cmd_header_t;

    explicit binPacket(quint8 cmd, quint8 pid, QByteArray &d):
        m_cmd(cmd),
        m_pid(pid),
        m_data(d)
    {
        //qDebug()<<"binparser:packet:construc";
    }
    explicit binPacket(){

    }

    quint16 checkSum16(const quint8 *data, quint16 length){
        quint16 chksum = 0;
        for(int i=0;i<length;i++){
            chksum+=data[i];
        }

        return chksum;
    }

    void validPacket(QByteArray b){
        cmd_header_t header;
        QByteArray s;
        if(b.size() >= 8){
            qDebug()<<"parse:size ok, buffer size="<<b.size();
            memcpy((char*)&header,b.constData(),8);
            if((header.magic1 == MAGIC1)&&(header.magic2==MAGIC2)){
                if(b.size() >= header.len){
                    s = b.mid(8,header.len-8);
                    emit packetValid(true,header,s);
                    qDebug()<<"packet valid";
                }else{
                    emit packetValid(false,header,s);
                    qDebug()<<"packet invalid";
                }
            }
        }else{
            qDebug()<<"packet invalid";
            emit packetValid(false,header,s);
        }
        this->deleteLater();
    }

    QByteArray packet(){
        QByteArray p;
        cmd_header_t header;
        header.magic1 = 0xab;
        header.magic2 = 0xba;
        header.type = m_cmd;
        header.pid = m_pid;
        header.len = m_data.size()+8;
        quint16 crc = 0;

        header.crc = checkSum16((quint8*)&header,6);
        for(int i=0;i<m_data.size();i++)
            header.crc += m_data.at(i);

        p.append((char*)&header,8);
        p.append(m_data);
        //qDebug()<<"binparser:packet:"<<p<<" sz="<<p.size();
        return p;
    }

signals:
    void packetValid(bool state, cmd_header_t header, QByteArray b);

private:
    quint8 m_cmd;
    quint8 m_pid;
    cmd_header_t header;
    QByteArray m_data;
};


class binParser : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(quint8 cmd READ cmd WRITE setCmd NOTIFY cmdChanged)
//    Q_PROPERTY(quint8 pid READ pid WRITE setPid NOTIFY pidChanged)
public:
    explicit binParser(QObject *parent = nullptr);
    void sendCommand(quint8 cmd, quint8 pid, QByteArray &d);
    void appendPacket(QByteArray b);
    void clearData(){m_data.clear();}
    //int parsePacket(QByteArray *d);


signals:
    void parsedCommand(bool state, quint8 cmd, quint8 cmd2, QByteArray b);
    void write(QByteArray);

public slots:
    int parsePacket(QByteArray b);

private:
    quint8 cmd,pid;
    QByteArray m_data;
};

#endif // BINPARSER_H
