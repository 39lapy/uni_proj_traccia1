import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

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

        TabBar {
            id: tabBar
            width: parent.width

            TabButton { text: "Programmi" }
            TabButton { text: "Nuovo" }
        }

        StackLayout {
            width: parent.width
            height: parent.height - tabBar.height
            currentIndex: tabBar.currentIndex

            // --- TAB 1: LIST ---
            Item {
                ListView {
                    id: programList
                    anchors.fill: parent
                    clip: true
                    model: db.getWorkoutPrograms()
                    spacing: 6

                    delegate: Rectangle {
                        width: programList.width - 16
                        height: 110
                        radius: 8
                        x: 8
                        color: "#f5f5f5"

                        Column {
                            anchors.left: parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.leftMargin: 12
                            spacing: 4
                            width: parent.width - 60

                            Text {
                                text: modelData.title
                                font.pixelSize: 16
                                font.bold: true
                                wrapMode: Text.WordWrap
                                width: parent.width
                            }

                            Text {
                                text: modelData.goal + " | " + modelData.difficulty
                                font.pixelSize: 13
                                color: "#555"
                            }

                            Text {
                                text: modelData.duration_weeks + " settimane | Trainer: " + modelData.trainer
                                font.pixelSize: 11
                                color: "#888"
                            }
                        }

                        Button {
                            text: "🗑"
                            anchors.right: parent.right
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.rightMargin: 12
                            onClicked: {
                                db.deleteWorkoutProgram(modelData.program_id)
                                programList.model = db.getWorkoutPrograms()
                            }
                        }
                    }
                }
            }

            // --- TAB 2: NEW PROGRAM ---
            Item {
                ScrollView {
                    anchors.fill: parent
                    contentWidth: parent.width

                    Column {
                        width: parent.width
                        padding: 16
                        spacing: 12

                        Text {
                            text: "Nuovo Programma"
                            font.pixelSize: 18
                            font.bold: true
                        }

                        TextField {
                            id: titleField
                            width: parent.width - 32
                            placeholderText: "Titolo"
                        }

                        TextField {
                            id: goalField
                            width: parent.width - 32
                            placeholderText: "Obiettivo (es. weight loss, muscle gain)"
                        }

                        ComboBox {
                            id: difficultyPicker
                            width: parent.width - 32
                            model: ["beginner", "intermediate", "advanced"]
                        }

                        TextField {
                            id: durationField
                            width: parent.width - 32
                            placeholderText: "Durata (settimane)"
                            inputMethodHints: Qt.ImhDigitsOnly
                        }

                        TextField {
                            id: descField
                            width: parent.width - 32
                            placeholderText: "Descrizione"
                        }

                        Text {
                            id: errorText
                            color: "red"
                            visible: false
                        }

                        Text {
                            id: successText
                            text: "✓ Programma creato!"
                            color: "green"
                            visible: false
                        }

                        Button {
                            text: "Crea Programma"
                            width: parent.width - 32
                            onClicked: {
                                if (titleField.text === "" || goalField.text === "" || durationField.text === "") {
                                    errorText.text = "Compila tutti i campi obbligatori"
                                    errorText.visible = true
                                    successText.visible = false
                                    return
                                }
                                var ok = db.addWorkoutProgram(
                                    titleField.text,
                                    goalField.text,
                                    difficultyPicker.currentText,
                                    parseInt(durationField.text) || 1,
                                    descField.text
                                )
                                if (ok) {
                                    titleField.text = ""
                                    goalField.text = ""
                                    durationField.text = ""
                                    descField.text = ""
                                    difficultyPicker.currentIndex = 0
                                    errorText.visible = false
                                    successText.visible = true
                                    programList.model = db.getWorkoutPrograms()
                                    tabBar.currentIndex = 0
                                } else {
                                    errorText.text = "Errore durante la creazione"
                                    errorText.visible = true
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}