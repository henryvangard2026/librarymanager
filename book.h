#pragma once

#include "entity.h"

class Book : public Entity {
private:
    std::string _author_;
    bool _is_borrowed_ = false;  // if a book is borrowed initialized to false

public:
    Book(std::string id, std::string name, std::string author);

    // getter
    bool borrowed() const { return _is_borrowed_; }  // _is_borrowed_ is a private member so only can use this to access it

    // settter
    void borrowed(bool status) { _is_borrowed_ = status; }  // status is borrowed true or not borrowed false

    // getter for author
    std::string author() const { return _author_; }

    void display_details() const override;
};
