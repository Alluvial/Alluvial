import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtMultimedia 5.0

ColumnLayout {

    id: playlistPanel
    x: parent.width * 0.8
    y: 0
    width: parent.width * 0.2
    height: parent.height
    Layout.fillWidth: true
    Layout.minimumWidth: 100
    Layout.fillHeight: true
    Layout.minimumHeight: parent.height

    Rectangle {
        width: parent.width
        height: parent.height
        x: 0
        y: 0
        color: '#E0E0E0'
        Layout.fillWidth: true
        Layout.minimumWidth: 100
        Layout.fillHeight: true
        Layout.minimumHeight: parent.height

        ComboBox {
            id: dropdownPlaylistOptions
            width: parent.width
            x:0
            y:0

            onCurrentIndexChanged: {
                console.log ("Playlist changed: " + playlistOptions.get(currentIndex).name)
            }

            ListModel {
                id: playlistOptions

                ListElement {
                    name: "Playlist 1"
                }

                ListElement {
                    name: "Playlist 2"
                }

                ListElement {
                    name: "Playlist 3"
                }

                ListElement {
                    name: "Playlist 4"
                }
            }

            model: playlistOptions
        }

        Rectangle {
            x: 10
            y: dropdownPlaylistOptions.height + 5
            width: parent.width
            height: parent.height
            color: "transparent"

            Layout.fillWidth: true
            Layout.minimumWidth: playListPanel.width
            Layout.fillHeight: true
            Layout.minimumHeight: playListPanel.height

            ListModel {
                id: trackListing

                ListElement {
                    name: "Song 1"
                }
                ListElement {
                    name: "Song 2"
                }
                ListElement {
                    name: "Song 3"
                }
                ListElement {
                    name: "Song 4"
                }
            }

            Component {
                id: track
                Item {
                    height: 20
                    width: parent.width
                    MouseArea {
                        anchors.fill: parent
                        onDoubleClicked: {
                            mainWindow.state = "showItemDetailView"
                            console.log("Song clicked from playlist pane: " + name)
                        }
                    }

                    Text {
                        text: '• ' + name
                    }
                }
            }

            ListView {
                anchors.fill: parent
                model: trackListing
                delegate: track
            }
        }
    }
}
