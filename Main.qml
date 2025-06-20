import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import cpp.StateController
import cpp.GameGridController
import cpp.HeatmapController

Window {
    width: 1000
    height: 720
    visible: true
    title: qsTr("Hello World")
    Text{
        id: title
        text: "Battleship tools"
    }
    Rectangle{
        id: game
        width: 376
        anchors{
            top: title.bottom
            bottom:parent.bottom
            margins: 10
            left: parent.left
        }

        color: "gray"

        Rectangle{
            id: gridbox
            color: "black"
            anchors{
                centerIn: parent
                margins: 10
            }
            width:356
            height:356

            Grid {
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

        Rectangle{
            anchors {
                top: gridbox.bottom
                bottom: parent.bottom
                left: parent.left
                right:parent.right
                margins: 20
            }
            color: "white"
            RowLayout{
                anchors{
                    centerIn: parent
                    fill: parent
                    margins: 10
                }
                ControlButton{
                    Layout.fillWidth: true
                    text: "hit"
                    onClicked: StateController.setHit(GameGridController.selectedRow, GameGridController.selectedCol)
                }
                ControlButton{
                    Layout.fillWidth: true
                    text: "miss"
                    onClicked: StateController.setEmpty(GameGridController.selectedRow, GameGridController.selectedCol)
                }

                ControlButton{
                    Layout.fillWidth: true
                    text: "clear"
                    onClicked: StateController.clearTile(GameGridController.selectedRow, GameGridController.selectedCol)
                }
            }
        }
    }


    Rectangle{
        id: heatmapZone
        width: 376
        anchors{
            top: title.bottom
            bottom:parent.bottom
            margins: 10
            left: game.right
        }

        color: "gray"

        Rectangle{
            id: heatmapBox
            color: "black"
            anchors{
                centerIn: parent
                margins: 10
            }
            width:356
            height:356

            Grid {
                rows: 8
                columns: 8
                spacing: 2
                anchors{
                    fill: parent
                    margins: 10
                }
                Repeater {
                    model: 64
                    HeatmapTile{
                        required property int index
                        baseColor:"lightgray"
                        size: 40
                        colNum: index%8
                        rowNum: index/8
                    }
                }
            }
        }

        Rectangle{
            anchors {
                top: heatmapBox.bottom
                bottom: parent.bottom
                left: parent.left
                right:parent.right
                margins: 20
            }
            color: "white"
            RowLayout{
                anchors{
                    centerIn: parent
                    fill: parent
                    margins: 10
                }
                ControlButton{
                    Layout.fillWidth: true
                    text: "Generate Heatmap"
                    onClicked: HeatmapController.updateMap()
                }
            }
        }
    }
}
