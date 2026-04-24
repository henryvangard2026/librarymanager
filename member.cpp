#include "member.h"
#include <iostream>

// in a class, members are both attribtues (variables) and functions

// constructor

Member::Member(std::string id, std::string name, std::string email, std::string phone)
	: Entity(id, name), _email_(email), _phone_(phone) {}

void Member::display_details() const {  //const means this member function won't modify a member attribute
    std::cout << "Member Info:" << std::endl;
    std::cout << "------------" << std::endl;
    std::cout << "ID: " << get_id() << std::endl;  // id can be used for any class
    std::cout << "Name: " << get_name() << std::endl;
    std::cout << "Email: " << get_email() << std::endl;
    std::cout << "Phone: " << get_phone() << std::endl;
}

