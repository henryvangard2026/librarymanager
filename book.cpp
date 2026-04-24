#include "book.h"
#include <iostream>

using namespace std;

Book::Book(string id, string title, string author)  // title in Book is name in Entity
	: Entity(id, title), _author_(author) {}

void Book::display_details() const {
	cout << "ID: " << get_id() << endl;
	cout << "Title: " << get_name() << endl;  // title is name in Entity
	cout << "Author: " << _author_ << endl;
	cout << "Status: " << (_is_borrowed_ ? "[OUT]" : "[IN]") << endl;  // if is_borrowed_ (true) then OUT else IN
}
