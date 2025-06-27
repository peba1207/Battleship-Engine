import QtQuick
import cpp.GameGridController
import cpp.StateController
import cpp.InformationMapController

Item{
    id: root
    required property color baseColor
    required property int size
    required property int rowNum
    required property int colNum
    width: size
    height: size
    Connections{
        target: InformationMapController
        function onUpdatedMap(){
            if(GameGridController.isHit(rowNum, colNum) || GameGridController.isMiss(rowNum, colNum)){
                baseColor = Qt.darker("darkgray")
                img.visible = false
                txt.text = ""
            }
            else {
                baseColor = InformationMapController.tileColor(rowNum, colNum)
                img.visible = InformationMapController.isBestMove(rowNum,colNum)
                txt.text = InformationMapController.getExpectedInfoGain(rowNum,colNum)
            }
        }
    }


    Rectangle {
        id: box
        anchors.fill: parent
        color: baseColor
        Image {
            id: img
            source: "images/star.png"
            visible: false
            anchors{
                fill: parent
                margins: 10
            }
        }
        Text{
            id: txt
            text: ""

            font.pointSize: 6
        }
    }
}
