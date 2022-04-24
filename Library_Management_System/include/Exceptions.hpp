// Classe para tratamento de exeções
#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP
#include <stdexcept>
#include <string>

class InvalidIdException : public std::exception {                   // Exceção matrícula não encontrada
  public:
    virtual const char* what() const throw();
};

class InvalidBookException : public std::exception {                 // Exceção livro não encontrado
  public:
    virtual const char* what() const throw();
};

class EmptyBook : public std::exception {                           // Exceção livro não encontrado
  public:
    virtual const char* what() const throw();
};

#endif
