#include "Admin.hpp"
#include <string>

Admin::Admin(){}

//! Construtor do Admnistrador
//! @param username Nome
//! @param username Senha
Admin::Admin(std::string username, std::string passwd) {
    set_name(username);
    this->_password = passwd;
}

//! Escreve Seja Bem-Vindo + nome do administrador
void Admin::print_welcome(){
    std::cout << "Seja Bem-Vindo, " << this->_name << "!" << std::endl;
}

//!@return Retorn a senha do administrador 
std::string Admin::get_password(){
    return _password;
}

Admin::~Admin() {

}
