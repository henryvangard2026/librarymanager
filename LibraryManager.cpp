//
// LibraryManager.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
*
* HOWTO:
* 
* RUN:      Ctrl + F5 or Debug > Start Without Debugging menu
* Debug:    F5 or Debug > Start Debugging menu
* 
* DATE:     April 2, 2026
* 
* TODO:
* 
* 
*/

#include "LibraryManager.h"
#include <iostream>
#include<limits>

#include <string>
#include <cctype> 
#include <regex>

using namespace std;

// Helper functions:
//-----------------------------------------------------------------------------------------------------------------

// 1.  Press Enter to continue ...

void LibraryManager::press_enter_to_continue() const {
    cout << "Press Enter to continue...";
    string dummy;
    getline(cin, dummy);
}

// 2.  Convert id (string) into an UPPER case string if needed (from LOWER case characters to UPPER case characters)

void LibraryManager::to_upper(std::string& id) {
    
    /*  Professional version:
    *
    *
    for (auto& c : id) {
        //c = static_cast<char>(::toupper(static_cast<unsigned char>(c)));  // professional UPPER casting
    }
    *
    * 
    */

    // original C/C++ 30 years ago
    for (int i = 0; i < id.length(); i++) {
        if (id[i] >= 97 && id[i] <= 122) {  // only use characters between those which 'a' - 'z'
            id[i] -= 32;  // subtracting 32 to get to 'A' - 'Z'
        }
    }
}

// 3.  Validate and format phone into XXX-YYY-ZZZZ

bool LibraryManager::validate_phone(string& phone) {
    // regex:  3 digits, optional dash, 3 digits, optional dash, 4 digits
    std::regex pattern(R"(^(\d{3})-?(\d{3})-?(\d{4})$)");  // each () captures a group so 3 groups:  XXX, XXX, XXXX

    // is there a match?
    if (std::regex_match(phone, pattern)) {
        // there is, captured groups ($1, $2, $3)
        phone = std::regex_replace(phone, pattern, "$1-$2-$3");  // reformat phone since it matched pattern
        return true;  // valid phone format:  651-222-3344
    }
    else
        return false;  // invalid phone format
}

// QML
//-----------------------------------------------------------------------------------------------------------------

Q_INVOKABLE void LibraryManager::add_book_gui(QString id, QString title, QString author) {




}

// Menu
//-----------------------------------------------------------------------------------------------------------------

void LibraryManager::menu() {
    string input;  // this will read in the input as raw string
    int choice = 0;

    while (true) {
        cout << "Library Manager:" << endl;
        cout << "----------------" << endl << endl;
        cout << "1. Add a Book" << endl;
        cout << "2. Add a Member" << endl;
        cout << "3. Borrow a Book" << endl;
        cout << "4. Return a Book" << endl;
        cout << "5. List all Books" << endl;
        cout << "6. Exit" << endl;
        cout << "----------------" << endl << endl;
        cout << "Please enter a number (1-6): ";  // no endl so the user enters the number right after the colon
        getline(cin, input);  // gets the whole string like in Python 

        // convert string raw_input into an int (choice)
        try {
            choice = stoi(input);
        }
        catch (...) {  // ... catches all exception types
            cout << endl << "Invalid input!" << endl;
            press_enter_to_continue();
            continue;
        }

        switch (choice) {
        case 1: add_book(); break;
        case 2: add_member(); break;
        case 3: borrow_book(); break;
        case 4: return_book(); break;
        case 5: list_books(); break;
        case 6: cout << "Exiting...\n"; return;
        default: 
            cout << "Invalid input!  Please enter a number (1-6)." << choice << endl; 
            press_enter_to_continue();
            break;
        }
    }
}

// Add a book
void LibraryManager::add_book() {
    string id, title, author;

    cout << "Add a Book:" << endl;
    cout << "-----------" << endl << endl;
    cout << "ID: ";
    getline(cin, id);
    to_upper(id);  // convert UPPER case

    cout << "Title: ";
    getline(cin, title);    
    to_upper(title);  // convert UPPER case

    cout << "Author: ";
    getline(cin, author);
    to_upper(author);  // convert UPPER case

    books.push_back(Book(id, title, author));  // creates a book from Book then add it to the books vector (database)
    cout << "\nSuccess: " << title << " added to the library." << endl;

    press_enter_to_continue();
}

// Add a member

void LibraryManager::add_member() {
    string id, name, email, phone;

    cout << "Add a Member:" << endl;
    cout << "-------------" << endl << endl;
    cout << "ID: ";
    getline(cin, id);
    to_upper(id);  // convert UPPER case

    cout << "Full Name: ";
    getline(cin, name);

    cout << "Email: ";
    getline(cin, email);
    // convert UPPER case

    cout << "Phone in format (651-222-3344): ";
    getline(cin, phone);
    if (!validate_phone(phone)) {
        cout << "ERROR:  Invalid phone number: " << phone << endl;
        press_enter_to_continue();
        return;  // return from add a member
    }

    members.push_back(Member(id, name, email, phone));  // creates a book from Book then add it to the books vector (database)
    cout << "\nSuccess: " << name << " added to the libary." << endl;

    press_enter_to_continue();
}

// List the books

void LibraryManager::list_books() const {
    if (books.empty()) {
        cout << "(The library is empy!)" << endl;
    }
    else {
        cout << "Libary Catalog:" << endl;
        cout << "---------------" << endl;

        for (const auto& book : books) {  // use const auto& so that book at the address auto& can't be changed const
            book.display_details();
            cout << "---------------" << endl;
        }
    }
}

// Borrow a book (by id)
//
// Defensive Programming
//

void LibraryManager::borrow_book() {
    string id;

    while (true) {
        cout << "Borrow a Book:" << endl;
        cout << "--------------" << endl << endl;
        cout << "Enter a book ID (r/R to return to Main Menu): ";
        getline(cin, id);  // get the whole string        
        to_upper(id); // Normalizing input so 'b001' becomes 'B001'

        // returning to the Main Menu 
        if (id == "r" || id == "R") {
            cout << "You're returning to the main menu." << endl;
            press_enter_to_continue();
            return;  // return to the main menu
        }

        // perform sanity checks: 

        // the user press Enter (the id is empty)
        if (id.empty()) {
            cout << "ERROR:  ID cannot be empty." << endl;
            press_enter_to_continue();
            continue;
        }

        bool found = false;
        for (auto& b : books) {
            if (b.get_id() == id) {  
                found = true;

                if (b.borrowed()) {  // it is checked OUT (_is_borrowed_ is true)
                    cout << "ERROR:  Book ID: " << id << " is checked OUT.  Can't borrow it." << endl;
                }
                else {
                    b.borrowed(true);  // it is checked OUT now, set _is_borrowed_ to true
                    cout << "SUCCESS:  Book ID "  << id << " is now checked OUT.  You've just borrowed it." << endl;

                }
                // common path for matched id
                press_enter_to_continue();
                break;
            }
        
        }

        // it's not found, try again with the opportunity to return to the Main Menu
        if (!found) {
            cout << "ERROR:  Book ID: " << id << " is not found!" << endl;
            press_enter_to_continue();
            continue;  // loop back for borrow a book menu 
        }
    }
}

// Return a book (by id)

void LibraryManager::return_book() {
    string id;

    while (true) {
        cout << "Borrow a Book:" << endl;
        cout << "--------------" << endl << endl;
        cout << "Enter a book ID to RETURN (r/R to return to Main Menu): ";
        getline(cin, id);
        to_upper(id); // Normalizing input so 'b001' becomes 'B001'

        // returning to the Main Menu 
        if (id == "r" || id == "R") {
            cout << "You're returning to the main menu." << endl;
            press_enter_to_continue();
            return;  // return to the main menu
        }

        // perform sanity checks: 

        // the user press Enter (the id is empty)
        if (id.empty()) {
            cout << "ERROR: ID cannot be empty." << endl;
            press_enter_to_continue();
            continue;
        }

        bool found = false;
        for (auto& b : books) {
            if (b.get_id() == id) {
                found = true;

                if (!b.borrowed()) {  // it is checked IN (_is_borrowed_ is false)... NOT checked OUT
                    cout << "ERROR:  Book ID: " << id << " is already IN the library.  Can't return it." << endl;
                }
                else {
                    b.borrowed(false);  // it is checked IN now, set _is_borrowed_ to false
                    cout << "SUCCESS: Book ID " << id << " has been returned to the shelf.  You've just returned it." << endl;
                }
                // common path for matched id
                press_enter_to_continue();
                break; 
            }
        }

        // it's not found, try again with the opportunity to return to the Main Menu
        if (!found) {
            cout << "ERROR: Book ID: " << id << " is not found!" << endl;
            press_enter_to_continue();
            continue; // loop back to the return a book menu
        }
    }


}

// main  (has been removed because there is now main.cpp, 4/4/26
//-----------------------------------------------------------------------------------------------------------------

/*
* 
int main() {
    LibraryManager manager;     // create a library 
    manager.menu();             // start the menu
    
    //* 
    //* 
    // Running tests: 
    // --------------

    // Test Book
    Book hobbit("B001", "The Hobbit", "J.R.R. Tolkien");
    cout << "=== Book Test ===" << endl;
    hobbit.display_details();
    cout << endl;

    // Test Member
    Member henry("M001", "Henry Vangard", "henry@abc.com", "651-444-1234");
    cout << "=== Member Test ===" << endl;
    henry.display_details();
    cout << endl;
    //*
    //*

    return 0;
}
*
*/

