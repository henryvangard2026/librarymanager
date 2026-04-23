#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// QT GUI

#include <QObject>      // Required for GUI integration
#include <QString>      // Qt's string type for the interface

#include "entity.h"
#include "book.h"
#include "member.h"

// Library Manager

class LibraryManager : public QObject {
	Q_OBJECT  // this macro is private (by default by being at the top) and makes C++ code visible to QML

private:
	std::vector<Book> books;	// all the books of class Book
	std::vector<Member> members;	// all the members of class Member

public:
	// QML:
	
	// Constructor 
	explicit LibraryManager(QObject* parent = nullptr) : QObject(parent) {}

	// GUI API 
	Q_INVOKABLE void add_book_gui(QString id, QString title, QString author);

	// CLI
	void add_book();
	void add_member();
	void borrow_book();
	void return_book();
	void list_books() const;
	
	// Helper Functions:
	void press_enter_to_continue() const;
	void to_upper(std::string&);
	bool validate_phone(std::string&);

	// Main Menu
	void menu();
};