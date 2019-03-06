#ifndef CMDINTERFACE_H
#define CMDINTERFACE_H

#include <QObject>

class cmdInterface : public QObject
{
    Q_OBJECT
public:
    explicit cmdInterface(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CMDINTERFACE_H