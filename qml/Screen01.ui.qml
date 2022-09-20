

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.2
import QtQuick.Controls 6.2
//import COM_Controller

Rectangle {
    id: rectangle
    width: 580
    height: 790
    color: "#c2c2c2"
    gradient: Gradient {
        orientation: Gradient.Vertical
        GradientStop {
            position: 0
            color: "#bdc2e8"
        }

        GradientStop {
            position: 0.01
            color: "#bdc2e8"
        }

        GradientStop {
            position: 1
            color: "#e6dee9"
        }
    }

    DelayButton {
        id: red_Light
        x: 27
        y: 92
        width: 100
        height: 100
        opacity: 1
        text: qsTr("RED")
        enabled: true
        smooth: true
        icon.cache: false
        autoRepeat: false
        autoExclusive: false
        checked: false
        delay: 5
        topInset: 0
        font.bold: true
        font.pointSize: 11
        font.family: "Tahoma"
        clip: false
        icon.color: "#ff0000"
        checkable: false
        display: AbstractButton.TextUnderIcon
    }

    Button {
        id: sendButton
        x: 454
        y: 707
        width: 95
        height: 40
        text: qsTr("Отправить")
    }

    DelayButton {
        id: blue_Light
        x: 305
        y: 92
        width: 100
        height: 100
        opacity: 1
        text: qsTr("BLUE")
        delay: 5
        font.family: "Tahoma"
        font.pointSize: 11
        icon.color: "#ff0000"
        topInset: 0
        checkable: false
        font.bold: true
        display: AbstractButton.TextUnderIcon
        clip: false
    }

    DelayButton {
        id: orange_Light
        x: 449
        y: 92
        width: 100
        height: 100
        opacity: 1
        text: qsTr("ORANGE")
        delay: 5
        font.family: "Tahoma"
        font.pointSize: 11
        icon.color: "#ff0000"
        topInset: 0
        checkable: false
        font.bold: true
        display: AbstractButton.TextUnderIcon
        clip: false
    }

    DelayButton {
        id: green_Light
        x: 167
        y: 92
        width: 100
        height: 100
        opacity: 1
        text: qsTr("GREEN")
        delay: 5
        font.family: "Tahoma"
        font.pointSize: 11
        icon.color: "#ff0000"
        topInset: 0
        checkable: false
        font.bold: true
        display: AbstractButton.TextUnderIcon
        clip: false
    }

    Slider {
        id: orangeSlider
        x: 449
        y: 198
        width: 100
        height: 36
        value: 0.5
    }

    Slider {
        id: greenSlider
        x: 167
        y: 198
        width: 100
        height: 36
        value: 0.5
    }

    Slider {
        id: redSlider
        x: 27
        y: 198
        width: 100
        height: 36
        value: 0.5
    }

    Slider {
        id: blueSlider
        x: 305
        y: 198
        width: 100
        height: 36
        value: 0.5
    }

    Label {
        id: label
        x: 472
        y: 240
        text: qsTr("Яркость")
    }

    Label {
        id: label1
        x: 190
        y: 240
        text: qsTr("Яркость")
    }

    Label {
        id: label2
        x: 50
        y: 240
        text: qsTr("Яркость")
    }

    Label {
        id: label3
        x: 325
        y: 240
        width: 60
        height: 31
        text: qsTr("Яркость")
    }

    Label {
        id: label4
        x: 27
        y: 28
        text: qsTr("Управление светодиодами")
        font.pointSize: 14
    }

    Label {
        id: label5
        x: 27
        y: 317
        text: qsTr("Управление сервоприводом")
        font.pointSize: 14
    }

    Slider {
        id: servoSlider
        x: 94
        y: 373
        width: 334
        height: 76
        value: 0.5
    }

    Label {
        id: label6
        x: 66
        y: 395
        width: 22
        height: 31
        text: qsTr("0°")
        font.pointSize: 18
    }

    Label {
        id: label7
        x: 434
        y: 395
        width: 22
        height: 31
        text: qsTr("180°")
        font.pointSize: 18
    }

    TextField {
        id: commandField
        x: 27
        y: 707
        width: 406
        height: 40
        placeholderText: qsTr("Команда")
    }

    ToolSeparator {
        id: toolSeparator
        x: 0
        y: 60
        width: 580
        height: 26
    }

    ToolSeparator {
        id: toolSeparator1
        x: 0
        y: 266
        width: 580
        height: 26
    }

    ToolSeparator {
        id: toolSeparator2
        x: 0
        y: 349
        width: 580
        height: 26
    }

    ToolSeparator {
        id: toolSeparator3
        x: 0
        y: 448
        width: 580
        height: 26
    }

    ComboBox {
        id: portBox
        x: 27
        y: 654
        width: 120
        height: 40
        displayText: "Port"
        currentIndex: -1
    }

    Label {
        id: label8
        x: 27
        y: 590
        text: qsTr("Отправить в порт")
        font.pointSize: 14
    }

    ComboBox {
        id: baudRateBox
        x: 170
        y: 654
        width: 120
        height: 40
        displayText: "BaundRate"
        textRole: ""
        editable: false
        currentIndex: -1
    }

    ToolSeparator {
        id: toolSeparator4
        x: 0
        y: 622
        width: 580
        height: 26
    }

    ToolSeparator {
        id: toolSeparator5
        x: 0
        y: 753
        width: 580
        height: 26
    }
}
