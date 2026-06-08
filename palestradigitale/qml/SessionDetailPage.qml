import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    property StackView stackView
    property var session: ({})
    property bool isLogging: false
    property var program: ({})
    property var exercises: null

    header: ToolBar {
        ToolButton {
            text: "← Indietro"
            onClicked: stackView.pop()
        }
    }

    ListModel {
        id: loggingModel
    }

    Component.onCompleted: {
        if (isLogging && exercises) {
            for (var i = 0; i < exercises.length; i++) {
                var ex = exercises[i]
                for (var s = 1; s <= ex.sets; s++) {
                    loggingModel.append({
                        "exercise_name": ex.name,
                        "program_exercise_id": ex.id,
                        "set_number": s,
                        "weight": "0",
                        "reps_performed": ex.reps.toString()
                    })
                }
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 12

        Text {
            text: isLogging ? "Nuovo Allenamento: " + program.title : session.program
            font.pixelSize: 20
            font.bold: true
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
        }

        Rectangle { Layout.fillWidth: true; Layout.preferredHeight: 1; color: "#ddd" }

        // --- VIEW MODE ---
        Column {
            visible: !isLogging
            Layout.fillWidth: true
            spacing: 8
            
            Text { text: "Data: " + (session.datetime || ""); font.pixelSize: 14; color: "#555" }
            Text { text: "Durata: " + (session.duration || "") + " minuti"; font.pixelSize: 14; color: "#555" }

            Text { text: "Risultati:"; font.bold: true; topPadding: 8 }
            
            ListView {
                width: parent.width
                height: 300
                clip: true
                model: session.session_id ? db.getSessionResults(session.session_id) : []
                delegate: Text {
                    width: parent.width
                    text: modelData.exercise_name + " (Set " + modelData.set_number + "): " + modelData.weight + "kg x " + modelData.reps_performed
                    font.pixelSize: 13
                    height: 25
                }
            }
        }

        // --- LOGGING MODE ---
        ColumnLayout {
            visible: isLogging
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 8

            ListView {
                id: logList
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                model: loggingModel
                spacing: 10
                delegate: Rectangle {
                    width: logList.width
                    height: 50
                    color: "#f5f5f5"
                    radius: 4
                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 8
                        spacing: 8
                        Text {
                            text: model.exercise_name + "\nSet " + model.set_number
                            font.pixelSize: 12
                            Layout.preferredWidth: 100
                        }
                        TextField {
                            placeholderText: "kg"
                            Layout.preferredWidth: 60
                            text: model.weight
                            onTextChanged: model.weight = text
                            inputMethodHints: Qt.ImhFormattedNumbersOnly
                        }
                        TextField {
                            placeholderText: "reps"
                            Layout.preferredWidth: 60
                            text: model.reps_performed
                            onTextChanged: model.reps_performed = text
                            inputMethodHints: Qt.ImhDigitsOnly
                        }
                    }
                }
            }

            Button {
                text: "💾 Salva Allenamento"
                Layout.fillWidth: true
                highlighted: true
                onClicked: {
                    var results = []
                    for (var i = 0; i < loggingModel.count; i++) {
                        var item = loggingModel.get(i)
                        results.push({
                            "program_exercise_id": item.program_exercise_id,
                            "set_number": item.set_number,
                            "weight": parseFloat(item.weight) || 0,
                            "reps_performed": parseInt(item.reps_performed) || 0
                        })
                    }
                    
                    var now = new Date().toISOString().replace('T', ' ').substring(0, 19)
                    var ok = db.logDetailedSession(db.currentUserId(), program.program_id, now, 60, results)
                    if (ok) {
                        stackView.pop()
                    }
                }
            }
        }
    }
}