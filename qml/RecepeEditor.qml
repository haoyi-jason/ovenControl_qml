import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQml 2.2
//import "../qml" as GI

Rectangle{
    id:root
    property int uh: 0
    property int lh: 0
    property int baketime: 0
    property string imgurl: ""
    property string caption: ""
    property int s1_time: 0
    property int s1_quantity: 0
    property int s2_time: 0
    property int s2_quantity: 0
    property int v1_on: 0
    property int v1_off: 0
    property int v2_on: 0
    property int v2_off: 0
    width: parent.width
    height: parent.height
    signal selected()
    signal selectImage()
    color: "transparent"
    Row{
        spacing: 1
        width:80
        height: parent.height
        ButtonImage{
            id:btn
            width: 40
            height:parent.height*0.8
            imgNormal: "../icons/A01-SELECT.png"
            onDeactivated: root.selected()
        }

        Column{
            width: 240
            height: parent.height
            TextInput {
                id: recepeName
                height:40
                width: parent.width
                font.pixelSize: 29
                font.bold: true
                font.family: "NotoSansTC-Bold"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: qsTr(caption)
                color:"#92F7FD"

                anchors.horizontalCenter: parent.horizontalCenter
            }
            ButtonImage{
                id:img
                width: parent.width
                height:parent.height-recepeName.height
                //fillMode: Image.PreserveAspectFit
                imgNormal:root.imgurl
                onDeactivated: root.selectImage()
            }
        }
        Column{
            width: 300
            height: parent.height
            spacing: 2
            LabelText{
                width: parent.width
                height: 32
                caption: "Time(min)"
                content: Number(baketime).toLocaleString()
            }
            LabelText2{
                width: parent.width
                height: 32
                caption: "Heater U/L"
                v1:uh
                v2:lh
            }
            LabelText2{
                width: parent.width
                height: 32
                caption: "S1 T/Q"
                v1:s1_time
                v2:s1_quantity
            }
            LabelText2{
                width: parent.width
                height: 32
                caption: "S2 T/Q"
                v1:s2_time
                v2:s2_quantity
            }
            LabelText2{
                width: parent.width
                height: 32
                caption: "V1 ON/OFF"
                v1:v1_on
                v2:v1_off
            }
            LabelText2{
                width: parent.width
                height: 32
                caption: "V2 ON/OFF"
                v1:v2_on
                v2:v2_off
            }
        }
    }
}
