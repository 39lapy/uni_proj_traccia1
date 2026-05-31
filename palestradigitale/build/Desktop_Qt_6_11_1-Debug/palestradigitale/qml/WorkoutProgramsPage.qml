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

    function applyFilters() {
        var diff = difficultyFilter.currentIndex === 0 ? "" : difficultyFilter.currentText
        var goal = goalFilter.currentIndex === 0 ? "" : goalFilter.currentText

        if (diff === "" && goal === "") {
            programList.model = db.getWorkoutPrograms()
        } else if (diff !== "" && goal === "") {
            programList.model = db.getWorkoutProgramsByDifficulty(diff)
        } else if (diff === "" && goal !== "") {
            programList.model = db.getWorkoutProgramsByGoal(goal)
        } else {
            // both filters active — filter client-side
            var all = db.getWorkoutProgramsByDifficulty(diff)
            var filtered = []
            for (var i = 0; i < all.length; i++) {
                if (all[i].goal === goal) filtered.push(all[i])
            }
            programList.model = filtered
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
                width: 130
                model: ["Difficoltà", "beginner", "intermediate", "advanced"]
                onActivated: applyFilters()
            }

            ComboBox {
                id: goalFilter
                width: 130
                model: ["Obiettivo"].concat(db.getGoals())
                onActivated: applyFilters()
            }

            Button {
                text: "Reset"
                onClicked: {
                    difficultyFilter.currentIndex = 0
                    goalFilter.currentIndex = 0
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