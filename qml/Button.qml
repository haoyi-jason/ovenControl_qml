import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Templates 2.2 as T

Button {
    background: Rectangle{
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#bbffffff"
            }
            GradientStop {
                position: 0.6
                color: "#00c0f5"
            }
        }
        border.width:height * 0.05
        border.color:"gray"
        radius:height / 5
    }

    //display: AbstractButton.IconOnly
//    contentItem: Text {
//        text: control.text
//        font: control.font
//        opacity: enabled ? 1.0 : 0.3
//        color: control.down ? "#17a81a" : "#21be2b"
//        horizontalAlignment: Text.AlignHCenter
//        verticalAlignment: Text.AlignVCenter
//        elide: Text.ElideRight

//    }

//    background: Rectangle {
//        implicitWidth: 100
//        implicitHeight: 40
//        opacity: enabled ? 1 : 0.3
//        border.color: control.down ? "#17a81a" : "#21be2b"
//        border.width: 1
//        radius: 2
//    }
}
