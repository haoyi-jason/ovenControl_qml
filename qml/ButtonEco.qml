import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Templates 2.2 as T

Button {
    property string color1: "#bbffff"
    property string color2: "#00c0f5"
    property string fillNormal: "white"
    property string fillPressed: "red"
    property bool running: false
    background: Rectangle{
        gradient: Gradient {
            GradientStop {
                position: 0
                color: color1
            }
            GradientStop {
                position: 0.6
                color: color2
            }
        }
        border.width:height * 0.02
        border.color:"gray"
        radius:height / 5
    }
    Image {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        id: name
        source: "../icons/Steam.png"
    }
    Canvas{
        id: cv
        property bool pressed: false
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d");
            //ctx.reset();
            var centreX = width/2;
            var centreY = height/2;
            ctx.moveTo(0,0);
            ctx.fillStyle= cv.pressed?"red":"white";
            ctx.font.pixelSize=36;
            ctx.fillText("ECO",centreX,centreY);
            ctx.stroke();
        }
        MouseArea{
            anchors.fill: parent
            onReleased: {
                cv.pressed=false
                cv.requestPaint()
            }

            onPressed: {
                cv.pressed=true
                cv.requestPaint()
            }
        }
    }
}
