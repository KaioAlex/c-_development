#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
    protected:
        std::string _name;

    public:
        User();
        User(std::string);

        void set_name(std::string);
        std::string get_name();

        virtual void print_welcome() = 0;

        virtual ~User();

};

#endif
