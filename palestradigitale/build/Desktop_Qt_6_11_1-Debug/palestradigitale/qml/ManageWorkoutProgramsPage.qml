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
                ListModel {
                    id: selectedExercisesModel
                }

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

                        Rectangle { width: parent.width - 32; height: 1; color: "#ddd" }

                        Text {
                            text: "Esercizi"
                            font.bold: true
                        }

                        Repeater {
                            model: selectedExercisesModel
                            delegate: Rectangle {
                                width: parent.width - 32
                                height: 40
                                color: "#eee"
                                radius: 4
                                Row {
                                    anchors.fill: parent
                                    anchors.margins: 8
                                    spacing: 8
                                    Text {
                                        text: model.name + " (" + model.sets + "x" + model.reps + ")"
                                        verticalAlignment: Text.AlignVCenter
                                        width: parent.width - 40
                                    }
                                    Button {
                                        text: "✕"
                                        width: 30; height: 24
                                        onClicked: selectedExercisesModel.remove(index)
                                    }
                                }
                            }
                        }

                        Button {
                            text: "+ Aggiungi Esercizio"
                            width: parent.width - 32
                            onClicked: exerciseDialog.open()
                        }

                        Rectangle { width: parent.width - 32; height: 1; color: "#ddd" }

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
                                
                                var exList = []
                                for (var i = 0; i < selectedExercisesModel.count; i++) {
                                    var item = selectedExercisesModel.get(i)
                                    exList.push({
                                        "exercise_id": item.exercise_id,
                                        "sets": item.sets,
                                        "reps": item.reps,
                                        "rest_seconds": item.rest_seconds
                                    })
                                }

                                var ok = db.addWorkoutProgramWithExercises(
                                    titleField.text,
                                    goalField.text,
                                    difficultyPicker.currentText,
                                    parseInt(durationField.text) || 1,
                                    descField.text,
                                    exList
                                )
                                if (ok) {
                                    titleField.text = ""
                                    goalField.text = ""
                                    durationField.text = ""
                                    descField.text = ""
                                    selectedExercisesModel.clear()
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

                Dialog {
                    id: exerciseDialog
                    title: "Aggiungi Esercizio"
                    x: (parent.width - width) / 2
                    y: (parent.height - height) / 2
                    width: 300
                    standardButtons: Dialog.Ok | Dialog.Cancel

                    Column {
                        spacing: 12
                        width: parent.width

                        ComboBox {
                            id: exercisePicker
                            width: parent.width
                            textRole: "name"
                            model: db.getAllExercises()
                        }

                        Row {
                            spacing: 10
                            TextField {
                                id: setsField
                                placeholderText: "Sets"
                                width: 135
                                inputMethodHints: Qt.ImhDigitsOnly
                            }
                            TextField {
                                id: repsField
                                placeholderText: "Reps"
                                width: 135
                                inputMethodHints: Qt.ImhDigitsOnly
                            }
                        }

                        TextField {
                            id: restField
                            placeholderText: "Recupero (sec)"
                            width: parent.width
                            inputMethodHints: Qt.ImhDigitsOnly
                        }
                    }

                    onAccepted: {
                        selectedExercisesModel.append({
                            "exercise_id": exercisePicker.model[exercisePicker.currentIndex].exercise_id,
                            "name": exercisePicker.model[exercisePicker.currentIndex].name,
                            "sets": parseInt(setsField.text) || 3,
                            "reps": parseInt(repsField.text) || 10,
                            "rest_seconds": parseInt(restField.text) || 60
                        })
                        setsField.text = ""
                        repsField.text = ""
                        restField.text = ""
                    }
                }
            }
        }
    }
}