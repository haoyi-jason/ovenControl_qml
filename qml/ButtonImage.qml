import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Templates 2.2 as T
Rectangle{
    id:root
    property string imgNormal: ""
    property string imgPressed: ""
    property string imgurl: ""
    property bool toggle: false
    property bool active: false

    signal activated
    signal deactivated(bool state)

    color: "transparent"

    Button {
        anchors.fill: parent
        background: Rectangle{
            color:"transparent"
        }

        Image{
            id:img
            source: root.imgNormal
            anchors.fill: parent
            fillMode: Image.Stretch
        }

        MouseArea{
            anchors.fill: parent
            onPressed: {
                if(!root.toggle)
                    root.activated()
                //console.log("pressed")
            }
            onReleased: {
                if(root.toggle){
                    root.active = !root.active
                }
                root.deactivated(root.active)
               // console.log("released")
            }
        }

    }
}
