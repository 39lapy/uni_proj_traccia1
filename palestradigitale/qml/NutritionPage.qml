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

        // Nutrition plans
        Text {
            text: "Piani Nutrizionali"
            font.pixelSize: 18
            font.bold: true
            leftPadding: 12
            topPadding: 12
        }

        ListView {
            id: planList
            width: parent.width
            height: 200
            clip: true
            model: db.getNutritionPlans()
            spacing: 6

            delegate: Rectangle {
                width: planList.width - 16
                height: 80
                radius: 8
                color: "#e3f2fd"
                x: 8

                MouseArea {
                        anchors.fill: parent
                        onClicked: stackView.push(nutritionPlanDetailPage, { plan: modelData })
                    }

                Column {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 4

                    Text {
                        text: modelData.title
                        font.pixelSize: 15
                        font.bold: true
                    }

                    Text {
                        text: modelData.description
                        font.pixelSize: 12
                        color: "#555"
                        wrapMode: Text.WordWrap
                        width: parent.width
                    }

                    Text {
                        text: "Nutrizionista: " + modelData.nutritionist
                        font.pixelSize: 11
                        color: "#888"
                    }
                }
            }
        }

        // MOTD
        Text {
            text: "Consigli Giornalieri"
            font.pixelSize: 18
            font.bold: true
            leftPadding: 12
            topPadding: 8
        }

        ListView {
            id: tipList
            width: parent.width
            height: parent.height - 280
            clip: true
            model: db.getNutritionTips(db.currentUserId())
            spacing: 6

            delegate: Rectangle {
                width: tipList.width - 16
                height: 80
                radius: 8
                color: "#f3e5f5"
                x: 8

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
    }
}