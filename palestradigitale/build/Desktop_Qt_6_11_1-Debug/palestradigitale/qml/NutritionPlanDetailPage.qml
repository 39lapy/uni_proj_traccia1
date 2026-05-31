import QtQuick
import QtQuick.Controls

Page {
    property StackView stackView
    property var plan: ({})

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
                text: plan.title
                font.pixelSize: 24
                font.bold: true
                wrapMode: Text.WordWrap
                width: parent.width - 32
            }

            Rectangle { width: parent.width - 32; height: 1; color: "#ddd" }

            Text {
                text: "Nutrizionista: " + plan.nutritionist
                font.pixelSize: 15
                color: "#555"
            }

            Text {
                text: "Creato il: " + plan.created_at
                font.pixelSize: 14
                color: "#888"
            }

            Rectangle { width: parent.width - 32; height: 1; color: "#ddd" }

            Text {
                text: plan.description
                font.pixelSize: 14
                wrapMode: Text.WordWrap
                width: parent.width - 32
                color: "#333"
            }

            Rectangle { width: parent.width - 32; height: 1; color: "#ddd" }

            // Tips section
            Text {
                text: "Consigli associati"
                font.pixelSize: 16
                font.bold: true
            }

            ListView {
                width: parent.width - 32
                height: 200
                clip: true
                model: db.getNutritionTips(db.currentUserId())
                spacing: 6

                delegate: Rectangle {
                    width: parent.width
                    height: 70
                    radius: 8
                    color: "#f3e5f5"

                    Column {
                        anchors.fill: parent
                        anchors.margins: 10
                        spacing: 4

                        Text {
                            text: modelData.plan + " — " + modelData.date
                            font.pixelSize: 13
                            font.bold: true
                            color: "#555"
                        }

                        Text {
                            text: modelData.content
                            font.pixelSize: 13
                            wrapMode: Text.WordWrap
                            width: parent.width
                        }
                    }
                }
            }

            Rectangle { width: parent.width - 32; height: 1; color: "#ddd" }

            // Inline feedback
            Text {
                text: "Lascia un feedback"
                font.pixelSize: 16
                font.bold: true
            }

            QtObject {
                id: feedbackRating
                property int value: 0
            }

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
                id: feedbackComment
                width: parent.width - 32
                placeholderText: "Commento (opzionale)"
            }

            Button {
                text: "Invia Feedback"
                width: parent.width - 32
                enabled: feedbackRating.value > 0
                onClicked: {
                    var ok = db.addFeedback(db.currentUserId(), -1, plan.plan_id,
                                            feedbackRating.value, feedbackComment.text)
                    if (ok) {
                        feedbackComment.text = ""
                        feedbackRating.value = 0
                        feedbackSent.visible = true
                    }
                }
            }

            Text {
                id: feedbackSent
                text: "✓ Feedback inviato!"
                color: "green"
                visible: false
            }
        }
    }
}