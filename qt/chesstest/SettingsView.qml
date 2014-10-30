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
        width: 108
        height: 43
        text: qsTr("Settings")
        font.family: "Verdana"
        font.pointSize: 21
        anchors.verticalCenterOffset: -215
        anchors.horizontalCenterOffset: 0
        anchors.centerIn: parent
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

    ComboBox {
        id: comboBox1
        x: 238
        y: 192
    }

    Text {
        id: text1
        x: 238
        y: 171
        text: qsTr("Text")
        font.pixelSize: 12
    }
}
