import QtQuick 2.0

Rectangle {
    property string imgurl: ""
    property string t1: "16"
    property string t2: "55"
    Image {
        id:img
        anchors.left: parent.left
        anchors.top:parent.top
        source:imgurl
        width:62.5
        height:62.5
        fillMode: Image.PreserveAspectFit
    }
    Text {
        id: txt
        font.pixelSize: 60
        font.bold: true
        width:150
        //font.family: "./font/VarelaRound-Regular"
        //height: parent.height
        color: "#92F7FD"
        anchors.left: img.right
        anchors.leftMargin: 20
        anchors.bottom: img.bottom
        text: qsTr(t1)+":"+qsTr(t2)
    }

}
