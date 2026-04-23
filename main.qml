import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 600
    height: 400
    title: "Library Manager Professional"

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "Welcome to the Library System"
            font.pointSize: 20
        }

        Button {
            text: "Add New Book"
            onClicked: {
                console.log("Button Clicked!")
                // This is where we will call backend.add_book_gui() later
            }
        }
    }
}