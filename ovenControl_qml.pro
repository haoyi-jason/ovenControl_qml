QT += quick serialport core sql
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    ovencontroller.cpp \
    binparser.cpp \
    cmdinterface.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ovencontroller.h \
    binparser.h \
    cmdinterface.h

DISTFILES += \
    mainView.qml \
    qml/Button.qml \
    qml/LabelText.qml \
    qml/RecepeView.qml \
    qml/ButtonStart.qml \
    qml/ButtonEco.qml \
    qml/ButtonPower.qml \
    qml/ManualBar.qml \
    qml/LabelValue.qml \
    qml/ButtonFan.qml \
    qml/ButtonLight.qml \
    qml/ButtonValve.qml \
    qml/ButtonImage.qml \
    qml/ImageText.qml \
    qml/ImageEdit.qml \
    qml/testPanel.qml \
    qml/TemperatureDisp.qml \
    qml/TimeDisp.qml \
    qml/RecepeViewV2.qml \
    qml/RecepeViewV2.qml \
    qml/RecepeViewS.qml \
    parameter_edit.qml \
    qml/RecepeEditor.qml \
    qml/LabelText2.qml
