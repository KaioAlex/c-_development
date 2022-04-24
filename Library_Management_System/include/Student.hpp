#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "User.hpp"
#include <memory>
#include <string>
#include "Book.hpp"
#include <vector>

class Student : public User{
    private:
        std::string books_file;
        unsigned int id;
        void read_books();
        std::vector<std::shared_ptr<Book>> books;
    public:
        Student(unsigned int,std::string);

        std::vector<std::shared_ptr<Book>> get_books();      //Retorna o vector books para System
        void set_one_book_in_books(std::shared_ptr<Book>);
        void set_books(std::vector<std::shared_ptr<Book>>);  // setar o vector de livros inteiro
        unsigned int get_id();
        void print_welcome(){};
        
        virtual ~Student();

};

#endif
