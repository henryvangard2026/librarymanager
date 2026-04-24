#pragma once

#include "entity.h"

class Book : public Entity {
private:
    std::string _author_;
    bool _is_borrowed_ = false;  // if a book is borrowed, initialized to false

public:
    Book(std::string id, std::string name, std::string author);  // name in Book is the title which is name in Entity

    // setters:
    void set_author(const std::string& author) { _author_ = author; }  
    void set_borrowed(bool status) { _is_borrowed_ = status; }  // status is true if it is borrowed and false if it is not borrowed 

    // getters:
    std::string get_author() const { return _author_; }
    bool get_borrowed() const { return _is_borrowed_; }  // _is_borrowed_ is a private member so only can use this to access it

    void display_details() const override;
};
