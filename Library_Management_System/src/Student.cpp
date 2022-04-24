#include "Student.hpp"
#include <fstream>
#include "System.hpp"

/**
*Construtor da class student, cria um arquivo onde seram guardados os livros do aluno, caso nao exista
*caso exista, le os livros que o aluno pegou emprestado
*@param id Matrícula do aluno
*@param name Nome do Aluno
*/
Student::Student(unsigned int id,std::string name){                   // Construtor de Student
    this->_name = name;
    this->id = id;

    //arquivo de texto com os livros de cada aluno
    //o nome do arquivo e igual id do aluno
    //o arquivo é criado automaticamente caso não exista

    this->books_file = "Alunos//" + std::to_string(id) + ".txt";

    std::ofstream saida;
    saida.open(books_file,std::ofstream::out | std::ofstream::app);

    //inicializar o vector de books com os livros do arquivos
    read_books();

    saida.close();
}


//! Le todos o livros guardados no arquivo de aluno para guardar em um vector
void Student::read_books(){

    //nao e pra usar esse metodo duas vezes no memso aluno
    //mas se usar nao tem problema
    this->books.clear();

    std::ifstream f;                                        // Abrindo para leitura do arquivo
    f.open(this->books_file);

    std::string isbn;
    while(f>>isbn){
        this->books.push_back(System::get_book(isbn, 0));  // get_book retorna um objeto do livro encontrado no acervo
        // std::cout << "Tamanho = " << isbn.length() << "\n" + isbn << "\n";
        // std::cout << isbn << std::endl;

        f>>isbn;

    }

    f.close();
}

//!@ return Retorna id do aluno
unsigned int Student::get_id(){
    return this->id;
}

//!@ return Retorna os livros do aluno
std::vector<std::shared_ptr<Book>> Student::get_books(){
    return this-> books;
}

//! Coloca um livro na lista privada de livros do aluno
void Student::set_books(std::vector<std::shared_ptr<Book>> books_received){
    this->books = books_received;
}

//! Coloca um livro na lista privada de livros do aluno
void Student::set_one_book_in_books(std::shared_ptr<Book> book_received){
    this->books.push_back(book_received);
}


Student::~Student(){

}
