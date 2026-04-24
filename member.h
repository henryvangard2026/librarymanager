#pragma once

#include "entity.h"
#include <string>

class Member : public Entity {
private:
	std::string _email_;
	std::string _phone_;

public:
	Member(std::string id, std::string name, std::string email, std::string phone);

	void display_details() const override;  // const for it won't change attributes (variables) of the class, override means it has to be defined 

	// setters
	void set_email(const std::string& new_email) { _email_ = new_email; }
	void set_phone(const std::string& new_phone) { _phone_ = new_phone; }

	// getters
	std::string get_email() const { return _email_; }
	std::string get_phone() const { return _phone_; }

};