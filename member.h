#pragma once

#include "entity.h"
#include <string>

class Member : public Entity {
private:
	std::string _email_;
	std::string _phone_;

public:
	Member(std::string _id_, std::string _name_, std::string _email_, std::string _phone_);
	void display_details() const override;  // const for it won't change attributes (variables) of the class, override means it has to be defined 
	std::string get_email() const { return _email_; }
	std::string get_phone() const { return _phone_; }

	void set_email(std::string new_email) { _email_ = new_email; }
	void set_phone(std::string new_phone) { _phone_ = new_phone; }
};