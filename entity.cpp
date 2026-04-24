#include "entity.h"

using namespace std;

/* 
*
* Old School:
* 
Entity(string id, string name) {
	this->id = id;
	this->name = name;
}
*
* 
* 
**/

Entity::Entity(string id, string name) 
	: _id_(id), _name_(name) {}

Entity::~Entity() {}