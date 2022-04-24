// Implementação das exceções
#include "Exceptions.hpp"

//! Exceção jogada se a matrícula não for encontrada
//!@return Retorna Matrícula não encontrada!\n
const char* InvalidIdException::what() const throw() {
  return "\n\tMatrícula não encontrada!\n";
}

//! Exceção jogada se o livro não for encontrado
//!@return Retorna Livro não encontrado!\n
const char* InvalidBookException::what() const throw() {
    return "\n\tLivro não encontrado!\n";
}

//! Exceção jogada se não houver nenhuma quantidade disponível deste livro para empréstimo.
//!@return Retorna Não há nenhuma quantidade disponível deste livro para empréstimo."
const char* EmptyBook::what() const throw() {
  return "\n\tNão há nenhuma quantidade disponível deste livro para empréstimo.";
}
