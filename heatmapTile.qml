import QtQuick
import cpp.GameGridController
import cpp.StateController
import cpp.HeatmapController

Item{
    id: root
    required property color baseColor
    required property int size
    required property int rowNum
    required property int colNum
    width: size
    height: size


    Connections{
        target: HeatmapController
        function onUpdatedMap(){
            if(GameGridController.isHit(rowNum, colNum) || GameGridController.isMiss(rowNum, colNum)){
                baseColor = Qt.darker("darkgray")
            }
            else {
                baseColor = HeatmapController.tileColor(rowNum, colNum)
            }
        }
    }


    Rectangle {
        id: box
        anchors.fill: parent
        color: baseColor
    }
}
