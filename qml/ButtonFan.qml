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
    Canvas{
        id: cv
        property bool pressed: false
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();
            var centreX = width/2;
            var centreY = height/2;
            var sz = height/2

            ctx.strokeStyle = pressed?"red":"blue";
            ctx.fillStyle = pressed?fillPressed:fillNormal;
            ctx.lineWidth = 3;

            ctx.beginPath();
            ctx.moveTo(centreX,centreY);
            ctx.arc(centreX, centreY, width*0.1, 0, 2 * Math.PI);

            ctx.moveTo(centreX+10,centreY+10);
            ctx.lineTo(centreX+20,centreY+20);

            ctx.moveTo(centreX-10,centreY+10);
            ctx.lineTo(centreX-20,centreY+20);

            ctx.moveTo(centreX,centreY-15);
            ctx.lineTo(centreX,centreY-25);
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
