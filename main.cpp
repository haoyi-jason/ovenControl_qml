#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QScreen>
#include "ovencontroller.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    ovenController oven;
    engine.rootContext()->setContextProperty("oven",&oven);
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.load(QUrl(QStringLiteral("mainView.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    //QScreen *screen = QGuiApplication::primaryScreen();
    //QGuiApplication::primaryScreen()->setOrientationUpdateMask(Qt::PortraitOrientation);


    return app.exec();
}
