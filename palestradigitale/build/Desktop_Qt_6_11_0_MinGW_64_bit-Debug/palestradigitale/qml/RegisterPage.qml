import QtQuick
import QtQuick.Controls

Page {
    id: loginPage
    signal goToRegister

    header: ToolBar {
        ToolButton {
            text: "← Indietro"
            onClicked: stackView.pop()
        }
    }

    property StackView stackView

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

            // OTP field — only visible for trainer/nutritionist
            Column {
                width: parent.width
                spacing: 6
                visible: userTypePicker.currentIndex > 0

                Text {
                    text: "Codice di autorizzazione"
                    font.pixelSize: 14
                    color: "#555"
                }

                TextField {
                    id: otpField
                    width: parent.width - 48
                    placeholderText: "Inserisci il codice OTP"
                    inputMethodHints: Qt.ImhDigitsOnly
                }
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

                    // Validate OTP for trainer/nutritionist
                    if (userTypePicker.currentIndex > 0) {
                        if (otpField.text === "") {
                            errorText.text = "Inserisci il codice di autorizzazione"
                            errorText.visible = true
                            return
                        }
                        if (!db.validateRegistrationCode(otpField.text, userTypePicker.currentText)) {
                            errorText.text = "Codice non valido o già utilizzato"
                            errorText.visible = true
                            return
                        }
                    }

                    var ok = db.registerUser(
                        firstNameField.text,
                        lastNameField.text,
                        emailField.text,
                        passwordField.text,
                        userTypePicker.currentText
                    )

                    if (ok) {
                        if (userTypePicker.currentIndex > 0)
                            db.markCodeAsUsed(otpField.text)

                        firstNameField.text = ""
                        lastNameField.text = ""
                        emailField.text = ""
                        passwordField.text = ""
                        confirmPasswordField.text = ""
                        otpField.text = ""
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