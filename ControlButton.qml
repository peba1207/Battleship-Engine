import QtQuick

Rectangle{
    id:root
    property alias text: textbox.text
    height:50
    property color baseColor: "gray"
    signal clicked()

    color: if(mouseArea.containsPress){
                Qt.darker(baseColor)
           } else if(mouseArea.containsMouse)
           {
               Qt.darker(baseColor, 1.5)
           } else {
               baseColor
           }

    Text{
        id: textbox
        anchors.centerIn: parent
        color: "white"
        font{
            pointSize: 16
            bold: false
        }

    }

    MouseArea{
        id: mouseArea
        anchors.fill: parent

        hoverEnabled: true

        onClicked: {
            root.clicked()
        }
    }
}
