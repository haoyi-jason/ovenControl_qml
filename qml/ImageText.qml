import QtQuick 2.0

Rectangle {
    property string caption: "caption"
    property string content: "content"
    //height:160
    Row{
        spacing: 20
    Text {
        id: label
        //x:10
        //y:10
        //height:80
        font.pixelSize: 24
        text: qsTr(caption)
    }
    Text {
        id: txt
        //x:20
        //y:40
        //height:80
        font.pixelSize: 60
        text: qsTr(content)
    }
    }
}
