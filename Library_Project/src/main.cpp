// Main do Sistema de Bibliotecas
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <fstream>

// Include das Classes
#include "System.hpp"
#include "Admin.hpp"
#include "Exceptions.hpp"
#include "Book.hpp"
#include "Student.hpp"
#include "User.hpp"
#include "time.h"

//static vector de estudantes
std::vector<std::shared_ptr<Student>> System::students;
std::list<std::shared_ptr<Admin>> System::admin;

using namespace std;

int main() {

    System::init_list();                        // Inicia lista de Adminstradores

    std::shared_ptr<Admin> a (System::login()); // a aponta para o "objeto" que logou no sistema

    System::init_students();                    // Método que pega os nomes dos estudantes em students.txt e coloca como objetos no vector System::students

    System::show_menu();

    return 0;
}
