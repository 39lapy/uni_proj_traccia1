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

    ScrollView {
        anchors.fill: parent
        contentWidth: parent.width

        Column {
            width: parent.width
            padding: 24
            spacing: 14

            Text {
                text: "Registrazione"
                font.pixelSize: 26
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
            }

            TextField {
                id: firstNameField
                width: parent.width - 48
                placeholderText: "Nome"
            }

            TextField {
                id: lastNameField
                width: parent.width - 48
                placeholderText: "Cognome"
            }

            TextField {
                id: emailField
                width: parent.width - 48
                placeholderText: "Email"
                inputMethodHints: Qt.ImhEmailAddress
            }

            TextField {
                id: passwordField
                width: parent.width - 48
                placeholderText: "Password"
                echoMode: TextInput.Password
            }

            TextField {
                id: confirmPasswordField
                width: parent.width - 48
                placeholderText: "Conferma Password"
                echoMode: TextInput.Password
            }

            Text {
                text: "Tipo account"
                font.pixelSize: 14
                color: "#555"
            }

            ComboBox {
                id: userTypePicker
                width: parent.width - 48
                model: ["client", "trainer", "nutritionist"]
            }

            Text {
                id: errorText
                color: "red"
                visible: false
                wrapMode: Text.WordWrap
                width: parent.width - 48
            }

            Text {
                id: successText
                text: "✓ Registrazione completata! Puoi ora effettuare il login."
                color: "green"
                visible: false
                wrapMode: Text.WordWrap
                width: parent.width - 48
            }

            Button {
                text: "Registrati"
                width: parent.width - 48
                onClicked: {
                    errorText.visible = false
                    successText.visible = false

                    if (firstNameField.text === "" || lastNameField.text === "" ||
                        emailField.text === "" || passwordField.text === "") {
                        errorText.text = "Compila tutti i campi obbligatori"
                        errorText.visible = true
                        return
                    }

                    if (passwordField.text !== confirmPasswordField.text) {
                        errorText.text = "Le password non coincidono"
                        errorText.visible = true
                        return
                    }

                    var ok = db.registerUser(
                        firstNameField.text,
                        lastNameField.text,
                        emailField.text,
                        passwordField.text,
                        userTypePicker.currentText
                    )

                    if (ok) {
                        firstNameField.text = ""
                        lastNameField.text = ""
                        emailField.text = ""
                        passwordField.text = ""
                        confirmPasswordField.text = ""
                        userTypePicker.currentIndex = 0
                        successText.visible = true
                    } else {
                        errorText.text = "Errore: email già in uso o dati non validi"
                        errorText.visible = true
                    }
                }
            }
        }
    }
}