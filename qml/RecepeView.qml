import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQml 2.2
//import "../qml" as GI

Column{
    property int uh: 0
    property int lh: 0
    property int baketime: 0
    //color: "transparent"
    //Rectangle{
        //color: ""
//    opacity: 0
        //anchors.fill: parent
        Text {
            id: caption
            text: qsTr("Current Recepe")
            height:100
        }
        Row{
            spacing: 10
            //height:320
            //y:80
                //id:values
            Column{
                width:240
                //height:320
                spacing: 0
                ImageEdit{
                    color: "transparent"
                    height:120
                    width: parent.width
                    image:"../icons/oh_low.png"
                    content: "250"
                }
                ImageEdit{
                    color: "transparent"
                    height:120
                    width: parent.width
                    image:"../icons/time_bake.png"
                    content: "180"
                }
                ImageEdit{
                    color: "transparent"
                    height:120
                    width: parent.width
                    image:"../icons/lh_low.png"
                    content: "180"
                }
            }
            Image{
                width:240
                height:320
                fillMode: Image.PreserveAspectFit
                source:"../image/bread-1284438__340.jpg"
            }
        }
    //}
}
