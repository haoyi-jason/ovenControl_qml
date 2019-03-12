import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.VirtualKeyboard 2.2

import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls 2.2
import "./qml" as GI
import Qt.labs.calendar 1.0
import QtQuick.Controls.Styles 1.0
Rectangle {
    //anchors.fill: parent
    Column{
        x:50
        y:50
        width:parent.width*0.8
        height: parent.height
        spacing: 5
        GI.LabelText{
            width: parent.width
            height:32
            caption: "Temp.High"
            content: oven.ovenCfg.maxTemp
        }
        GI.LabelText{
            width: parent.width
            height:32
            caption: "Temp.Low"
            content: oven.ovenCfg.minTemp
        }
    }
}
