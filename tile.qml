import QtQuick
import cpp.GameGridController
import cpp.StateController

Item{
    id: root
    required property color baseColor
    required property int size
    required property int rowNum
    required property int colNum
    property bool selected: GameGridController.selectedCol === colNum && GameGridController.selectedRow === rowNum
    width: size
    height: size


    Connections{
        target: StateController
        function onStateChanged(){
            if(GameGridController.isHit(rowNum, colNum)){
                baseColor = "pink"
                img.source = "images/explosion.png"
            }else if(GameGridController.isMiss(rowNum, colNum)){
                baseColor = "lightblue"
                img.source = "images/x.png"

            } else {
                baseColor = "lightgray"
                img.source = ""
            }
        }
    }

    Rectangle {
        id: box
        anchors.fill: parent

        color: if(selected){
                   Qt.darker(baseColor)
               } else if(mouseArea.containsMouse)
               {
                   Qt.darker(baseColor, 1.5)
               } else {
                   baseColor
               }
        Image {
            id: img
            anchors{
                fill: parent
                margins: 5
            }

        }
    }

    MouseArea{
        id: mouseArea
        anchors.fill: parent

        hoverEnabled: true

        onClicked: {
            GameGridController.selectedCol = colNum
            GameGridController.selectedRow = rowNum

        }
    }


}
