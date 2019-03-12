import QtQuick 2.0

Rectangle {
    id:root
    property string caption: "caption"
    property string content: "content"
    property int v1: 0
    property int v2: 0
    height:parent.height
    width:parent.width
    color: "transparent"
    Row{
        width:parent.width
        height: parent.height
        spacing: 0
        Text {
            id: label
            width:160
            font.pixelSize: 24
            font.bold: true
            font.family: "NotoSansTC-Bold"
            color:"#92F7FD"
            text: qsTr(caption)
        }
        TextInput {
            id: txt
            //anchors.left: label.right
            width:50
            //height: parent.height
            font.pixelSize: 32
            font.bold: true
            font.family: "NotoSansTC-Bold"
            color:"#92F7FD"
            text: Number(v1).toLocaleString()
            inputMethodHints: Qt.ImhDigitsOnly
        }
        TextInput {
            id: txt2
            //anchors.left: txt.right
            width:50
            //height: parent.height
            font.pixelSize: 32
            font.bold: true
            font.family: "NotoSansTC-Bold"
            color:"#92F7FD"
            text: Number(v2).toLocaleString()
            inputMethodHints: Qt.ImhDigitsOnly
        }
    }
}
