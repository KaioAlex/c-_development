#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "User.hpp"
#include "Student.hpp"
#include <iostream>
#include <string>

class Admin : public User {
    private:
        std::string _password;

    public:
        Admin();

        Admin(std::string, std::string);
        void print_welcome() override;
        std::string get_password();

        virtual ~Admin();
};

#endif
