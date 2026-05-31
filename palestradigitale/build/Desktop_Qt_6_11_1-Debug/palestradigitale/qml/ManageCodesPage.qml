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

        // Generate code section
        Rectangle {
            width: parent.width
            height: 130
            color: "#e8f5e9"

            Column {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 10

                Text {
                    text: "Genera Codice OTP"
                    font.pixelSize: 16
                    font.bold: true
                }

                ComboBox {
                    id: rolePicker
                    width: parent.width
                    model: ["trainer", "nutritionist"]
                }

                Row {
                    spacing: 12
                    width: parent.width

                    Button {
                        text: "Genera"
                        onClicked: {
                            var code = db.generateRegistrationCode(rolePicker.currentText)
                            if (code !== "") {
                                generatedCode.text = "Codice: " + code
                                generatedCode.visible = true
                                codeList.model = db.getRegistrationCodes()
                            }
                        }
                    }

                    Text {
                        id: generatedCode
                        visible: false
                        font.pixelSize: 20
                        font.bold: true
                        color: "#2e7d32"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
        }

        // Code list
        Text {
            text: "Codici generati"
            font.pixelSize: 15
            font.bold: true
            leftPadding: 12
            topPadding: 8
        }

        ListView {
            id: codeList
            width: parent.width
            height: parent.height - 180
            clip: true
            model: db.getRegistrationCodes()
            spacing: 6

            delegate: Rectangle {
                width: codeList.width - 16
                height: 70
                radius: 8
                x: 8
                color: modelData.used ? "#f5f5f5" : "#e8f5e9"

                Column {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 4

                    Row {
                        spacing: 12

                        Text {
                            text: modelData.code
                            font.pixelSize: 20
                            font.bold: true
                            color: modelData.used ? "#aaa" : "#2e7d32"
                        }

                        Text {
                            text: modelData.used ? "✓ Usato" : "● Attivo"
                            font.pixelSize: 13
                            color: modelData.used ? "#aaa" : "green"
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                    Text {
                        text: modelData.role + " | " + modelData.created_at
                        font.pixelSize: 12
                        color: "#888"
                    }
                }
            }
        }
    }
}