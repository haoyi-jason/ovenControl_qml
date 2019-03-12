import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.VirtualKeyboard 2.2

import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.2
import "./qml" as GI
import Qt.labs.calendar 1.0
import QtQuick.Controls.Styles 1.0

import Qt.labs.folderlistmodel 2.2

Window {
    id: window
    visible: true
    width: 1024
    height: 600
    title: qsTr("Oven Controller")
    color: "black"
    Rectangle{
        id:rec
        color: "#444444"
        width:600
        height:1024
        x:(window.width-rec.width)/2
        y:(window.height-rec.height)/2
        //anchors.horizontalCenter:window.width/2
        //anchors.verticalCenter:window.height/2
        //transformOrigin: window.Center
        rotation:90
        InputPanel {
            id: inputPanel
            z: 99
            x: 0
            y: rec.height
            width: rec.width

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
        currentIndex: 0
        anchors.fill: parent
        property int icon_w: 125
        property int icon_h: 125
        Page{
            id:page1
            background: Rectangle{
                Image {
                    id: bg
                    source: "./icons/A01-BG2.png"
                    anchors.fill: parent
                    fillMode: Image.Stretch
                }
            }

            Rectangle{
                id:rrr
                x:20
                y:20
                width: parent.width-40
                height: 125
                color: "transparent"
                Text {
                    id: rtc
                    font.pixelSize: 60
                    font.bold: true
                    font.family: "NotoSansTC-Bold"
                    height: 62.5
                    color: "#92F7FD"
                    anchors.left: parent.left
                    anchors.top:parent.top
                    text: oven.rtc
                }

                GI.ButtonImage{
                    id:bn_setup
                    toggle: false
                    anchors.right: parent.right
                    imgNormal: "../icons/a01-util.png"
                    imgPressed: "../icons/a01-utila.png"
                    width: view.icon_w
                    height:view.icon_h
                    onActivated: {
                        imgurl = "../icons/a01-utila.png"
                        imgNormal = "../icons/a01-utila.png"
                    }
                    onDeactivated: {
                        imgurl = state?"../icons/a01-utila.png":"../icons/A01-UTIL.png"
                        imgNormal = state?"../icons/a01-utila.png":"../icons/A01-UTIL.png"
                        //view.currentIndex=1;
                        pop_confirm.open()

                    }
                }
            }
            Row{
                id:r1
                x:20
                y:165
                width: parent.width-40
                height: 125
                spacing: 20
                GI.ButtonImage{
                    id:bn_power
                    imgNormal: "../icons/A01-PWR.png"
                    imgPressed: "../icons/A01-PWRA.png"
                    width: view.icon_w
                    height:view.icon_h
                    toggle: false
                    onActivated: {
                        imgurl = "../icons/A01-PWRA.png"
                        imgNormal = imgurl
                    }
                    onDeactivated: {
                        oven.light(state)
                        imgurl=state?"../icons/A01-PWRA.png":"../icons/A01-PWR.png"
                        imgNormal=imgurl
                    }
                }

                GI.ButtonImage{
                    id:bn_eco
                    imgNormal: "../icons/A01-ECO.png"
                    imgPressed: "../icons/A01-ECOA.png"
                    width: view.icon_w
                    height:view.icon_h
                    toggle: true
                    onDeactivated: {

                        imgurl=state?"../icons/A01-ECOA.png":"../icons/A01-ECO.png"
                        imgNormal=imgurl
                    }
                }

                GI.ButtonImage{
                    id:bn_ast
                    imgNormal: "../icons/A01-AST.png"
                    imgPressed: "../icons/A01-ASTA.png"
                    width: view.icon_w
                    height:view.icon_h
                    toggle: false
                    onActivated: {
                        imgurl = "../icons/A01-ASTA.png"
                        imgNormal = imgurl
                    }
                    onDeactivated: {
                        imgurl=state?"../icons/A01-ASTA.png":"../icons/A01-AST.png"
                        imgNormal=imgurl
                    }
                }
                GI.ButtonImage{
                    id:bn_go
                    imgNormal: "../icons/A01-GO.png"
                    imgPressed: "../icons/A01-GOA.png"
                    width: view.icon_w
                    height:view.icon_h
                    toggle: true
                    onActivated: {
                        imgurl = "../icons/A01-GOA.png"
                        imgNormal = imgurl
                    }
                    onDeactivated: {
                        imgurl=state?"../icons/A01-GOA.png":"../icons/A01-GO.png"
                        imgNormal=imgurl
                    }
                }
            }
            Row{
                id:r2
                x:20
                y:310
                width: parent.width-40
                height: 125
                spacing: 20
                GI.ButtonImage{
                    id:bn_light
                    imgNormal: "../icons/A01-LIGHT.png"
                    imgPressed: "../icons/A01-LIGHTA.png"
                    width: view.icon_w
                    height:view.icon_h
                    toggle: true
                    onActivated: {
                        imgurl = "../icons/A01-LIGHTA.png"
                        imgNormal = imgurl
                    }
                    onDeactivated: {
                        imgurl=state?"../icons/A01-LIGHTA.png":"../icons/A01-LIGHT.png"
                        imgNormal=imgurl
                    }
                }

                GI.ButtonImage{
                    id:bn_fan
                    imgNormal: "../icons/A01-FAN.png"
                    imgPressed: "../icons/A01-FANA.png"
                    width: view.icon_w
                    height:view.icon_h
                    toggle: true
                    onActivated: {
                        imgurl = "../icons/A01-FANA.png"
                        imgNormal = imgurl
                    }
                    onDeactivated: {
                        imgurl=state?"../icons/A01-FAN.png":"../icons/A01-FANA.png"
                        imgNormal=imgurl
                    }
                }

                GI.ButtonImage{
                    id:bn_steam
                    imgNormal: "../icons/A01-STEAM.png"
                    imgPressed: "../icons/A01-STEAMA.png"
                    width: view.icon_w
                    height:view.icon_h
                    toggle: false
                    onActivated: {
                        imgurl = "../icons/A01-STEAMA.png"
                        imgNormal = imgurl
                    }
                    onDeactivated: {
                        imgurl=state?"../icons/A01-STEAMA.png":"../icons/A01-STEAM.png"
                        imgNormal=imgurl
                    }
                }
                GI.ButtonImage{
                    id:bn_valve
                    imgNormal: "../icons/A02-VALVE.png"
                    imgPressed: "../icons/A02-VALVEA.png"
                    width: view.icon_w
                    height:view.icon_h
                    toggle: true
                    onActivated: {
                        imgurl = "../icons/A02-VALVEA.png"
                        imgNormal = imgurl
                    }
                    onDeactivated: {
                        imgurl=state?"../icons/A02-VALVEA.png":"../icons/A02-VALVE.png"
                        imgNormal=imgurl
                    }
                }
            }

            Row{
                x:20
                y:455
                width: (parent.width-60)
                height: 62.5
                spacing: 20

                GI.TemperatureDisp{
                    color: "transparent"
                    id:ohdisp
                    width: parent.width/2
                    height:parent.height
                    //imgurl:"../icons/oh_low.png"
                    temp1:oven.ovenVars.uh
//                    temp2:oven.activeRecepe.uh
                    //temp2:oven.recepeModel.data(oven.recepeModel.index(oven.activeR,0),1).uhTemp
                    temp2:oven.actRecepe.uhTemp
                    celius: oven.celius
//                    Component.onCompleted: {
//                        console.log("ovenvars:",oven.ovenCfg.maxTemp)
//                    }
                }
                GI.TimeDisp{
                    id:runtime
                    color:"transparent"
                    width: parent.width/2
                    height:parent.height
                    //imgurl:"../icons/timer_run.png"
                    t1: oven.runTime
                    t2: ""
                }
            }
            Row{
                x:20
                y:537.5
                width: (parent.width-60)
                height: 62.5
                spacing: 20
                GI.TemperatureDisp{
                    id:lhdisp
                    color: "transparent"
                    width: parent.width/2
                    height:parent.height
                    //imgurl:"../icons/lh_low.png"
                    temp1:oven.ovenVars.lh
                    temp2:oven.actRecepe.lhTemp
                    celius: oven.celius
                }
                GI.TimeDisp{
                    color:"transparent"
                    width:parent.width/2
                    height: parent.height
                    //imgurl:"../icons/time_finished.png"
                    t1:oven.finishTime
                    t2:""
                }
            }

            GI.RecepeViewV2{
                id:rcpview
                anchors.horizontalCenter: parent.horizontalCenter
                x:20
                y:620
                height:384
                width: parent.width-40
                uh:oven.actRecepe.uhTemp
                lh:oven.actRecepe.lhTemp
                baketime: oven.actRecepe.bakeTime
                imgurl: oven.actRecepe.imgurl
                caption: "ID:"+oven.actRecepe.id + ":" + oven.actRecepe.name
                onNextR: oven.nextRecepe()
                onPrevR: oven.prevRecepe()
                onShowRecepeWin: view.currentIndex=1
            }
        }
        Page{
            id:recepeEdit
            background: Rectangle{
                Image {
                    id: bg2
                    source: "./icons/A01-BG.png"
                    anchors.fill: parent
                    fillMode: Image.Stretch
                }
            }
            ListView{
                id:rcpLst
                x:20
                y:20
                width: parent.width-40
                height: 700
                model:oven.recepeModel
                snapMode: ListView.SnapToItem
                delegate: GI.RecepeEditor{
                    width: recepeEdit.width
                    height:240
                    caption: edit.name
                    imgurl: edit.imgurl
                    uh:edit.uhTemp
                    lh:edit.lhTemp
                    baketime:edit.bakeTime
                    v1_on:edit.v1_on
                    v1_off:edit.v1_off
                    v2_on:edit.v2_on
                    v2_off:edit.v2_off
                    s1_time: edit.s1_time
                    s1_quantity: edit.s1_quantity
                    s2_time: edit.s2_time
                    s2_quantity: edit.s2_quantity

                    onSelectImage: console.log("Select Image")
                    onSelected: console.log("Select index:",index)
                }
            }
            Rectangle{
                anchors.horizontalCenter: rcpLst.horizontalCenter
                y:880
                width: parent.width-40
                height:150
                color: "transparent"
                Row{
                    leftPadding: 100
                    rightPadding: 100
                    spacing: 100
                    GI.ButtonImage{
                        id:bn_new
                        toggle: false
                        imgNormal: "../icons/A02-ADD.png"
                        imgPressed: "../icons/A02-ADDA.png"
                        width: view.icon_w
                        height:view.icon_h
                        onActivated: {
                            imgurl = "../icons/A02-ADDA.png"
                            imgNormal = "../icons/A02-ADDA.png"
                        }
                        onDeactivated: {
                            imgurl = state?"../icons/A02-ADDA.png":"../icons/A02-ADD.png"
                            imgNormal = state?"../icons/A02-ADDA.png":"../icons/A02-ADD.png"
                        }
                    }
                    GI.ButtonImage{
                        id:bn_remove
                        toggle: false
                        imgNormal: "../icons/A02-MINUS.png"
                        imgPressed: "../icons/A02-MINUSA.png"
                        width: view.icon_w
                        height:view.icon_h
                        onActivated: {
                            imgurl = "../icons/A02-MINUSA.png"
                            imgNormal = "../icons/A02-MINUSA.png"
                        }
                        onDeactivated: {
                            imgurl = state?"../icons/A02-MINUSA.png":"../icons/A02-MINUS.png"
                            imgNormal = state?"../icons/A02-MINUSA.png":"../icons/A02-MINUS.png"
                        }
                    }
                }
            }
        }

        Page{
            id: ovenSetting
            background: Rectangle{
                Image {
                    id: bg3
                    source: "./icons/A01-BG.png"
                    anchors.fill: parent
                    fillMode: Image.Stretch
                }
            }

//            Loader{
//                id:l1
//                source: "./parameter_edit.qml"
//            }
        }
        Page{
            id: testpanel
            background: Rectangle{
                Image {
                    id: bg4
                    source: "./icons/A01-BG.png"
                    anchors.fill: parent
                    fillMode: Image.Stretch
                }
            }
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
                    text:oven.activeRecepe.oh+oven.activeRecepe.imgurl
                }
                TextInput{
                    id:tid
                    x:0
                    y:250
                    width:100
                    height:50
                    text:oven.activeRecepe.uh
                    onEditingFinished: {
                        var obj = oven.activeRecepe
                        console.log(obj)
                        obj.oh = tid.text
                        oven.activeRecepe = obj
                        console.log("UH:"+tid.text)
                    }
                }

                ListView{
                    x:0
                    y:300
                    width: 500
                    height: 300
                    model:oven.recepeModel
                    delegate: TextInput{
                        id:tt
                        font.pixelSize: 60
                        color: "red"
                        text:Number(edit.uhTemp).toLocaleString()
//                        MouseArea{
//                            anchors.fill: parent
//                            onClicked: {
//                                tt.selectAll()
//                            }
//                        }

                        onEditingFinished: {
                            console.log("Set data to:",Number(tt.text))
                            edit.uhTemp=300
                            var model_index = oven.recepeModel.index(0,0)
                            //console.log("Model index:",model_index)
                            var ok=oven.recepeModel.setData(model_index,"300",1)
                            //var modelData = oven.recepeModel.data(model_index,1)
                            //console.log(modelData)
                            //modelData.setUhTemp(300)
                            console.log("data changed?",ok)
                        }
                    }


                }

                GridView{
                    x:0
                    y:600
                    width: parent.width
                    height: 300
                    FolderListModel{
                        id:imgModel
                        folder: "./image"
                        nameFilters: ["*.jpg"]
                    }

                    model:imgModel
                    delegate: Column{
                        Image{source:fileURL;width: 50;height: 50}
                        Text {text:fileName;color:"red"}

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

    Rectangle{

        transform: Rotation{
            angle: -90
        }

    Dialog{
        id:pop_confirm
        x:100
        y:500
        width:200
        height:200
        focus: true
        title: "TEST"
        standardButtons: StandardButton.Save | StandardButton.Cancel

        background: Rectangle{
            color:"yellow"
        }

        Text{
            text:"Hello"
            anchors.centerIn: parent
        }
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside


    }
    }
    Popup{
        id: dialog
        modal: true
        focus: true
        x:100
        y:500
        width: 300
        height: 300

        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    }
    }
}

