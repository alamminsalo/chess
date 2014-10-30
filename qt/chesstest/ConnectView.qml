import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 600
    height: 600
    minimumWidth: 600
    minimumHeight: 600
    maximumHeight: 600
    maximumWidth: 600
    title: qsTr("Main Menu")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
        Menu{
            title: qsTr("Edit")
            MenuItem {
                text: qsTr("entry0")
            }
            MenuItem{
                text: qsTr("entry1")
            }
        }
    }

    Text {
        width: 252
        height: 43
        text: qsTr("Connect to server")
        font.family: "Verdana"
        font.pointSize: 21
        anchors.verticalCenterOffset: -215
        anchors.horizontalCenterOffset: 0
        anchors.centerIn: parent
    }

    TextField {
        id: textField1
        x: 174
        y: 226
        width: 174
        height: 25
        placeholderText: qsTr("Text Field")
    }

    TextField {
        id: textField2
        x: 361
        y: 226
        width: 65
        height: 25
        placeholderText: qsTr("Text Field")
    }

    Text {
        id: text1
        x: 174
        y: 199
        width: 27
        height: 15
        text: qsTr("IP")
        font.family: "Verdana"
        font.pixelSize: 12
    }

    Text {
        id: text2
        x: 361
        y: 199
        width: 27
        height: 15
        text: qsTr("Port")
        font.pixelSize: 12
        font.family: "Verdana"
    }

    Button {
        id: button1
        x: 341
        y: 281
        text: qsTr("Connect")
    }

    Button {
        id: button2
        x: 440
        y: 500
        width: 92
        height: 27
        text: qsTr("Back")
        MouseArea{
            anchors.fill: parent
            onClicked: pageLoader.source = "qrc:/MainView.qml"
        }
    }
}
