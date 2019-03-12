import QtQuick 2.0

Rectangle {
    property string imgurl: ""
    property string temp1: "100"
    property string temp2: "100"
    property bool celius:true
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
        id: t1
        font.pixelSize: 60
        font.bold: true
        width:150
        font.family: "NotoSansTC-Bold"
        //height: parent.height
        color: "#92F7FD"
        anchors.left: img.right
        anchors.leftMargin: 20
        anchors.bottom: img.bottom
        text: qsTr(temp1)
    }
    Text {
        id: t2
        font.pixelSize: 25
        font.bold: true
        font.family: "NotoSansTC-Bold"
        color: "#92F7FD"
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        text: "/ " + qsTr(temp2)
    }
    Text {
        id: unit
        font.pixelSize: 42
        font.bold: true
        font.family: "NotoSansTC-Bold"
        color: "#92F7FD"
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: parent.top
        text: celius?"C":"F"
    }
}
