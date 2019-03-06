import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQml 2.2


Rectangle{
    property int uh
    width:parent.width
    height: 320
    SwipeView{
        y:50
        id: recepeView
        currentIndex: indicator.currentIndex
        anchors.fill: parent
        //orientation: Qt.Vertical
        clip:true
        height: 480
        Item{
            Text {
                id: txt_uh
                x: 20
                y: 20
                width: 200
                height: 100
                color: (uh > 100)?"red":"blue"
                text: "222"
                font.wordSpacing: 1.2
                font.letterSpacing: 1
                style: Text.Raised
                font.weight: Font.Bold
                font.family: "Verdana"
                font.bold: true
                fontSizeMode: Text.Fit
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 48
            }
            Text {
                id: txt_time
                x: 20
                y: 120
                width: 200
                height: 100
                color: (uh > 100)?"red":"blue"
                text: "015"
                font.wordSpacing: 1.2
                font.letterSpacing: 1
                style: Text.Raised
                font.weight: Font.Bold
                font.family: "Verdana"
                font.bold: true
                fontSizeMode: Text.Fit
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 48
            }
            Text {
                id: txt_lh
                x: 20
                y: 220
                width: 200
                height: 100
                color: (uh > 100)?"red":"blue"
                text: "333"
                font.wordSpacing: 1.2
                font.letterSpacing: 1
                style: Text.Raised
                font.weight: Font.Bold
                font.family: "Verdana"
                font.bold: true
                fontSizeMode: Text.Fit
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 48
            }
            Image{
                x: 250
                y:50
                width:300
                height:300
                source:"../image/bread-1284438__340.jpg"
            }
        }
        Item{
            Image{
                x: 200
                width:200
                height:200
                source:"../image/bread-1238384__340.jpg"
            }
        }

        PageIndicator{
            id: indicator
            count:recepeView.count
            currentIndex: recepeView.currentIndex
            //anchors.bottom: recepeView.bottom
        }
    }

}
