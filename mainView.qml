import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.VirtualKeyboard 2.2

import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls 2.2
import "./qml" as GI
import Qt.labs.calendar 1.0
import QtQuick.Controls.Styles 1.2

Window {
    id: window
    visible: true
    width: 600
    height: 1024
    title: qsTr("Oven Controller")
    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: window.height
        width: window.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: window.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }

    SwipeView{
        id: view
        width: 600
        height: 1024
        anchors.bottomMargin: 0
        currentIndex: 3
        anchors.fill: parent
        Page{
            Rectangle{
//                background: "green"
                color:"#444444"
                anchors.fill: parent
                GI.ManualBar{
                    y:10
                    height:120
                }

                Row{
                    id:r1
                    property int icon_w: 120
                    property int icon_h: 120
                    y:50
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    GI.ButtonImage{
                        id:bn_light
                        imgNormal: "../icons/power_normal.png"
                        imgPressed: "../icons/power_pressed.png"
                        width: r1.icon_w
                        height:r1.icon_h
                        onClicked: {
                            oven.light(!bn_light.state)
                        }
                    }

                    GI.ButtonImage{
                        imgNormal: "../icons/eco_normal.png"
                        imgPressed: "../icons/eco_pressed.png"
                        width: r1.icon_w
                        height:r1.icon_h
                    }

                    GI.ButtonImage{
                        imgNormal: "../icons/go_normal.png"
                        imgPressed: "../icons/go_pressed.png"
                        width: r1.icon_w
                        height:r1.icon_h
                    }
                    GI.ButtonImage{
                        imgNormal: "../icons/go_normal.png"
                        imgPressed: "../icons/go_pressed.png"
                        width: r1.icon_w
                        height:r1.icon_h
                    }
                }
                Row{
                    id:r2
                    property int icon_w: 120
                    property int icon_h: 120
                    y:210
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    GI.ButtonImage{
                        imgNormal: "../icons/light_normal.png"
                        imgPressed: "../icons/light_normal.png"
                        width: r2.icon_w
                        height:r2.icon_h
                    }

                    GI.ButtonImage{
                        imgNormal: "../icons/fan_normal.png"
                        imgPressed: "../icons/fan_normal.png"
                        width: r2.icon_w
                        height:r2.icon_h
                    }

                    GI.ButtonImage{
                        imgNormal: "../icons/steam_normal.png"
                        imgPressed: "../icons/steam_pressed.png"
                        width: r2.icon_w
                        height:r2.icon_h
                    }
                    GI.ButtonImage{
                        imgNormal: "../icons/valve_normal.png"
                        imgPressed: "../icons/valve_open.png"
                        width: r2.icon_w
                        height:r2.icon_h
                    }
                }

                Row{
                    y:350
                    height: 80
                    width: parent.width*0.9
                    spacing: 50

                    //anchors.fill: parent
                    anchors.horizontalCenter: parent.horizontalCenter
                    GI.ImageText{
                        height:parent.height
                        image:"../icons/oh_low.png"
                        content: "180/220"
                    }
                    GI.ImageText{
                        height:parent.height
                        x:parent.width/2
                        image:"../icons/timer_run.png"
                        content: "20 min"
                    }
                }
                Row{
                    y:450
                    width: parent.width*0.9
                    spacing: 50
                    height: 80
                    anchors.horizontalCenter: parent.horizontalCenter
                    GI.ImageText{
                        height:parent.height
                        image:"../icons/lh_low.png"
                        content: "180/220"
                    }
                    GI.ImageText{
                        height:parent.height
                        x:parent.width/2
                        image:"../icons/time_finished.png"
                        content: "16:55"
                    }
                }
                GI.RecepeView{
                    //x:0
                    //y:200
                    height:480
                    width: parent.width*0.9
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    //anchors.fill: parent
                }
            }

        }
        Page{
            id:recepeEdit
            Rectangle{
                GI.RecepeView{

                }
            }
        }

        Page{
            id: testpanel
            Connections{
                target:oven
                onUpdateRelay:{
                    sw_relay.itemAt(id).checked = oven.relay(id)
                }
            }

            //Rectangle{
                Row{
                    x:0
                    y:0
                    height:200
                    Repeater{
                        id:sw_relay
                        model:9
                        Switch{
                            checked: oven.relay(index)
                            onClicked: {
                                oven.setRelay(index,checked?1:0)
                            }
                        }
                    }
                }
                Text{
                    x:0
                    y:200
                    width:100
                    height:50
                    text:oven.activeRecepe.oh
                }
                TextInput{
                    id:tid
                    x:0
                    y:250
                    width:100
                    height:50
                    text:oven.activeRecepe.oh
                    onEditingFinished: {
                        var obj = oven.activeRecepe
                        console.log(obj)
                        obj.oh = tid.text
                        oven.activeRecepe = obj
                        console.log("UH:"+tid.text)
                    }
                }
            //}
        }
    }

    PageIndicator{
        id: pageindicator
        anchors.bottom: view.bottom
        anchors.bottomMargin: 10
        anchors.horizontalCenter: view.horizontalCenter
        count: view.count
        currentIndex: view.currentIndex
    }

    Popup{
        id:pop_confirm
        x:100
        y:100
        width:200
        height:200
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent


    }

    Dialog{
        id: dialog
        title: "Title"
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel

        onAccepted: console.log("Ok clicked")
        onRejected: console.log("Cancel clicked")
    }

}

