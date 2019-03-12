import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQml 2.2
//import "../qml" as GI

ListView{
    property int uh: 0
    property int lh: 0
    property int baketime: 0
    property string imgurl: ""
    id: listview
    model:ListModel{
        ListElement { sender: "Bob Bobbleton"; title: "How are you going?" }
        ListElement { sender: "Rug Emporium"; title: "SALE! All rugs MUST go!" }
        ListElement { sender: "Electric Co."; title: "Electricity bill 15/07/2016 overdue" }
        ListElement { sender: "Tips"; title: "Five ways this tip will save your life" }
        ListElement { sender: "Bob Bobbleton"; title: "How are you going?" }
        ListElement { sender: "Rug Emporium"; title: "SALE! All rugs MUST go!" }
        ListElement { sender: "Electric Co."; title: "Electricity bill 15/07/2016 overdue" }
        ListElement { sender: "Tips"; title: "Five ways this tip will save your life" }
        ListElement { sender: "Bob Bobbleton"; title: "How are you going?" }
        ListElement { sender: "Rug Emporium"; title: "SALE! All rugs MUST go!" }
        ListElement { sender: "Electric Co."; title: "Electricity bill 15/07/2016 overdue" }
        ListElement { sender: "Tips"; title: "Five ways this tip will save your life" }
    }
    snapMode: listview.SnapOneItem
    cacheBuffer:0
    delegate: SwipeDelegate{
        id:swipeDelegate
        text:model.sender
        width: parent.width
        height:200
//        ListView.onRemove: SequentialAnimation {
//            PropertyAction {
//                target: swipeDelegate
//                property: "ListView.delayRemove"
//                value: true
//            }
//            NumberAnimation {
//                target: swipeDelegate
//                property: "height"
//                to: 0
//                easing.type: Easing.InOutQuad
//            }
//            PropertyAction {
//                target: swipeDelegate
//                property: "ListView.delayRemove"
//                value: false
//            }
//        }
        swipe.right: Label {
            id: deleteLabel
            text: qsTr("Delete")
            color: "white"
            verticalAlignment: Label.AlignVCenter
            padding: 12
            height: parent.height
            anchors.right: parent.right

            SwipeDelegate.onClicked: listView.model.remove(index)

            background: Rectangle {
                color: deleteLabel.SwipeDelegate.pressed ? Qt.darker("tomato", 1.1) : "tomato"
            }
        }
    }


}
