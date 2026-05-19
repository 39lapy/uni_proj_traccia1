import QtQuick
import QtQuick.Controls

Page {
    property StackView stackView

    signal logout

    Column {
        anchors.centerIn: parent
        spacing: 16
        width: 300

        Text {
            text: "Benvenuto, " + db.currentUserName()
            font.pixelSize: 24
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            text: "Programmi di Allenamento"
            width: parent.width
            onClicked: stackView.push(workoutProgramsPage)
        }

        Button {
            text: "Le mie Sessioni"
            width: parent.width
            onClicked: stackView.push(sessionsPage)
        }

        Button {
            text: "Nutrizione"
            width: parent.width
            onClicked: stackView.push(nutritionPage)
        }
    }


    Button {
            text: "Logout"
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 16
            onClicked: logout()
        }
}