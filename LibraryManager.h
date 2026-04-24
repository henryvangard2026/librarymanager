#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// QT GUI

#include <QObject>      // Required for GUI integration
#include <QString>      // Qt's string type for the interface

#include <QVariantList>
//#include <QVariant>
//#include <QMetaType>

// sql

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "entity.h"
#include "book.h"
#include "member.h"

// Library Manager

class LibraryManager : public QObject {
	Q_OBJECT


private:
	QSqlDatabase db;  // SQLite database
	std::vector<Book> books;	// all the books of class Book
	std::vector<Member> members;	// all the members of class Member

	void initDatabase();

public:
	// Constructor 
	explicit LibraryManager(QObject* parent = nullptr) : QObject(parent) {

		/* Before integrating SQLite:  4/22/26
		*  -----------------------------------
		
		// sample books
		books.push_back(Book("B001", "THE HOBBIT", "J.R.R. TOLKIEN"));
		books.push_back(Book("B002", "CLEAN CODE", "ROBERT MARTIN"));
		books.push_back(Book("B003", "THE PRAGMATIC PROGRAMMER", "DAVID THOMAS"));
		books.push_back(Book("B004", "DESIGN PATTERNS", "GANG OF FOUR"));
		books.push_back(Book("B005", "INTRODUCTION TO ALGORITHMS", "THOMAS CORMEN"));
		books.push_back(Book("B006", "THE C++ PROGRAMMING LANGUAGE", "BJARNE STROUSTRUP"));
		books.push_back(Book("B007", "CODE COMPLETE", "STEVE MCCONNELL"));
		books.push_back(Book("B008", "CRACKING THE CODING INTERVIEW", "GAYLE MCDOWELL"));
		books.push_back(Book("B009", "STRUCTURE AND INTERPRETATION", "HAROLD ABELSON"));
		books.push_back(Book("B010", "THE MYTHICAL MAN MONTH", "FREDERICK BROOKS"));
		
		*/

		// Integrating SQLite:  4/22/26
		// ----------------------------

		initDatabase();

		// only see if books table is empty
		QSqlQuery query;
		query.exec("SELECT COUNT(*) FROM books");
		query.next();
		int count = query.value(0).toInt();

		if (count == 0) {
			query.exec("INSERT INTO books VALUES ('B001', 'THE HOBBIT',                     'J.R.R. TOLKIEN',    0)");
			query.exec("INSERT INTO books VALUES ('B002', 'CLEAN CODE',                     'ROBERT MARTIN',     0)");
			query.exec("INSERT INTO books VALUES ('B003', 'THE PRAGMATIC PROGRAMMER',       'DAVID THOMAS',      0)");
			query.exec("INSERT INTO books VALUES ('B004', 'DESIGN PATTERNS',                'GANG OF FOUR',      0)");
			query.exec("INSERT INTO books VALUES ('B005', 'INTRODUCTION TO ALGORITHMS',     'THOMAS CORMEN',     0)");
			query.exec("INSERT INTO books VALUES ('B006', 'THE C++ PROGRAMMING LANGUAGE',   'BJARNE STROUSTRUP', 0)");
			query.exec("INSERT INTO books VALUES ('B007', 'CODE COMPLETE',                  'STEVE MCCONNELL',   0)");
			query.exec("INSERT INTO books VALUES ('B008', 'CRACKING THE CODING INTERVIEW',  'GAYLE MCDOWELL',    0)");
			query.exec("INSERT INTO books VALUES ('B009', 'STRUCTURE AND INTERPRETATION',   'HAROLD ABELSON',    0)");
			query.exec("INSERT INTO books VALUES ('B010', 'THE MYTHICAL MAN MONTH',         'FREDERICK BROOKS',  0)");
		}

		// load books from database into vector
		query.exec("SELECT id, title, author, borrowed FROM books");
		while (query.next()) {
			Book b(
				query.value(0).toString().toStdString(),
				query.value(1).toString().toStdString(),
				query.value(2).toString().toStdString()
			);
			b.set_borrowed(query.value(3).toInt() == 1);
			books.push_back(b);
		}
	}

	// GUI (Q_INVOKABLE means it is callable from QML)
	Q_INVOKABLE void add_book_gui(QString id, QString title, QString author);
	Q_INVOKABLE void add_member_gui(QString id, QString name, QString email, QString phone);
	Q_INVOKABLE void borrow_book_gui(QString id);
	Q_INVOKABLE void return_book_gui(QString id);
	Q_INVOKABLE QVariantList list_books_gui();

	// Sorting the list of books by title, author or status, enum class won't work with QML
	enum SortField { 
		SortTitle, 
		SortAuthor, 
		SortStatus };

	Q_ENUM(SortField)

	Q_INVOKABLE void sortBooks(SortField field, bool ascending);

	// CLI
	void add_book();
	void add_member();
	void borrow_book();
	void return_book();
	void list_books() const;
	
	// Helpers
	void press_enter_to_continue() const;
	void to_upper(std::string&);
	bool validate_phone(std::string&);

	// Main Menu
	void menu();

// signals do NOT need to be on the very top below Q_OBJECT
signals:
	void errorOccurred(QString message);
	void memberAdded(QString message);
	void bookBorrowed(QString message);  
	void bookReturned(QString message);
	void booksChanged();

};

Q_DECLARE_METATYPE(LibraryManager*)