import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Templates 2.2 as T

Button {
    property string imgNormal: ""
    property string imgPressed: ""

    Image{
        id:img
        //anchors.horizontalCenter: parent.horizontalCenter
        //anchors.verticalCenter: parent.verticalCenter
        source: imgNormal
        anchors.fill: parent
        fillMode: Image.Stretch
    }

//    background:{
//        color:"transparent"
//    }

    MouseArea{
        anchors.fill: parent
        onPressed: {
            img.source=imgPressed
        }
        onReleased: {
            img.source=imgNormal
        }
    }
}
