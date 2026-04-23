#include "member.h"
#include <iostream>

// in a class, members are both attribtues (variables) and functions

// constructor

Member::Member(std::string id, std::string name, std::string email, std::string phone)
	: Entity(id, name), _email_(email), _phone_(phone) {}

void Member::display_details() const {  //const means this member function won't modify a member attribute
    std::cout << "Member Info:" << std::endl;
    std::cout << "ID: " << _id_ << std::endl;  // id can be used for any class
    std::cout << "Name: " << _name_ << std::endl;
    std::cout << "Email: " << _email_ << std::endl;
    std::cout << "Phone: " << _phone_ << std::endl;
}

