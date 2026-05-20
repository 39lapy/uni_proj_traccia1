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

    Text {
        anchors.centerIn: parent
        text: "Coming soon"
        font.pixelSize: 18
        color: "#aaa"
    }
}