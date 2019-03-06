import QtQuick 2.0

Rectangle {
    property string caption: "caption"
    property string unit:"unit"
    property int content: 0
    property int lowBound: 0
    property int hiBound: 1000
    //height:160
    Row{
        //anchors.fill: parent
        spacing: 20
        Text {
            width:100
            height:60
            id: label
            font.pixelSize: 24
            text: qsTr(caption)
        }
        Text {
            id: txt
            width:100
            height:80
            font.pixelSize: 60
            font.bold: true
            color: Qt.rgba((content)/200,(200-content)/200,1,1)
            text: Number(content).toLocaleString()
        }
        Text {
            id: unt
            width:100
            height:60
            font.pixelSize: 36
            text: unit
        }
    }
}
