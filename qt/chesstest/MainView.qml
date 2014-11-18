import QtQuick 2.3
import QtQuick.Controls 1.2
import StartExternal 1.0

ApplicationWindow {
    id: mainView
    visible: true
    width: 600
    height: 600
    minimumWidth: 600
    minimumHeight: 600
    maximumHeight: 600
    maximumWidth: 600
    title: qsTr("Main Menu")

    StartExternal{
        id: gameview
    }

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
        width: 152
        height: 43
        text: qsTr("Main Menu")
        font.family: "Verdana"
        font.pointSize: 21
        anchors.verticalCenterOffset: -218
        anchors.horizontalCenterOffset: 0
        anchors.centerIn: parent
    }

    Button {
        id: button1
        x: 254
        y: 203
        width: 92
        height: 27
        text: qsTr("Local Game")
        tooltip: "Start a game locally"
        activeFocusOnPress: false
        enabled: true
        MouseArea{
            anchors.fill: parent
            onClicked: {
                gameview.start("local");
                Qt.quit();
            }

        }
    }

    Button {
        id: button2
        x: 254
        y: 258
        text: qsTr("Online Game")
        tooltip: "Connect to a server"
        MouseArea{
            anchors.fill: parent
            onClicked: pageLoader.source = "qrc:/ConnectView.qml"
        }

    }

    Button {
        id: button3
        x: 440
        y: 500
        width: 92
        height: 27
        text: qsTr("Quit")
        enabled: true
        MouseArea{
            anchors.rightMargin: 0
            anchors.bottomMargin: 1
            anchors.leftMargin: 0
            anchors.topMargin: -1
            anchors.fill: parent
            onClicked: Qt.quit();
        }
    }

    Button {
        id: button4
        x: 254
        y: 376
        width: 92
        height: 27
        text: qsTr("Settings")
        MouseArea{
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.fill: parent
            onClicked: pageLoader.source = "qrc:/SettingsView.qml"

        }
    }

    Button {
        id: button5
        x: 254
        y: 316
        width: 92
        height: 27
        text: qsTr("Scores")
        MouseArea{
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.fill: parent
            onClicked: pageLoader.source = "qrc:/DBView.qml"

        }
    }
}
