#pragma once
#include <string>

// Entity

class Entity {
protected:
	std::string _id_;
	std::string _name_;

public:
	Entity(std::string id, std::string name);
	virtual ~Entity();
	virtual void display_details() const = 0;  // 0 means it's not defined here and must be defined in the derived classes vs. "abstract" in C#

	// getters
	std::string get_id() const { return _id_; }
	std::string get_name() const { return _name_; }

	// setters
	void set_id(std::string new_id) { _id_ = new_id; }
	void set_name(std::string new_name) { _name_ = new_name; }
};