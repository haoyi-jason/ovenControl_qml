import QtQuick 2.0

Rectangle {
    property string caption: "caption"
    property string content: "content"
    height:160
    border.color: "red"
    border.width: 5
    //Row{
      //  spacing: 20
        Text{
            id:rtc
            x:20
            text:"17:09:00"
            font.bold: true
            font.pixelSize: 36
        }
        Button{
            id:btnHome
            x:500
            //anchors.verticalCenter: parent.verticalCenter
            Image {
                source: "../icons/Home.png"
            }
        }

    //}
}
