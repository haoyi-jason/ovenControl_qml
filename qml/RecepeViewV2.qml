import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQml 2.2
//import "../qml" as GI

Column{
    id:root
    property int uh: 0
    property int lh: 0
    property int baketime: 0
    property string imgurl: ""
    property string caption: ""
    spacing: 20
    width: parent.width
    height: parent.height
    signal nextR
    signal prevR
    signal showRecepeWin


    Image{
        id:rcpimg
        width:560
        height:239
        fillMode: Image.PreserveAspectFit
        source:imgurl
    }
    Row{
        width: 560
        height:125
        spacing: 20
        ButtonImage{
            id:prevRecepe
            imgNormal: "../icons/A01-PREV.png"
            imgPressed: "../icons/A01-PREVA.png"
            width: 125
            height:125
            onDeactivated: root.prevR()
        }
        Column{
            width:270
            height:125
            Text {
                id: recepeName
                font.pixelSize: 29
                font.bold: true
                font.family: "NotoSansTC-Bold"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: qsTr(caption)
                color:"#92F7FD"
                height:62.5
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Button{
                id:recepeWin
                width: parent.width
                height: 62.5
                anchors.horizontalCenter: parent.horizontalCenter
                background: Rectangle{
                    color:"transparent"
                }

                Image{
                    id:ii1
                    anchors.fill: parent
                    source:"../icons/A01-RECEPE.png"
                    fillMode: Image.Stretch
                }

                onClicked: root.showRecepeWin()
            }
        }
        ButtonImage{
            id:nextRecepe
            imgNormal: "../icons/A01-NEXT.png"
            imgPressed: "../icons/A01-NEXTA.png"
            width: 125
            height:125
            onDeactivated: root.nextR();
        }
    }
}
