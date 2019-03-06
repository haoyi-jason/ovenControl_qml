#ifndef OVENCONTROLLER_H
#define OVENCONTROLLER_H

#include <QObject>

class ovenController : public QObject
{
    Q_OBJECT
public:
    explicit ovenController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // OVENCONTROLLER_H