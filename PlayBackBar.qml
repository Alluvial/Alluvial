import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import Alluvial.Globals 1.0
import QtMultimedia 5.4

ColumnLayout {
    width: parent.width
    height: 100
    x: 0
    y: parent.height - 100
    Layout.fillHeight: true
    Layout.minimumHeight: 80
    Layout.maximumHeight: 100

    QtObject {
        id: activeSongMeta
        objectName: "activeSongMeta"
        property string hash: '#0'
        property string songName: "Shake it off"
        property string album: "1989"
        property string albumArt: "rawr.jpg"
        property string artist: "Taylor Swift"
        property int length: 100
        property double size: 1024
    }

    Rectangle {
        id: playbackBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        color: "#607D8B"

        RowLayout {
            id: sliderRow
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.05
            anchors.right: parent.right
            anchors.rightMargin: parent.width * 0.05
            anchors.top: parent.top
            height: parent.height * 0.5

            Timer {
                id: timer
                interval: 1000
                repeat: true
                triggeredOnStart: false
                onTriggered: {
                    if (playbackSlider.value >= playbackSlider.maximumValue)
                    {
                        timer.stop
                        playButton.state == 'pause'
                    }
                    else
                    {
                        playbackSlider.value += 1
                    }
                }
            }

            Slider {
                objectName: "playbackSlider"
                id: playbackSlider
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                stepSize: 1
                tickmarksEnabled: false
                updateValueWhileDragging: false

                signal playbackPosChanged(int val);

                onValueChanged: {
                    playbackSlider.playbackPosChanged(playbackSlider.value*1000)

                    if (playbackSlider.value >= playbackSlider.maximumValue)
                    {
                        playButton.state = 'pause'
                    }
                }

            }

            Item {
                id: statusBar
                objectName: "statusBar"
                anchors.left: playbackSlider.left
                anchors.right: playbackSlider.right
                anchors.top: playbackSlider.bottom
                anchors.bottom: parent.bottom

                Label {
                    id: songStart
                    text: "0:00"
                    anchors.left: parent.left
                }

                Label {
                    id: songPosition
                    text: {
                        if (playbackSlider.value % 60 < 10)
                        {
                            Math.floor(playbackSlider.value / 60).toString() + ':0' + Math.floor(playbackSlider.value % 60).toString()
                        }
                        else
                        {
                            Math.floor(playbackSlider.value / 60).toString() + ':' + Math.floor(playbackSlider.value % 60).toString()
                        }
                    }

                    anchors.centerIn: parent
                }

                Label {
                    objectName: "songEnd"
                    id: songEnd
                    anchors.right: parent.right

                    onTextChanged: {
                        console.log("SongEnd Text = " + songEnd.text)
                    }
                }
            }
        }

        RowLayout {
            id: buttonsRow
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.05
            anchors.right: parent.right
            anchors.rightMargin: parent.width * 0.05
            anchors.bottom: parent.bottom
            height: parent.height * 0.5

            RowLayout {
                id: playbackOptions
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.05
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width * 0.3

                ToolButton {
                    objectName: "shuffleButton"
                    id: shuffleButton
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width * 0.05
                    y: (parent.height - this.height) / 2
                    text: "SHF"
                    state: "released"

                    onClicked: {
                        changeButtonState()
                    }

                    states: [
                        State {
                            name: "pressed"
                            PropertyChanges {
                                target: shuffleButton
                                iconName: "pressed_shuffle"
                                iconSource: "icons/pressed_shuffle.png"
                            }
                        },
                        State {
                            name: "released"
                            PropertyChanges {
                                target: shuffleButton
                                iconName: "released_shuffle"
                                iconSource: "icons/shuffle.png"
                            }
                        }
                    ]

                    function changeButtonState() {
                        if (state == "pressed")
                        {
                            state = "released"
                        }
                        else
                        {
                            state = "pressed"
                        }
                    }
                }

                ToolButton {
                    objectName: "repeatButton"
                    id: repeatButton
                    anchors.right: parent.right
                    anchors.rightMargin: parent.width * 0.05
                    y: (parent.height - this.height) / 2
                    width: parent.width * 0.4
                    text: "RPT"
                    state: "released"

                    onClicked: {
                        changeButtonState()
                    }

                    states: [
                        State {
                            name: "pressed"
                            PropertyChanges {
                                target: repeatButton
                                iconName: "pressed_repeat"
                                iconSource: "icons/pressed_repeat.png"
                            }
                        },
                        State {
                            name: "released"
                            PropertyChanges {
                                target: repeatButton
                                iconName: "released_repeat"
                                iconSource: "icons/repeat.png"
                            }
                        }

                    ]

                    function changeButtonState() {
                        if (state == "pressed")
                        {
                            state = "released"
                        }
                        else
                        {
                            state = "pressed"
                        }
                    }
                }

            }

            RowLayout {
                id: mediaOptions
                anchors.centerIn: parent
                Layout.fillWidth: true
                Layout.minimumWidth: 160
                Layout.maximumWidth: 160

                Button {
                    objectName: "leftSkipButton"
                    id: leftSkipButton
                    x: parent.width * 0.05
                    y: (parent.height - this.height) / 2
                    width: parent.width * 0.12
                    iconName: "skip_left"
                    iconSource: "icons/previous.png"
                }

                Button {
                    objectName: "rewindButton"
                    id: rewindButton
                    x: parent.width * 0.21
                    y: (parent.height - this.height) / 2
                    width: parent.width * 0.12
                    iconName: "rewind"
                    iconSource: "icons/player_start.png"
                }

                Button {
                    id: playButton
                    objectName: "playButton"
                    x: parent.width * 0.375
                    y: (parent.height - this.height) / 2
                    width: parent.width * 0.25
                    state: "play"

                    signal qmlSig(string msg);
                    signal playClicked();

                    onClicked: {
                        playButton.playClicked();
                        playButton.qmlSig("RAWR I'M A BALLOON");

                        if (playbackSlider.value >= playbackSlider.maximumValue)
                        {
                            playButton.state = 'pause'
                        }
                        else
                        {
                            changePausedState()
                        }
                    }

                    function changePausedState() {
                        if (state == "pause")
                        {
                            state = "play"
                        }
                        else
                        {
                            state = "pause"
                        }
                    }

                    states: [
                        State {
                            name: "pause"
                            PropertyChanges {
                                target: playButton
                                iconName: "play"
                                iconSource: "icons/player_play.png"
                            }
                            PropertyChanges {
                                target: timer
                                running: false
                            }
                        },
                        State {
                            name: "play"
                            PropertyChanges {
                                target: playButton
                                iconName: "pause"
                                iconSource: "icons/player_pause.png"
                            }
                            PropertyChanges {
                                target: timer
                                running: true
                            }
                        }
                    ]
                }

                Button {
                    objectName: "fastForwardButton"
                    id: fastForwardButton
                    x: parent.width * 0.67
                    y: (parent.height - this.height) / 2
                    width: parent.width * 0.12
                    iconName: "fast_forward"
                    iconSource: "icons/player_fwd.png"

                    signal heldDown();

                }

                Button {
                    objectName: "rightSkipButton"
                    id: rightSkipButton
                    x: parent.width * 0.83
                    y: (parent.height - this.height) / 2
                    width: parent.width * 0.12
                    iconName: "skip_track"
                    iconSource: "icons/next_track.png"
                }
            }

            RowLayout {
                id: volumeOptions
                anchors.right: parent.right
                anchors.rightMargin: parent.width * 0.05
                anchors.top: parent.top
                anchors.bottom: parent.bottom

                Slider {
                    objectName: "volumeSlider"
                    id: volumeSlider
                    anchors.right: parent.right
                    width: 10
                    minimumValue: 0
                    maximumValue: 100
                    stepSize: 1
                    signal changeVol(int val)

                    onValueChanged: {
                        volumeSlider.changeVol(volumeSlider.value)
                    }
                }

            }
        }
    }
}
