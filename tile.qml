import QtQuick
import cpp.GameGridController
Item{
    id: root
    required property color baseColor
    required property int size
    required property int rowNum
    required property int colNum
    property bool selected: GameGridController.selectedCol === colNum && GameGridController.selectedRow === rowNum
    width: size
    height: size


    Rectangle {
        anchors.fill: parent

        color: if(selected){
                   Qt.darker(baseColor)
               } else if(mouseArea.containsMouse)
               {
                   Qt.darker(baseColor, 1.5)
               } else {
                   baseColor
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
