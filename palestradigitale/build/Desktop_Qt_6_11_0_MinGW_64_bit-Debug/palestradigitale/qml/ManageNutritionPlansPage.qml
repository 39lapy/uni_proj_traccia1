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

            TabButton { text: "Piani" }
            TabButton { text: "Nuovo Piano" }
            TabButton { text: "Nuovo Consiglio" }
        }

        StackLayout {
            width: parent.width
            height: parent.height - tabBar.height
            currentIndex: tabBar.currentIndex

            // --- TAB 1: LIST ---
            Item {
                ListView {
                    id: planList
                    anchors.fill: parent
                    clip: true
                    model: db.getNutritionPlans()
                    spacing: 6

                    delegate: Rectangle {
                        width: planList.width - 16
                        height: 90
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
                                text: modelData.description
                                font.pixelSize: 13
                                color: "#555"
                                wrapMode: Text.WordWrap
                                width: parent.width
                            }

                            Text {
                                text: "Nutrizionista: " + modelData.nutritionist + " | " + modelData.created_at
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
                                db.deleteNutritionPlan(modelData.plan_id)
                                planList.model = db.getNutritionPlans()
                            }
                        }
                    }
                }
            }

            // --- TAB 2: NEW PLAN ---
            Item {
                ScrollView {
                    anchors.fill: parent
                    contentWidth: parent.width

                    Column {
                        width: parent.width
                        padding: 16
                        spacing: 12

                        Text {
                            text: "Nuovo Piano Nutrizionale"
                            font.pixelSize: 18
                            font.bold: true
                        }

                        TextField {
                            id: planTitleField
                            width: parent.width - 32
                            placeholderText: "Titolo"
                        }

                        TextField {
                            id: planDescField
                            width: parent.width - 32
                            placeholderText: "Descrizione"
                        }

                        Text {
                            id: planErrorText
                            color: "red"
                            visible: false
                        }

                        Text {
                            id: planSuccessText
                            text: "✓ Piano creato!"
                            color: "green"
                            visible: false
                        }

                        Button {
                            text: "Crea Piano"
                            width: parent.width - 32
                            onClicked: {
                                if (planTitleField.text === "") {
                                    planErrorText.text = "Il titolo è obbligatorio"
                                    planErrorText.visible = true
                                    planSuccessText.visible = false
                                    return
                                }
                                var ok = db.addNutritionPlan(planTitleField.text, planDescField.text)
                                if (ok) {
                                    planTitleField.text = ""
                                    planDescField.text = ""
                                    planErrorText.visible = false
                                    planSuccessText.visible = true
                                    planList.model = db.getNutritionPlans()
                                    tabBar.currentIndex = 0
                                } else {
                                    planErrorText.text = "Errore durante la creazione"
                                    planErrorText.visible = true
                                }
                            }
                        }
                    }
                }
            }

            // --- TAB 3: NEW TIP ---
            Item {
                ScrollView {
                    anchors.fill: parent
                    contentWidth: parent.width

                    Column {
                        width: parent.width
                        padding: 16
                        spacing: 12

                        Text {
                            text: "Nuovo Consiglio Nutrizionale"
                            font.pixelSize: 18
                            font.bold: true
                        }

                        ComboBox {
                            id: tipPlanPicker
                            width: parent.width - 32
                            model: db.getNutritionPlans()
                            textRole: "title"
                        }

                        ComboBox {
                            id: tipClientPicker
                            width: parent.width - 32
                            model: db.getClients()
                            textRole: "first_name"
                        }

                        TextField {
                            id: tipDateField
                            width: parent.width - 32
                            placeholderText: "Data (yyyy-MM-dd)"
                            text: new Date().toISOString().substring(0, 10)
                        }

                        TextField {
                            id: tipContentField
                            width: parent.width - 32
                            placeholderText: "Contenuto del consiglio"
                        }

                        Text {
                            id: tipErrorText
                            color: "red"
                            visible: false
                        }

                        Text {
                            id: tipSuccessText
                            text: "✓ Consiglio aggiunto!"
                            color: "green"
                            visible: false
                        }

                        Button {
                            text: "Aggiungi Consiglio"
                            width: parent.width - 32
                            onClicked: {
                                if (tipContentField.text === "") {
                                    tipErrorText.text = "Il contenuto è obbligatorio"
                                    tipErrorText.visible = true
                                    tipSuccessText.visible = false
                                    return
                                }
                                var plan = db.getNutritionPlans()[tipPlanPicker.currentIndex]
                                var client = db.getClients()[tipClientPicker.currentIndex]
                                var ok = db.addNutritionTip(plan.plan_id, client.user_id,
                                                             tipDateField.text, tipContentField.text)
                                if (ok) {
                                    tipContentField.text = ""
                                    tipErrorText.visible = false
                                    tipSuccessText.visible = true
                                } else {
                                    tipErrorText.text = "Errore durante l'aggiunta"
                                    tipErrorText.visible = true
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}