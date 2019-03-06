/*
 *  Binary packet parser for grididea communication
 *  Autohr: Jason
 *  Dat: 22/1, 2019
 */

#include "binparser.h"

binParser::binParser(QObject *parent) : QObject(parent)
{

}

void binParser::sendCommand(quint8 cmd, quint8 pid, QByteArray &d)
{

}

int binParser::parsePacket(QByteArray b)
{

    return 0;
}
