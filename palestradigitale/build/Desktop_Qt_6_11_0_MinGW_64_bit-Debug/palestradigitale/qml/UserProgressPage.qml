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

        // Client picker
        Rectangle {
            width: parent.width
            height: 60
            color: "#e8f5e9"

            Row {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 8

                ComboBox {
                    id: clientPicker
                    width: parent.width - 100
                    model: db.getClients()
                    textRole: "first_name"
                    onActivated: {
                        var client = db.getClients()[currentIndex]
                        sessionList.model = db.getUserProgress(client.user_id)
                        feedbackList.model = db.getFeedbackByUser(client.user_id)
                        statsText.update(client.user_id)
                    }
                }

                Button {
                    text: "Carica"
                    onClicked: {
                        var client = db.getClients()[clientPicker.currentIndex]
                        sessionList.model = db.getUserProgress(client.user_id)
                        feedbackList.model = db.getFeedbackByUser(client.user_id)
                        statsText.update(client.user_id)
                    }
                }
            }
        }

        TabBar {
            id: tabBar
            width: parent.width

            TabButton { text: "Sessioni" }
            TabButton { text: "Feedback" }
            TabButton { text: "Statistiche" }
        }

        StackLayout {
            width: parent.width
            height: parent.height - tabBar.height - 60
            currentIndex: tabBar.currentIndex

            // --- TAB 1: SESSIONS ---
            Item {
                ListView {
                    id: sessionList
                    anchors.fill: parent
                    clip: true
                    spacing: 6

                    delegate: Rectangle {
                        width: sessionList.width - 16
                        height: 80
                        radius: 8
                        x: 8
                        color: modelData.completed ? "#c8e6c9" : "#f0f0f0"

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
                                text: (modelData.completed ? "✓ Completata" : "In corso") + "  |  " + modelData.difficulty
                                font.pixelSize: 12
                                color: modelData.completed ? "green" : "orange"
                            }
                        }
                    }
                }
            }

            // --- TAB 2: FEEDBACK ---
            Item {
                ListView {
                    id: feedbackList
                    anchors.fill: parent
                    clip: true
                    spacing: 6

                    delegate: Rectangle {
                        width: feedbackList.width - 16
                        height: 90
                        radius: 8
                        x: 8
                        color: "#fff8e1"

                        Column {
                            anchors.fill: parent
                            anchors.margins: 10
                            spacing: 4

                            Text {
                                text: modelData.program ? modelData.program : (modelData.plan ? modelData.plan : "N/D")
                                font.pixelSize: 15
                                font.bold: true
                            }

                            Row {
                                spacing: 0
                                anchors.left: parent.left
                                Repeater {
                                    model: 5
                                    Text {
                                        text: "★"
                                        font.pixelSize: 16
                                        width: 18
                                        horizontalAlignment: Text.AlignHCenter
                                        color: index < modelData.rating ? "#f5a623" : "#ccc"
                                    }
                                }
                            }

                            Text {
                                text: modelData.comment !== "" ? modelData.comment : "Nessun commento"
                                font.pixelSize: 12
                                color: "#555"
                                wrapMode: Text.WordWrap
                                width: parent.width
                            }

                            Text {
                                text: modelData.date
                                font.pixelSize: 11
                                color: "#888"
                            }
                        }
                    }
                }
            }

            // --- TAB 3: STATS ---
            Item {
                Column {
                    anchors.centerIn: parent
                    spacing: 16
                    width: parent.width - 32

                    Text {
                        id: statsText
                        font.pixelSize: 15
                        color: "#333"
                        wrapMode: Text.WordWrap
                        width: parent.width
                        text: "Seleziona un cliente per vedere le statistiche."

                        function update(userId) {
                            var sessions = db.getUserProgress(userId)
                            var total = sessions.length
                            var completed = 0
                            var totalMinutes = 0
                            for (var i = 0; i < sessions.length; i++) {
                                if (sessions[i].completed) completed++
                                totalMinutes += sessions[i].duration
                            }
                            var feedback = db.getFeedbackByUser(userId)
                            var avgRating = 0
                            if (feedback.length > 0) {
                                var sum = 0
                                for (var j = 0; j < feedback.length; j++)
                                    sum += feedback[j].rating
                                avgRating = (sum / feedback.length).toFixed(1)
                            }
                            text = "Sessioni totali: " + total +
                                   "\nSessioni completate: " + completed +
                                   "\nMinuti totali allenamento: " + totalMinutes +
                                   "\nFeedback ricevuti: " + feedback.length +
                                   "\nValutazione media: " + (feedback.length > 0 ? avgRating + " ★" : "N/D")
                        }
                    }
                }
            }
        }
    }
}