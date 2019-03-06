#ifndef BINPARSER_H
#define BINPARSER_H

#include <QObject>

class binParser : public QObject
{
    Q_OBJECT
public:
    explicit binParser(QObject *parent = nullptr);

signals:

public slots:
};

#endif // BINPARSER_H