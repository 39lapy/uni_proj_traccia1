import QtQuick
import QtQuick.Controls

Button {
    property StackView stackView
    text: "← Indietro"
    onClicked: stackView.pop()
}