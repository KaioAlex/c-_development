#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "Admin.hpp"
#include "Student.hpp"

#include <thread>         // std::this_thread::sleep_for       // Fazer o programa pausar por um tempo
#include <chrono>         // std::chrono::seconds
#include <algorithm>
#include <cstdlib>        // system("CLS")

#include <memory>         // Smart Pointers
#include <iostream>
#include <list>
#include <vector>
#include "Book.hpp"

class System {
    private:
        static std::list<std::shared_ptr<Admin>> admin; // Lista de Adminstradores
        static std::string student_file;
        static std::vector<std::shared_ptr<Student>> students; // Vector de alunos

    public:
        static void init_list();
        static std::shared_ptr<Admin> login();;
        static void init_students();

        static int get_admin_size();
        static int show_menu();
        static int borrow_book();
        static std::shared_ptr<Book> get_book(std::string, int);       // o atributo int é como uma flag para dizer se vai procurar o livro na opção 1 ou 2 do menu
		static int return_book();
        static int show_adm_menu();


};

#endif
