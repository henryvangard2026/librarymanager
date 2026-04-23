#include "book.h"
#include <iostream>

using namespace std;

Book::Book(string id, string name, string author)
	: Entity(id, name), _author_(author) {}

void Book::display_details() const {
	cout << "ID: " << get_id() << endl;
	cout << "Title: " << get_name() << endl;
	cout << "Author: " << _author_ << endl;
	cout << "Status: " << (_is_borrowed_ ? "[OUT]" : "[IN]") << endl;  // if is_borrowed_ (true) then OUT else IN
}
