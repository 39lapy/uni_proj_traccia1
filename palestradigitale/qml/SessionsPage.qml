import QtQuick
import QtQuick.Controls

Page {
    property StackView stackView

    header: ToolBar {
        ToolButton {
            text: "← Indietro"
            onClicked: stackView.pop()
        }
    }

    Column {
        anchors.fill: parent
        spacing: 0

        // Log new session
        Rectangle {
            width: parent.width
            height: 180
            color: "#e8f5e9"

            Column {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 8

                Text {
                    text: "Registra Sessione"
                    font.pixelSize: 16
                    font.bold: true
                }

                ComboBox {
                    id: programPicker
                    width: parent.width
                    model: db.getWorkoutPrograms()
                    textRole: "title"
                }

                Row {
                    spacing: 8
                    width: parent.width

                    TextField {
                        id: durationField
                        width: parent.width * 0.5
                        placeholderText: "Durata (minuti)"
                        inputMethodHints: Qt.ImhDigitsOnly
                    }

                    Button {
                        text: "Registra (Dettagliato)"
                        onClicked: {
                            var prog = db.getWorkoutPrograms()[programPicker.currentIndex]
                            var exs = db.getProgramExercises(prog.program_id)
                            if (exs.length === 0) {
                                noExercisesMsg.visible = true
                            } else {
                                noExercisesMsg.visible = false
                                stackView.push(sessionDetailPage, {
                                    isLogging: true,
                                    program: prog,
                                    exercises: exs
                                })
                            }
                        }
                    }

                    Text {
                        id: noExercisesMsg
                        text: "Questo programma non ha esercizi assegnati."
                        color: "red"
                        visible: false
                        font.pixelSize: 12
                    }
                }
            }
        }

        // Session history
        Text {
            text: "Storico"
            font.pixelSize: 15
            font.bold: true
            leftPadding: 12
            topPadding: 8
        }

        ListView {
            id: sessionList
            width: parent.width
            height: parent.height - 220
            clip: true
            model: db.getSessions(db.currentUserId())
            spacing: 6

            delegate: Rectangle {
                width: sessionList.width - 16
                height: 80
                radius: 8
                color: modelData.completed ? "#c8e6c9" : "#f0f0f0"
                x: 8

                MouseArea {
                        anchors.fill: parent
                        onClicked: stackView.push(sessionDetailPage, { session: modelData })
                    }


                Column {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 4

                    Text {
                        text: modelData.program
                        font.pixelSize: 15
                        font.bold: true
                    }

                    Text {
                        text: modelData.datetime + "  |  " + modelData.duration + " min"
                        font.pixelSize: 12
                        color: "#555"
                    }

                    Text {
                        text: modelData.completed ? "✓ Completata" : "In corso"
                        font.pixelSize: 12
                        color: modelData.completed ? "green" : "orange"
                    }
                }
            }
        }
    }
}