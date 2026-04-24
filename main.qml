import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

ApplicationWindow {
    id: root
    visible: true
    width: 1100
    height: 600
    title: "Library Manager"
    Material.theme: Material.Dark
    Material.accent: Material.LightBlue

    readonly property int colTitle:  420
    readonly property int colAuthor: 250
    readonly property int colStatus: 120

    // sort by title, author or status flags
    property bool sortAscendingTitle:  true
    property bool sortAscendingAuthor: true
    property bool sortAscendingStatus: true

    ListModel {
        id: libraryModel
        ListElement { bookId: "B001"; title: "The Hobbit";                      author: "J.R.R. Tolkien";       status: "Available" }
        ListElement { bookId: "B002"; title: "Clean Code";                      author: "Robert Martin";        status: "Available" }
        ListElement { bookId: "B003"; title: "The Pragmatic Programmer";        author: "David Thomas";         status: "Available" }
        ListElement { bookId: "B004"; title: "Design Patterns";                 author: "Gang of Four";         status: "Available" }
        ListElement { bookId: "B005"; title: "Introduction to Algorithms";      author: "Thomas Cormen";        status: "Available" }
        ListElement { bookId: "B006"; title: "The C++ Programming Language";    author: "Bjarne Stroustrup";    status: "Available" }
        ListElement { bookId: "B007"; title: "Code Complete";                   author: "Steve McConnell";      status: "Available" }
        ListElement { bookId: "B008"; title: "Cracking the Coding Interview";   author: "Gayle McDowell";       status: "Available" }
        ListElement { bookId: "B009"; title: "Structure and Interpretation";    author: "Harold Abelson";       status: "Available" }
        ListElement { bookId: "B010"; title: "The Mythical Man Month";          author: "Frederick Brooks";     status: "Available" }
    }

    Connections {
        target: backend
        function onErrorOccurred(message)  { statusBar.text = message }
        function onMemberAdded(message)    { statusBar.text = message }
        function onBookBorrowed(message)   { statusBar.text = message; refreshList() }
        function onBookReturned(message)   { statusBar.text = message; refreshList() }
    }

    function refreshList() {
        libraryModel.clear()
        var books = backend.list_books_gui()
        for (var i = 0; i < books.length; i++) {
            libraryModel.append({
                bookId: books[i].id,
                title:  books[i].title,
                author: books[i].author,
                status: books[i].borrowed ? "Borrowed" : "Available"
            })
        }
    }

    // ---- Dialogs -------------------------------------------------------

    // add a book
    Dialog {
        id: addBookDialog
        title: "Add a Book"
        modal: true
        anchors.centerIn: parent
        width: 400
        standardButtons: Dialog.Ok | Dialog.Cancel

        onAccepted: {
            if (bookId.text.trim() === "" || bookTitle.text.trim() === "" || bookAuthor.text.trim() === "") {
                statusBar.text = "ERROR:  All fields are required."
                return
            }
            backend.add_book_gui(
                bookId.text.trim(),
                bookTitle.text.trim(),
                bookAuthor.text.trim()
            )
            statusBar.text = "Success: " + bookTitle.text.trim().toUpperCase() + " added."
            libraryModel.append({
                bookId: bookId.text.trim().toUpperCase(),
                title:  bookTitle.text.trim().toUpperCase(),
                author: bookAuthor.text.trim().toUpperCase(),
                status: "Available"
            })
            bookId.clear(); bookTitle.clear(); bookAuthor.clear()
        }

        onRejected: {
            bookId.clear(); bookTitle.clear(); bookAuthor.clear()
        }

        ColumnLayout {
            width: parent.width
            spacing: 12

            Label { text: "ID:" }
            TextField { id: bookId;     Layout.fillWidth: true; placeholderText: "e.g. B001" }

            Label { text: "Title:" }
            TextField { id: bookTitle;  Layout.fillWidth: true; placeholderText: "e.g. Clean Code" }

            Label { text: "Author:" }
            TextField { id: bookAuthor; Layout.fillWidth: true; placeholderText: "e.g. Robert Martin" }
        }
    }

    // add a member
    Dialog {
        id: addMemberDialog
        title: "Add a Member"
        modal: true
        anchors.centerIn: parent
        width: 400
        standardButtons: Dialog.Ok | Dialog.Cancel

        onAccepted: {
            if (memberId.text.trim() === "" || memberName.text.trim() === "" ||
                memberEmail.text.trim() === "" || memberPhone.text.trim() === "") {
                statusBar.text = "ERROR:  All fields are required."
                return
            }

            backend.add_member_gui(
                memberId.text.trim(),
                memberName.text.trim(),
                memberEmail.text.trim(),
                memberPhone.text.trim()
            )
            memberId.clear(); memberName.clear(); memberEmail.clear(); memberPhone.clear()
        }

        onRejected: {
            memberId.clear(); memberName.clear(); memberEmail.clear(); memberPhone.clear()
        }

        ColumnLayout {
            width: parent.width
            spacing: 12

            Label { text: "ID:" }
            TextField { id: memberId;    Layout.fillWidth: true; placeholderText: "e.g. M001" }

            Label { text: "Full Name:" }
            TextField { id: memberName;  Layout.fillWidth: true; placeholderText: "e.g. Bobby Lee" }

            Label { text: "Email:" }
            TextField { id: memberEmail; Layout.fillWidth: true; placeholderText: "e.g. blee@abc.com" }

            Label { text: "Phone:" }
            TextField { id: memberPhone; Layout.fillWidth: true; placeholderText: "e.g. 651-222-3344" }
        }
    }

    // list all members
    Dialog {
        id: listAllMembersDialog
        title:  "List All Members"

        modal: true
        anchors.centerIn: parent
        width: 400
        standardButtons: Dialog.Ok | Dialog.Cancel

        onAccepted: {
                statusBar.text = "Members listed."

        }

        onRejected: {
                statusBar.text = "Members list cancelled."
        }
    }

    // ---- Main layout ---------------------------------------------------

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 12

        // action buttons:
        // ---------------

        RowLayout {
            Layout.fillWidth: true
            spacing: 8

            // add a book
            Button { text: "Add Book";      Layout.fillWidth: true; highlighted: true; onClicked: addBookDialog.open() }
            


            // borrow a book
            Button {
                text: "Borrow Book"
                Layout.fillWidth: true
                enabled: libraryView.currentIndex >= 0 && libraryModel.get(libraryView.currentIndex).status === "Available"
                onClicked: {
                    var selectedId = libraryModel.get(libraryView.currentIndex).bookId
                    backend.borrow_book_gui(selectedId)
                }
            }

            // return a book
            Button {
                text: "Return Book"
                Layout.fillWidth: true
                enabled: libraryView.currentIndex >= 0 && libraryModel.get(libraryView.currentIndex).status === "Borrowed"
                onClicked: {
                    var selectedId = libraryModel.get(libraryView.currentIndex).bookId
                    backend.return_book_gui(selectedId)
                }
            }

            // list all books
            Button {
                text: "List All Books"
                Layout.fillWidth: true
                onClicked: {
                    refreshList()
                    statusBar.text = "Catalog refreshed from database."
                }
            }

            // add a member
            Button { text: "Add Member";    Layout.fillWidth: true; onClicked: addMemberDialog.open() }

            // list all members
            Button { text: "List All Members";    Layout.fillWidth: true; onClicked: listAllMembersDialog.open() }
        }

        // column headers:
        // ---------------

        Rectangle {
            Layout.fillWidth: true
            height: 32
            color: "#1a1a2e"
            radius: 4

            Row {
                anchors.fill: parent
                anchors.leftMargin: 10
                anchors.rightMargin: 15
                spacing: 0

                // title
                Label {
                    text: "Title"
                    font.bold: true
                    color: "#4fc3f7"
                    width: root.colTitle

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            backend.sortBooks(0, root.sortAscendingTitle)
                            refreshList()
                            root.sortAscendingTitle = !root.sortAscendingTitle
                        }
                    }
                }

                // author
                Label {
                    text: "Author"
                    font.bold: true
                    color: "#4fc3f7"
                    width: root.colAuthor
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            backend.sortBooks(1, root.sortAscendingAuthor)
                            refreshList()
                            root.sortAscendingAuthor = !root.sortAscendingAuthor
                        }
                    }
                }

                // status
                Label {
                    text: "Status"
                    font.bold: true
                    color: "#4fc3f7"
                    width: root.colStatus
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            backend.sortBooks(2, root.sortAscendingStatus)
                            refreshList()
                            root.sortAscendingStatus = !root.sortAscendingStatus
                        }
                    }
                }
            }
        }

        // book list
        Frame {
            Layout.fillWidth: true
            Layout.fillHeight: true
            padding: 0
            background: Rectangle {
                color: "#2d2d2d"
                border.color: "#4fc3f7"
                radius: 4
            }

            ListView {
                id: libraryView
                anchors.fill: parent
                clip: true
                model: libraryModel
                currentIndex: -1

                ScrollIndicator.vertical: ScrollIndicator {}   

                delegate: Item {
                    width: ListView.view.width
                    height: 40

                    MouseArea {                                 
                        anchors.fill: parent
                        onClicked: libraryView.currentIndex = index
                    }

                    Rectangle {
                        anchors.fill: parent
                        anchors.leftMargin: 2
                        anchors.rightMargin: 1
                        color: libraryView.currentIndex === index
                               ? "#1a3a5c"
                               : index % 2 === 0 ? "transparent" : "#353535"
                    }

                    Row {
                        anchors.fill: parent
                        anchors.leftMargin: 10
                        anchors.rightMargin: 15
                        anchors.topMargin: 10
                        anchors.bottomMargin: 10
                        spacing: 0

                        Label {
                            text: model.title
                            elide: Text.ElideRight
                            width: root.colTitle
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Label {
                            text: model.author
                            elide: Text.ElideRight
                            width: root.colAuthor
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Label {
                            text: model.status
                            color: model.status === "Available" ? "#66bb6a" : "#ef5350"
                            font.bold: true
                            width: root.colStatus
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                }  // end delegate
            }  // end ListView
        }  // end Frame

        // status bar
        Label {
            id: statusBar
            Layout.fillWidth: true
            text: "Ready  |  " + libraryModel.count + " book(s) in catalog"
            color: "#888"
            font.pixelSize: 11
        }

    }  // end ColumnLayout
}  // end ApplicationWindow