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

        // Filter bar
        Row {
            width: parent.width
            height: 50
            spacing: 8
            padding: 8

            ComboBox {
                id: difficultyFilter
                width: 150
                model: ["Tutti", "beginner", "intermediate", "advanced"]
                onActivated: programList.model = currentIndex === 0
                    ? db.getWorkoutPrograms()
                    : db.getWorkoutProgramsByDifficulty(currentText)
            }

            Button {
                text: "Reset"
                onClicked: {
                    difficultyFilter.currentIndex = 0
                    programList.model = db.getWorkoutPrograms()
                }
            }
        }

        // Program list
        ListView {
            id: programList
            width: parent.width
            height: parent.height - 50
            clip: true
            model: db.getWorkoutPrograms()
            spacing: 8

            delegate: Rectangle {
                width: programList.width - 16
                height: 120
                radius: 8
                color: "#f0f0f0"
                x: 8

                MouseArea {
                    anchors.fill: parent
                    onClicked: stackView.push(workoutProgramDetailPage, { program: modelData })
                }

                Column {
                    anchors.fill: parent
                    anchors.margins: 12
                    spacing: 4

                    Text {
                        text: modelData.title
                        font.pixelSize: 18
                        font.bold: true
                    }

                    Text {
                        text: "Obiettivo: " + modelData.goal
                        font.pixelSize: 13
                        color: "#555"
                    }

                    Text {
                        text: "Difficoltà: " + modelData.difficulty + "  |  Durata: " + modelData.duration_weeks + " settimane"
                        font.pixelSize: 13
                        color: "#555"
                    }

                    Text {
                        text: "Trainer: " + modelData.trainer
                        font.pixelSize: 12
                        color: "#888"
                    }
                }
            }
        }
    }
}