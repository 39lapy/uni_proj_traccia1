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

        Text {
            text: db.currentUserType()
            font.pixelSize: 14
            color: "#888"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle { width: parent.width; height: 1; color: "#ddd" }

        Button {
            text: "👥 Gestione Utenti"
            width: parent.width
            onClicked: stackView.push(manageUsersPage)
        }

        Button {
            text: "🏋️ Programmi di Allenamento"
            width: parent.width
            onClicked: stackView.push(manageWorkoutProgramsPage)
        }

        Button {
            text: "🥗 Piani Nutrizionali"
            width: parent.width
            onClicked: stackView.push(manageNutritionPlansPage)
        }

        Button {
            text: "📊 Progressi Utenti"
            width: parent.width
            onClicked: stackView.push(userProgressPage)
        }

        Button {
            text: "🔑 Codici Registrazione"
            width: parent.width
            visible: db.currentUserType() === "administrator"
            onClicked: stackView.push(manageCodesPage)
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