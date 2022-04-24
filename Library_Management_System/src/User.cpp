#include "User.hpp"
#include <string>

User::User(std::string name) {
    this->_name = name;
}

User::User() {

}

void User::set_name(std::string username){
    this->_name = username;
}

std::string User::get_name(){
    return _name;
}

User::~User() {
}
