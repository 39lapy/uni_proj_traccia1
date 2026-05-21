import QtQuick
import QtQuick.Controls

Page {
    id: loginPage
    signal loginSuccess(string userType)
    signal goToRegister

    Column {
        anchors.centerIn: parent
        spacing: 16
        width: 300

        Text {
            text: "Palestra Digitale"
            font.pixelSize: 28
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        TextField {
            id: emailField
            width: parent.width
            placeholderText: "Email"
        }

        TextField {
            id: passwordField
            width: parent.width
            placeholderText: "Password"
            echoMode: TextInput.Password
        }

        Text {
            id: errorText
            color: "red"
            visible: false
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            text: "Login"
            width: parent.width
            onClicked: {
                if (db.login(emailField.text, passwordField.text)) {
                    loginSuccess(db.currentUserType())
                } else {
                    errorText.text = "Email o password errati"
                    errorText.visible = true
                }
            }
        }

        Button {
            text: "Non hai un account? Registrati"
            width: parent.width
            flat: true
            onClicked: goToRegister()
        }
    }
}