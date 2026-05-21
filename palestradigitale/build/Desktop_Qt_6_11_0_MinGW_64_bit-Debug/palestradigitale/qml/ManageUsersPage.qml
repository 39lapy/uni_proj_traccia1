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

        // Tab bar
        TabBar {
            id: tabBar
            width: parent.width

            TabButton { text: "Utenti" }
            TabButton { text: "Assegnazioni" }
        }

        StackLayout {
            width: parent.width
            height: parent.height - tabBar.height
            currentIndex: tabBar.currentIndex

            // --- TAB 1: USERS ---
            Item {
                ListView {
                    id: userList
                    anchors.fill: parent
                    clip: true
                    model: db.getAllUsers()
                    spacing: 6

                    delegate: Rectangle {
                        width: userList.width - 16
                        height: 90
                        radius: 8
                        x: 8
                        color: "#f5f5f5"

                        Column {
                            anchors.left: parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.margins: 12
                            spacing: 4

                            Text {
                                text: modelData.first_name + " " + modelData.last_name
                                font.pixelSize: 16
                                font.bold: true
                            }

                            Text {
                                text: modelData.email
                                font.pixelSize: 13
                                color: "#555"
                            }

                            Text {
                                text: modelData.user_type + " | registrato: " + modelData.registration_date
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
                                db.deleteUser(modelData.user_id)
                                userList.model = db.getAllUsers()
                            }
                        }
                    }
                }
            }

            // --- TAB 2: ASSIGNMENTS ---
            Item {
                Column {
                    anchors.fill: parent
                    spacing: 0

                    // Assign trainer
                    Rectangle {
                        width: parent.width
                        height: 160
                        color: "#e8f5e9"

                        Column {
                            anchors.fill: parent
                            anchors.margins: 12
                            spacing: 8

                            Text {
                                text: "Assegna Trainer a Cliente"
                                font.pixelSize: 15
                                font.bold: true
                            }

                            ComboBox {
                                id: trainerPicker
                                width: parent.width
                                model: db.getTrainers()
                                textRole: "first_name"
                            }

                            ComboBox {
                                id: clientPicker
                                width: parent.width
                                model: db.getClients()
                                textRole: "first_name"
                            }

                            Button {
                                text: "Assegna"
                                width: parent.width
                                onClicked: {
                                    var trainer = db.getTrainers()[trainerPicker.currentIndex]
                                    var client = db.getClients()[clientPicker.currentIndex]
                                    var today = new Date().toISOString().substring(0, 10)
                                    var ok = db.assignTrainer(trainer.user_id, client.user_id, today)
                                    if (ok) assignmentList.model = db.getAssignments()
                                }
                            }
                        }
                    }

                    // Assignment list
                    Text {
                        text: "Assegnazioni attive"
                        font.pixelSize: 15
                        font.bold: true
                        leftPadding: 12
                        topPadding: 8
                    }

                    ListView {
                        id: assignmentList
                        width: parent.width
                        height: parent.height - 200
                        clip: true
                        model: db.getAssignments()
                        spacing: 6

                        delegate: Rectangle {
                            width: assignmentList.width - 16
                            height: 70
                            radius: 8
                            x: 8
                            color: "#f0f0f0"

                            Column {
                                anchors.fill: parent
                                anchors.margins: 10
                                spacing: 4

                                Text {
                                    text: "Trainer: " + modelData.trainer
                                    font.pixelSize: 14
                                    font.bold: true
                                }

                                Text {
                                    text: "Cliente: " + modelData.client
                                    font.pixelSize: 13
                                    color: "#555"
                                }

                                Text {
                                    text: "Dal: " + modelData.start_date
                                    font.pixelSize: 11
                                    color: "#888"
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}