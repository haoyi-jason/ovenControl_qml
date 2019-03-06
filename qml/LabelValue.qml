import QtQuick 2.0

Item {
    property string caption: "caption"
    property string content: "content"
    height:160
    Text {
        id: label
        x:10
        y:10
        height:80
        font.pixelSize: 24
        text: qsTr(caption)
    }
    Text {
        id: txt
        x:20
        y:40
        height:80
        font.pixelSize: 36
        text: qsTr(content)
    }
}
