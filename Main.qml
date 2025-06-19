import QtQuick
import QtQuick.Window

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Grid{
        rows: 8
        columns: 8
        spacing: 2
        anchors{
            fill: parent
            margins: 10
        }
        Repeater {
                model: 64
                Tile{
                    required property int index
                    baseColor:"lightgray"
                    size: 40
                    colNum: index%8
                    rowNum: index/8
                }
            }
    }


}
