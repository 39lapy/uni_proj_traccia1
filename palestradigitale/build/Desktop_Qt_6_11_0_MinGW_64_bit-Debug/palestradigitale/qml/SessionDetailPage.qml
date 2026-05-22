import QtQuick
import QtQuick.Controls

Page {
    property StackView stackView
    property var session: ({})

    header: ToolBar {
        ToolButton {
            text: "← Indietro"
            onClicked: stackView.pop()
        }
    }

    Column {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 12

        Text {
            text: session.program
            font.pixelSize: 24
            font.bold: true
            wrapMode: Text.WordWrap
            width: parent.width
        }

        Rectangle { width: parent.width; height: 1; color: "#ddd" }

        Text {
            text: "Data: " + session.datetime
            font.pixelSize: 15
            color: "#555"
        }

        Text {
            text: "Durata: " + session.duration + " minuti"
            font.pixelSize: 15
            color: "#555"
        }

        Text {
            text: "Stato: " + (session.completed ? "✓ Completata" : "In corso")
            font.pixelSize: 15
            color: session.completed ? "green" : "orange"
        }

        Rectangle { width: parent.width; height: 1; color: "#ddd" }

        // Summary box
        Rectangle {
            width: parent.width
            height: 80
            radius: 8
            color: session.completed ? "#c8e6c9" : "#fff9c4"

            Column {
                anchors.centerIn: parent
                spacing: 6

                Text {
                    text: session.completed ? "Ottimo lavoro! 💪" : "Sessione in corso..."
                    font.pixelSize: 18
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    text: "Hai allenato per " + session.duration + " minuti"
                    font.pixelSize: 13
                    color: "#555"
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
    }
}