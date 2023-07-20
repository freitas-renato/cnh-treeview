import QtQuick 2.4
import QtQuick.Window
import QtQuick.Controls

import cnh.treeview 1.0

ApplicationWindow {
    width: 800
    height: 500
    minimumWidth: 400
    minimumHeight: 400
    visible: true
    title: qsTr("CNH Tree View")

    color: "#FFFFFF"

    Rectangle {
        id: headerArea
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 30
        color: "lightgray"
        clip: true
        z: 2

        Text {
            id: title
            text: qsTr("Controls Test")
            font.pixelSize: 18
            anchors.centerIn: parent
            color: "black"
        }
    }


    TreeView {
        id: _treeView
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: headerArea.bottom
        anchors.margins: 5

        // QAbstractItemModel from C++ backend
        model: treeModel

        flickableDirection: Flickable.VerticalFlick

        delegate: Item {
            id: treeDelegate

            implicitWidth: padding + background.x + background.implicitWidth + padding
            implicitHeight: background.height

            readonly property real padding: 15
            required property TreeView treeView
            required property int hasChildren

            TapHandler { 
                onTapped: {
                    treeView.toggleExpanded(row)
                }
            }

            Rectangle {
                id: background
                width: label.width + indicator.width * 2 + icon.width + padding * 2
                height: padding * 3
                anchors.leftMargin: padding + model.item.indentation * 10
                anchors.left: parent.left
                color: "white"
                radius: 10

                Row {
                    spacing: treeDelegate.padding
                    anchors.verticalCenter: parent.verticalCenter

                    children: [
                        Image {
                            id: indicator
                            visible: treeDelegate.hasChildren
                            source: treeView.isExpanded(row) ? "qrc:/assets/minus.png" : "qrc:/assets/plus.png"
                        },

                        Item {
                            id: placeholder
                            visible: !treeDelegate.hasChildren
                            width: 32
                            height: 3
                        },

                        Image {
                            id: icon
                            source: model.item.icon
                        },

                        Text {
                            id: label
                            text: model.item.text
                            font.pixelSize: 18
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    ]
                }

                // Only active if the item is clickable
                MouseArea {
                    anchors.fill: background
                    cursorShape: Qt.PointingHandCursor
                    hoverEnabled: model.item.clickable
                    propagateComposedEvents: true
             
                    onClicked: {
                        console.log("Button clicked: " + model.item.text)
                        treeView.toggleExpanded(row)
                    }

                    enabled: model.item.clickable
                    visible: model.item.clickable
                }
            }
        }
    }  // TreeView
}
