import QtQuick
import QtQuick.Controls

Page {
    property StackView stackView

    signal logout

    Column {
        anchors.centerIn: parent
        spacing: 16

        Text {
            text: "Benvenuto, " + db.currentUserName()
            font.pixelSize: 24
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            text: "Admin Dashboard"
            font.pixelSize: 16
            anchors.horizontalCenter: parent.horizontalCenter
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