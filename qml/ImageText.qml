import QtQuick 2.0

Rectangle {
    property string image: ""
    property string content: "content"
    Row{
        spacing: 10
        height:parent.height
        Image {
            id:img
            anchors.left: parent.left
            anchors.top:parent.top
            source:image
            width:62.5
            height:62.5
            fillMode: Image.PreserveAspectFit
        }
        Text {
            id: txt
            font.pixelSize: 48
            font.bold: true
            //height: parent.height
            color: "red"
            anchors.left: img.right
            text: qsTr(content)
            Image {
                id: name
                opacity: 0.2
                width: parent.width
                height:parent.height
                source: "../icons/bg_metalpng.png"
            }
        }
    }
}
