import QtQuick
import QtQuick.Controls

Page {
    property StackView stackView
    property var program: ({})

    header: ToolBar {
        ToolButton {
            text: "← Indietro"
            onClicked: stackView.pop()
        }
    }

    ScrollView {
        anchors.fill: parent
        contentWidth: parent.width

        Column {
            width: parent.width
            padding: 16
            spacing: 12

            Text {
                text: program.title
                font.pixelSize: 24
                font.bold: true
                wrapMode: Text.WordWrap
                width: parent.width - 32
            }

            Rectangle { width: parent.width - 32; height: 1; color: "#ddd" }

            Text { text: "Obiettivo: " + program.goal; font.pixelSize: 15; color: "#555" }
            Text { text: "Difficoltà: " + program.difficulty; font.pixelSize: 15; color: "#555" }
            Text { text: "Durata: " + program.duration_weeks + " settimane"; font.pixelSize: 15; color: "#555" }
            Text { text: "Trainer: " + program.trainer; font.pixelSize: 15; color: "#555" }

            Rectangle { width: parent.width - 32; height: 1; color: "#ddd" }

            Text {
                text: program.description
                font.pixelSize: 14
                wrapMode: Text.WordWrap
                width: parent.width - 32
                color: "#333"
            }

            Rectangle { width: parent.width - 32; height: 1; color: "#ddd" }

            Text { text: "Esercizi in questo programma"; font.pixelSize: 16; font.bold: true }

            ListView {
                width: parent.width - 32
                height: 150
                model: db.getProgramExercises(program.program_id)
                clip: true
                spacing: 4
                delegate: Rectangle {
                    width: parent.width
                    height: 30
                    color: "#f9f9f9"
                    Text {
                        anchors.fill: parent; anchors.leftMargin: 8
                        text: modelData.name + " - " + modelData.sets + "x" + modelData.reps + " (rec. " + modelData.rest_seconds + "s)"
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }

            Button {
                text: "🚀 Inizia Allenamento"
                width: parent.width - 32
                highlighted: true
                onClicked: {
                    stackView.push(sessionDetailPage, { 
                        isLogging: true, 
                        program: program,
                        exercises: db.getProgramExercises(program.program_id)
                    })
                }
            }

            Rectangle { width: parent.width - 32; height: 1; color: "#ddd" }

            Text { text: "Lascia un feedback"; font.pixelSize: 16; font.bold: true }

            QtObject { id: feedbackRating; property int value: 0 }

            Row {
                spacing: 4
                Repeater {
                    model: 5
                    delegate: Button {
                        flat: true
                        contentItem: Text {
                            text: "★"
                            font.pixelSize: 24
                            color: index < feedbackRating.value ? "#f5a623" : "#ccc"
                            horizontalAlignment: Text.AlignHCenter
                        }
                        onClicked: feedbackRating.value = index + 1
                    }
                }
            }

            TextField {
                id: feedbackComment; width: parent.width - 32
                placeholderText: "Commento (opzionale)"
            }

            Button {
                text: "Invia Feedback"
                enabled: feedbackRating.value > 0
                onClicked: {
                    var ok = db.addFeedback(db.currentUserId(), program.program_id, -1,
                                            feedbackRating.value, feedbackComment.text)
                    if (ok) {
                        feedbackComment.text = ""
                        feedbackRating.value = 0
                        feedbackSent.visible = true
                    }
                }
            }

            Text { id: feedbackSent; text: "✓ Feedback inviato!"; color: "green"; visible: false }
        }
    }
}