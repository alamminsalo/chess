import QtQuick 2.3
import QtQuick.Controls 1.2
import SqlConnector 1.0


ApplicationWindow {
    visible: true
    width: 600
    height: 600
    minimumWidth: 600
    minimumHeight: 600
    maximumHeight: 600
    maximumWidth: 600
    title: qsTr("Database Viewer")

    SqlConnector{
        id:sqlconnector
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

    Text {
        id: status
        x: 29
        y: 21
        width: 114
        height: 15
        text: (sqlconnector.connectToDatabase("localhost","chess","antti","ebin") ? "Connected" : "Connecting...")
        font.pixelSize: 12
    }
}
