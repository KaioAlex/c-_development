#include "Book.hpp"

#include <iostream>
#include <fstream>
#include "time.h"

using namespace std;

Book::Book(){

}

//! Construtor do livro usando somente o isbn
Book::Book(std::string isbn){
    this->isbn = isbn;
}

//! Construtor do livro inicializa um livro com as informações encontradas no arquivo book.txt
Book::Book(std::string title,std::string author, std::string isbn,int amount){
    this->isbn = isbn;
    this->title = title;
    this->author = author;
    this->amountOwned = amount;
}

int Book::get_amount(){
    return this->amountOwned;
}

//! Devolve o livro, verifica se o livro existe na lista do aluno,
//! e se exister retira do arquivo de texto do aluno, adiciona 1 a quantidade possuida.
//! Calcula a multa para o aluno case ele tenha passado do prazo de devolução.
void Book::return_book(int id){

    ifstream books;                                          // Abrindo pra leitura
    string file = "Alunos//";
    file.append(to_string(id));
    file.append(".txt");
    books.open(file);
    ofstream buffer;                                        // Abrindo pra escrita
    buffer.open("Alunos//buffer.txt",std::ofstream::out | std::ofstream::app);

    string s;
    bool found = false;
    while(books>>s){

        if(s == isbn){
            found = true;
            books>>s;

            if(stoll(s)<time(0)){

                    int fine = ((time(0) - stoll(s))/(24*60*60)) +1;
                    cout<<"\nPENDÊNCIA: Aluno com livro atrasado multa de R$"<<fine<<endl;}

        }

        else{

            buffer<<s<<" ";
            books>>s;
            buffer<<s<<endl;

        }

    }

    books.close();
    buffer.close();

    remove(file.c_str());
    rename("Alunos//buffer.txt",file.c_str());

    int dashcount = 0;
    bool skip= false;

    books.open("Acervo-de-Livros//books.txt");
    buffer.open("Acervo-de-Livros//buffer.txt",std::ofstream::out | std::ofstream::app);

    if(found){
        do{

            books>>s;
            buffer<<s;
            buffer<<" ";

            if(skip){
                buffer<<endl;
                skip = !skip;
            }

            if(s == "-") dashcount++;
            if(!(dashcount%3) && dashcount) {skip = true;dashcount = 0;}
    }while(s != isbn);

        amountOwned++;
        buffer << "- ";
        dashcount = 0;
        buffer<<amountOwned;
        buffer<< '\n';
        books>>s;
        books>>s;

        while(books>>s){

            buffer<<s;
            buffer<<" ";

            if(skip){

                buffer<<endl;
                skip = !skip;
            }

            if(s == "-") dashcount++;
            if(!(dashcount%3) && dashcount) {skip = true;dashcount = 0;}

        }

        buffer.close();
        books.close();

        remove("Acervo-de-Livros//books.txt");
        rename("Acervo-de-Livros//buffer.txt","Acervo-de-Livros//books.txt");

    }

}

//!@return Retorna o isbn
std::string Book::get_isbn(){
    return this->isbn;
}

void Book::set_isbn(std::string isbn){
    this->isbn = isbn;
}

//!@return Retorna o título do livro
std::string Book::get_title(){
    return this->title;
}

//!@return Retorna o autor do livro
std::string Book::get_author(){
    return this->author;
}

//! Verifica se o livro pode ser emprestado
bool Book::can_borrow(){
    return amountOwned > 0;
}

//! Empresta o livro para o aluno, removendo 1 da quantidade possuida.
void Book::borrow() {
    remove("Acervo-de-Livros//buffer.txt");

    ofstream buffer;
    ifstream books;

    string s;

    buffer.open("Acervo-de-Livros//buffer.txt",std::ofstream::out | std::ofstream::app);
    books.open("Acervo-de-Livros//books.txt");

    int dashcount = 0;
    bool skip= false;

    do{

        books>>s;
        buffer<<s;
        buffer<<" ";

        if(skip){

            buffer<<endl;
            skip = !skip;
        }

        if(s == "-") dashcount++;
        if(!(dashcount%3) && dashcount) {skip = true;dashcount = 0;}

    }while(s != isbn);

    amountOwned--;
    buffer << "- ";
    dashcount = 0;
    buffer<<amountOwned;
    buffer<< '\n';
    books>>s;
    books>>s;

    while(books>>s){

        buffer<<s;
        buffer<<" ";

        if(skip){

            buffer<<endl;
            skip = !skip;
        }

        if(s == "-") dashcount++;
        if(!(dashcount%3) && dashcount) {skip = true;dashcount = 0;}
    }

    buffer.close();
    books.close();

    remove("Acervo-de-Livros//books.txt");
    rename("Acervo-de-Livros//buffer.txt","Acervo-de-Livros//books.txt");

}

Book::~Book()
{
    
}
