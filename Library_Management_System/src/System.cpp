#include "System.hpp"
#include "Exceptions.hpp"
#include "time.h"

#include <stdexcept>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

//! Inicializa todos os administradores
void System::init_list() {
    std::shared_ptr<Admin> teste (new Admin("teste", "teste"));
    std::shared_ptr<Admin> caio (new Admin("Caio", "123"));
    std::shared_ptr<Admin> gean (new Admin("Gean", "senha"));
    admin.push_back(teste);    
    admin.push_back(gean);
    admin.push_back(caio); // colocando objeto na lista

}

//! Inicializa todos os estudates registrados nos sistema
//! As informações do estudante são guardadas no arquivo students.txt
void System::init_students(){
    //inicializar a lista de studantes com os estudantes no txt
    string name,string_append;
    string id;
    ifstream entrada;
    entrada.open("Alunos//students.txt");

    while(!entrada.fail()){
        std::getline(entrada, name, '-');

        entrada >> id;                              // lê '\n'
        entrada.ignore();                           // retira \n
        std::shared_ptr<Student>send (new Student(std::stoi(id),name));
        System::students.push_back(send); // método stoi() converte string para int
    }                              // Instanciando objetos Student e colocando no vector System::students

    entrada.close();
}

//! Retorna um objeto Admin que conseguiu logar no sistema
std::shared_ptr<Admin> System::login() {
    std::string username;
    std::string passwd;

    std::shared_ptr<Admin> f; //
    bool flag = false;

    system("clear");
    std::cout << "\t\tINICIALIZANDO... \n";
    std::this_thread::sleep_for (std::chrono::seconds(3));

    system("clear");                                            // Limpar a tela
    std::cout << "\t\tLOGIN\t\t\n";                            // No Windows é system("cls");
    // Fazendo a leitura do username
    int count_tempts = 0;
    do {
        std::cout << "USUÁRIO: ";
        std::cin >> username;

        //Percorrendo a lista para encontrar usuário
        for(std::shared_ptr<Admin> a : admin){
            if(a->get_name() == username){
                f = a;
                flag = true;             // se encontrar seta como 1 e sai
                break;
            }
        }

        if(!flag){
            system("clear");
            std::cout << "\nUsuário Não Existe...\n" << std::endl;
            count_tempts++;
        }
        if(count_tempts >= 3){
            system("clear");
            count_tempts = 0;
            std::cout << "Você errou o usuário por 3 vezes.\nAguarde 10 segundos para tentar novamente.." << std::endl;
            std::this_thread::sleep_for (std::chrono::seconds(10));
            system("clear");
        }

    }while(!flag);

    //Percorrendo para encontrar a senha
    count_tempts = 0;
    do {
        // system("clear");
        std::cout << "SENHA: ";
        std::cin >> passwd;

        if(f->get_password() != passwd){
            system("clear");
            std::cout << "\nSenha Incorreta...\n" << std::endl;
            count_tempts++;
        }
        if(count_tempts >= 3){
            system("clear");
            count_tempts = 0;
            std::cout << "Você errou a senha por 3 vezes.\nAguarde 10 segundos para tentar novamente.." << std::endl;
            std::this_thread::sleep_for (std::chrono::seconds(10));
            system("clear");
        }

    }while(f->get_password() != passwd);
    system("clear");

    f->print_welcome();
    std::this_thread::sleep_for (std::chrono::seconds(2));

    return f;
}

//! @return Retorna tamanho do vetor de aministradores
int System::get_admin_size(){
    return admin.size();
}

/**
* Caso o livro exista, adiciona o livro à lista do aluno, e remove um da quantidade possuida
* e guarda a momento em que o aluno pegou o livro para verificar se ele devolveu dentro do prazo
* Joga exceções InvalidBookException se o livro nao for encontrado e EmptyBook se o livro nao estiver disponínel.
* Também guarda o momento em que o livro foi emprestado +15 dias para verificação do prazo durante a devolução
*/
int System::borrow_book(){                             // 1ª Opção Menu
    std::string isbn_book, id_student;

    try{                                               // Zona de observação
        unsigned int tam = System::students.size();
        bool flag_student = true;

        std::cout << "\n\tEmpréstimo de Livro\n\nDigite matrícula do aluno (digite 'b' para voltar): ";
        std::cin >> id_student;
        if(id_student == "b"){
            return 0;
        }

        unsigned i;                         // Para guardar o i-ésimo estudante encontrado
        for(i = 0; i < tam; i++){
            if(System::students[i]->get_id() == unsigned(std::stoi(id_student))){
                flag_student = false;
                break;
            }
        }

        if(flag_student){                                // Lançamento da exceção de matrícula ñ encontrada
            throw InvalidIdException();
        }

        std::cout << "\nDigite o código do livro: (digite 'b' para voltar): ";
        std::cin >> isbn_book;
        if(isbn_book == "b"){
            return 0;
        }

        std::shared_ptr<Book> b = System::get_book(isbn_book, 1);    // se não achar o livro, lança exceção
        System::students[i]->set_one_book_in_books(b);                  // Colocando no vector de livros do aluno
        b->borrow();                                                    // Método da Classe Book

        std::cout << "\nAguarde...\n";
        std::this_thread::sleep_for (std::chrono::seconds(1));               // Dormir por 3s

        std::ofstream arq;                                        // Abrindo para escrita no arquivo
        arq.open("Alunos//" + id_student + ".txt", ios::app);
        arq << isbn_book <<" " << (time(0)+(15*24*60*60)) << endl;

        arq.close();

        std::cout << "\n\t Livro Emprestado com Sucesso!\n\nIMPORTANTE: Lembre o aluno de que ele possui 15 dias para fazer a Devolução.\n\t    Multa de R$1,00 por cada dia de atraso!\n\n";
        std::this_thread::sleep_for (std::chrono::seconds(5));       

        }
        catch(InvalidIdException& e){
            std::cout << e.what() << "\nDigite 'm' voltar para o Menu ou 'b' para voltar: ";

            std::string ch;
            std::cin >> ch;
            system("clear");

            if(ch == "m"){
                return 0;
            }
            else if(ch == "b"){
                borrow_book();
            }
        }
        catch(InvalidBookException& f){
            std::cout << f.what() << "\nDigite 'm' para ir ao Menu ou 'b' para voltar: ";

            std::string ch;
            std::cin >> ch;
            system("clear");

            if(ch == "m"){
                return 0;
            }
            else if(ch == "b"){
                borrow_book();
            }
        }
        catch(EmptyBook& e){
            std::cout << e.what() << "\nDigite 'm' para ir ao Menu ou 'b' para voltar: ";

            std::string ch;
            std::cin >> ch;
            system("clear");

            if(ch == "m"){
                return 0;
            }
            else if(ch == "b"){
                borrow_book();
            }
        }
        catch(std::invalid_argument& e){
            std::cout << "Entrada Inválida!" << std::endl;
            std::cout << "\nDigite 'm' para ir ao Menu ou 'b' para voltar: ";

            std::string ch;
            std::cin >> ch;
            system("clear");

            if(ch == "m"){
                return 0;
            }
            else if(ch == "b"){
                borrow_book();
            }
        }

    return 0;
}

//! Encontrado o livro especificado na lista de livros e retorna um objeto book com as informações do livro
//! se o livro não for encontrado joga exceção InvalidBookException
//! @return Objeto book com as informações do livro encontrado na lista
//! @param isbn isbn do livro a ser proucurado

std::shared_ptr<Book> System::get_book(std::string isbn, int option){

    //achar o livro com esse isbn na lista de livros

    ifstream f;
    string s,author,title,amount;                            // s == isbn lido
    f.open("Acervo-de-Livros//books.txt");

    do {
        s = "";        // Precisa esvaziar a string para não acumular com os append na hora da busca pelo livro
        author = "";
        title = "";
        amount = "";

        int dash_count = 0;

        while(f>>s){
            if(dash_count == 0 && s != "-"){
                title.append(s);
                title.append(" ");
            }
            else if(dash_count == 1 && s != "-"){
                author.append(s);
                author.append(" ");
            }
            if(s == "-" )
                dash_count++;

            if(dash_count == 2) {                                // Lê o código do livro
                f>>s;
                break;
            }

        }

        f>>amount;                                             // "-" Precisa ler 2 vezes
        f>>amount;                                            // este é o nº de livros

        if(std::stoi(amount) == 0 && option == 1){
            f.close();       // Se a quantidade do livro for igual a 0 no acervo e tiver pesquisando na opção 1 do menu
            throw EmptyBook();
        }

        if(f.fail()){
            f.close();         // Se chegar ao fim do arquivo e não encontrar o isbn do livro
            throw InvalidBookException();
        }


    }while(s != isbn);
    f.close();

    std::shared_ptr<Book>send(new Book(title,author,isbn,stoi(amount))); // Instanciando um objeto Book com smart pointer

    // ao contrario
    return send;
}

//!Verifica se o aluno e livro existem, e se o aluno está com o livro escolhido para chamar o metodo return book da classe book
//! Joga exceções InvalidIdException se aluno nao existe, InvalidBookException se o livro nao existe, e invalid_argument se o aluno não tem o livro
int System::return_book(){                        // 2ª Opção Menu
    bool flag_student_id = true;
    bool flag_student_books = false;

    std::string isbn_book, id_student;

    try{
        unsigned int tam = System::students.size();
        std::cout << "\n\tDevolução de Livro\n\nDigite a matrícula do aluno (digite 'b' para voltar): ";
        std::cin >> id_student;

        if(id_student == "b"){
            return 0;
        }

        unsigned i;                       // para guardar o i-ésimo student encontrado
        for(i = 0; i < tam; i++){        // Varrendo o vector para ver se encontra student pela matrícula
            if(System::students[i]->get_id() == unsigned(std::stoi(id_student))){
                flag_student_id = false;
                break;
            }
        }

        if(flag_student_id){                                // Lançamento da exceção da matrícula
            throw InvalidIdException();
        }

        std::cout << "\nDigite o código do livro (digite 'b' para voltar): ";
        std::cin >> isbn_book;
        if(isbn_book == "b"){
            return 0;
        }

        std::cout << "\nAguarde...\n\n";
        std::this_thread::sleep_for (std::chrono::seconds(1));
        std::vector<shared_ptr<Book>> temp;

        // Verificar se o aluno está com o livro na sua lista de livros emprestados
        ifstream ifs;
        string s;
        string filebooks = "Alunos//" + id_student + ".txt";
        ifs.open(filebooks);

        while(ifs>>s){

            if(isbn_book == s){
                // Removendo o livro de books setando um novo vector sem ele
                for(unsigned k = 0; k < System::students[i]->get_books().size(); k++){
                    if(System::students[i]->get_books()[k]->get_isbn() != isbn_book){
                        temp.push_back(System::students[i]->get_books()[k]);
                    }
                }
                System::students[i]->set_books(temp);

                flag_student_books = true;
                break;
            }
        }
        ifs.close();

        //essa funcao apaga o livro da lista entao tem que verificar depois
        System::get_book(isbn_book, 2)->return_book(stoi(id_student)); // Verifica também se está no .txt, se não estiver lnaça exceção

        if(flag_student_books){
            std::cout << "\n\t Livro Devolvido com Sucesso!\n"<<endl;
            std::this_thread::sleep_for (std::chrono::seconds(1));
        }
        if(!flag_student_books){
            std::cout << "\nLivro não encontrado na lista de emprestados do aluno: " << id_student << "\nDigite 'm' para ir ao Menu ou 'b' para voltar: ";
            std::string ch;

            std::cin >> ch;
            system("clear");

            if(ch == "m"){
                return 0;
            }
            else if(ch == "b"){
                return_book();
            }
        }

    }
    catch(InvalidIdException& e){
        std::cout << e.what() << std::endl;
        std::this_thread::sleep_for (std::chrono::seconds(4));     
        system("clear");

        std::string ch;
        std::cout << e.what() << "\nDigite 'm' voltar para o Menu ou 'b' para voltar: ";

        std::cin >> ch;
        system("clear");

        if(ch == "m"){
            return 0;
        }
        else if(ch == "b"){
            return_book();
        }
    }
    catch(InvalidBookException& f){
        std::cout << f.what() << std::endl;
        std::this_thread::sleep_for (std::chrono::seconds(4));     
        system("clear");

        std::string ch;
        std::cout << f.what() << "\nDigite 'm' para ir ao Menu ou 'b' para voltar: ";

        std::cin >> ch;
        system("clear");

        if(ch == "m"){
            return 0;
        }
        else if(ch == "b"){
            return_book();
        }
    }
    catch(std::invalid_argument& e){
        std::cout << "Entrada Inválida!" << std::endl;
        std::cout << "\nDigite 'm' para ir ao Menu ou 'b' para voltar: ";

        std::string ch;
        std::cin >> ch;
        system("clear");

        if(ch == "m"){
            return 0;
        }
        else if(ch == "b"){
            return_book();
        }
    }

    return 0;
}

//! Mosta na tela de o menu de admnistração com opções 1- Registrar novo livro 2- Registrar novo estudante 3- Mostrar Registro de Estudantes
//! 4- Mostrar Info. de Estudante Específico Mostrar Lista de livros 5- Mostrar Lista de livros 6-Mostrar Info. de Livro especifico
//! 7- Remover estudante e 8- remover livro

int System::show_adm_menu(){

    std::string ch;
    try {
        do {
            system("clear");
            std::cout << " ##################################################";
            std::cout << "\n##\t\t    MENU ADM             \t  ##";
            std::cout << "\n##\t\t\t\t\t\t  ##\n##\t01. Registrar Novo Livro                  ##";
            std::cout << "\n##\t\t\t\t\t\t  ##\n##\t02. Registrar Novo Estudante              ##";
            std::cout << "\n##\t\t\t\t\t\t  ##\n##\t03. Mostrar Registro de Estudantes        ##";
            std::cout << "\n##\t\t\t\t\t\t  ##\n##\t04. Mostrar Info. de Estudante Específico ##";
            std::cout << "\n##\t\t\t\t\t\t  ##\n##\t05. Mostrar Lista de Livros               ##";
            std::cout << "\n##\t\t\t\t\t\t  ##\n##\t06. Mostrar Info. de Livro Específico     ##";
            std::cout << "\n##\t\t\t\t\t\t  ##\n##\t07. Remover um Estudante                  ##";
            std::cout << "\n##\t\t\t\t\t\t  ##\n##\t08. Remover um Livro                      ##";
            std::cout << "\n##\t\t\t\t\t\t  ##\n##\t09. Voltar                                ##\n";
            std::cout << " ##################################################\n";
            std::cout << "\n ==> Por favor selecione uma das opções(1-9): ";
            std::cin >> ch;

            if(ch == "1"){                           // Registrar novo livro
                string titulo,autor,isbn,quantidade;
                ofstream books;
                books.open("Acervo-de-Livros//books.txt",std::ofstream::out | std::ofstream::app);

                system("clear");
                cout<<"Titulo (Digite 'm' para ir ao Menu ou 'b' para voltar): ";
                cin>>titulo;

                if(titulo == "m"){
                    return 0;
                }
                else if(titulo == "b"){
                    continue;
                }


                cout<<"Autor:"<<endl;;
                cin>>autor;


                cout<<"ISBN:"<<endl;
                cin>>isbn;

                try{
                    System::get_book(isbn,0);
                    cout<<"Ja existe esse livro"<<endl;
                    std::this_thread::sleep_for (std::chrono::seconds(2));
                }
                catch(...){
                    cout<<"Quantos?:"<<endl;;

                    cin>>quantidade;

                    books<<titulo;
                    books<<" - ";
                    books<<isbn;
                    books<<" - ";
                    books<<autor;
                    books<<" - ";
                    books<<quantidade;
                }
                books.close();
            }

            else if(ch == "2"){                             // Registrar novo estudante

                string name, id;
                ifstream istudents;
                istudents.open("Alunos//students.txt");
                system("clear");
                cout<<"Nome (Digite 'm' para ir ao Menu ou 'b' para voltar): ";

                cin.ignore();
                getline(cin, name);
                // std::cout << name << std::endl;

                if(name == "m"){
                    return 0;
                }
                else if(name == "b"){
                    continue;
                }

                cout<<"\nMatricula:";
                cin>>id;

                try{

                    stoi(id);
                    bool student_found = false;

                    string s;
                    while(istudents>>s){
                        istudents>>s;
                        if(s == id){
                            student_found = true;
                            break;
                        }
                    }

                    istudents.close();
                    if(student_found){

                        cout<<"Aluno ja registrado!"<<endl;
                        std::this_thread::sleep_for (std::chrono::seconds(2));
                    }
                    else{
                        ofstream students;
                        students.open("Alunos//students.txt",std::ofstream::out | std::ofstream::app);
                        students<<endl<<name<<" - "<<id;
                        
                        cout<<"Estudante registrado com sucesso!"<<endl;
                        std::shared_ptr<Student> send (new Student(std::stoi(id),name)); // Colocando student no vector
                        System::students.push_back(send);
                        std::this_thread::sleep_for (std::chrono::seconds(2));
                    }

                }
                catch(invalid_argument& e){
                    cout<< "Matricula deve ser um número" <<endl;
                }

            }

            else if(ch == "3"){                          // Mostrar Registro de Estudantes
                std::string option;

                system("clear");
                std::cout << "\t\tLista de Estudantes\n\n";
                std::cout << "==========================================================================\n";
                std::cout << "\tMatrícula \tN° Livros Emprestados \t     Nome\n";
                std::cout << "==========================================================================\n";

                for(unsigned i = 0; i < students.size(); i++){
                    std::cout << "\t" << students[i]->get_id() << "\t" << students[i]->get_books().size() << "\t\t\t" << students[i]->get_name() << std::endl;
                }

                std::cout << "\nDigite 'm' para ir ao Menu ou 'b' para voltar: ";
                std::cin >> option;

                if(option == "m"){
                    return 0;
                }
                else if(option == "b"){
                    continue;
                }
            }
            else if(ch == "4"){                            // Mostrar Info. de Estudante Específico
                std::string option, id;
                bool flag_student_id = true;
                std::vector<std::shared_ptr<Book>>::iterator it;

                system("clear");
                std::cout << "Digite o Número de Matrícula (digite 'b' para voltar): ";
                std::cin >> id;

                if(id == "b"){
                    continue;
                }

                unsigned i;
                for(i = 0; i < students.size(); i++){            // Pegando o i-ésimo correspondente ao aluno
                    if(students[i]->get_id() == unsigned(stoi(id))){
                        flag_student_id = false;
                        break;
                    }
                }

                if(flag_student_id){
                    throw InvalidIdException();
                }

                std::cout << "\n\tNome: " << students[i]->get_name() << "\n";
                std::cout << "\n\tNúmero de Matrícula: " << stoi(id) << "\n";
                std::cout << "\n\tNúmero de Livros Emprestados: " << students[i]->get_books().size() << "\n";
                std::cout << "\n\tLivros:\n";

                for(unsigned j = 0; j < System::students[i]->get_books().size(); j++){                          // Lendo vector de books de students e printando titulo
                    std::cout << "\t\tLivro Nº: " << students[i]->get_books()[j]->get_isbn() << std::endl;
                }

                std::cout << "\nDigite 'm' para ir ao Menu ou 'b' para voltar: ";
                std::cin >> option;

                if(option == "m"){
                    return 0;
                }
                else if(option == "b"){
                    continue;
                }

            }

            else if(ch == "5"){                             // Mostrar Lista de livros
                int i = 0;
                std::string option;

                system("clear");
                std::cout << "\t\tLista de Livros\n\n";
                std::cout << "==========================================================================================\n";
                std::cout << "\tISBN" << "\tQuantidade" << "\tTítulo do Livro" << "\t\tAutor\n";
                std::cout << "==========================================================================================\n";

                ifstream read;
                string isbn,author,title,amount, string;
                read.open("Acervo-de-Livros//books.txt");

                do {
                    i++;
                    std::getline(read, title, '-');
                    std::getline(read, author, '-');
                    std::getline(read, isbn, '-');
                    read >> string;
                    isbn.append(string);
                    std::getline(read,string, '-');
                    isbn.append(string);
                    std::getline(read,amount, '\n');

                    std::cout << isbn  << "\a" << amount << "\a\t" <<title << "\a\t" << author << std::endl;
                } while((!read.fail()));

                std::cout << "==========================================================================================\n";
                std::cout << "\tISBN" << "\tQuantidade" << "\tTítulo do Livro" << "\t\tAutor\n";
                std::cout << "==========================================================================================\n";

                read.close();

                std::cout << "\nDigite 'm' para ir ao Menu ou 'b' para voltar: ";
                std::cin >> option;

                if(option == "m"){
                    return 0;
                }
                else if(option == "b"){
                    continue;
                }
            }

            else if(ch == "6"){                             // Mostrar Info. de Livro especifico
                std::string isbn, option;

                system("clear");
                std::cout << "Digite o Código do Livro (digite 'b' para voltar): ";
                std::cin >> isbn;

                if(isbn == "b")
                    continue;

                std::shared_ptr<Book> teste = get_book(isbn, 0);                // este métdo tem uma exceção que verfica isbn

                std::cout << "\n\nDetalhes do Livro:\n\n";
                std::cout << "\t\t Título do Livro: " << teste->get_title() << std::endl;
                std::cout << "\t\t Autor do Livro: " << teste->get_author() << std::endl;
                std::cout << "\t\t Código do Livro: " << teste->get_isbn() << std::endl;
                std::cout << "\t\t Quantidade no Acervo: " << teste->get_amount() << std::endl;

                std::cout << "\nDigite 'm' para ir ao Menu ou 'b' para voltar: ";
                std::cin >> option;

                if(option == "m"){
                    return 0;
                }
                else if(option == "b"){
                    continue;
                }
            }

            else if(ch == "7"){                                 //Remover um Estudante
                system("clear");
				cout<<"Matricula do estudante (Digite 'm' para ir ao Menu ou 'b' para voltar): ";
				string id;
                cin.ignore();
                cin>>id;

                if(id == "m"){
                    return 0;
                }
                else if(id == "b"){
                    continue;
                }

                ifstream alunos;
                ofstream buffer;
                alunos.open("Alunos//students.txt");
                buffer.open("Alunos//buffer.txt",std::ofstream::out | std::ofstream::app);

                string s;
                bool found = false;
                int i = 1;
                while(alunos>>s){
                    
                    try{

                        std::stoi(s);
                        i++;
                        if(s == id)
                            found = true;

                    }
                    catch(...){}
                    alunos.ignore();
                }

                alunos.close();

                if(found){

                    string file = "Alunos//";
                    file.append(id);
                    file.append(".txt");

                    remove(file.c_str());


                    // Remover o aluno do vector students
                    std::vector<shared_ptr<Student>> temp;
                    temp = students;
                    
                    students.clear();
                    for(unsigned k = 0; k < temp.size(); k++){
                        if(temp[k]->get_id() != unsigned(stoi(id)))
                            students.push_back(temp[k]);
                    }
                    ifstream aluno;
                    aluno.open("Alunos//students.txt");

                    int j=0;      // para contar o número de linhas no arquivo
                    while(true){

                        string name;
                        string id_lido;
                        
                        getline(aluno,name, '-');
                        getline(aluno,id_lido);    
                        
                        if(unsigned(stoi(id_lido)) != unsigned(stoi(id))){
                            //std::cout << name << id_lido << std::endl;
                            if(unsigned(j) == students.size()){   // para nao deixar quebra de linha no ultimo
                                buffer << name << "-" << id_lido;
                            }
                            else
                                buffer << name << "-" << id_lido << std::endl;
                        }
                        if(!aluno.good()) 
                            break;
                        j++;
                    }
                    //std::cout << students.size() << std::endl;
                    aluno.close();
				    cout<<"Estudante removido com Sucesso!"<<endl;
                    std::this_thread::sleep_for (std::chrono::seconds(2));
                }

			else{
				cout<<"Estudante não existe!"<<endl;
                std::this_thread::sleep_for (std::chrono::seconds(2));
			}

                alunos.close();
                buffer.close();

                string r = "Alunos//students.txt";
                remove(r.c_str());
                rename("Alunos//buffer.txt","Alunos//students.txt");

			}

            else if(ch == "8"){                      // Remover Livro
                system("clear");
				cout<<"ISBN do livro (Digite 'm' para ir ao Menu ou 'b' para voltar): ";
                string isbn;
                cin >>isbn;

                if(isbn == "m"){
                    return 0;
                }
                else if(isbn == "b"){
                    continue;
                }

                try{
                    get_book(isbn,0);

                    ifstream livros;
                    ofstream buffer;
                    livros.open("Acervo-de-Livros//books.txt");
                    buffer.open("Acervo-de-Livros//buffer.txt",std::ofstream::out | std::ofstream::app);

                    string s,temp;

                    while(true){

                        getline(livros,s);
                        stringstream str(s);
                        bool done = false;

                        while(str>>temp){

                            if(temp == isbn){
                                done = true;
                            }
                        }

                        if(!done) buffer<<s<<endl;

                        if(!livros.good()) break;
                        
                    }
                    
                    livros.close();
                    buffer.close();

                    cout<<"Livro removido com sucesso!"<<endl;
                    std::this_thread::sleep_for (std::chrono::seconds(2));
                    string r = "Acervo-de-Livros//books.txt";
                    remove(r.c_str());
                    rename("Acervo-de-Livros//buffer.txt","Acervo-de-Livros//books.txt");
                    std::this_thread::sleep_for (std::chrono::seconds(2));

                }
                catch(...){
                    cout<<"Livro não encontrado!"<<endl;
                    std::this_thread::sleep_for (std::chrono::seconds(2));
                }
			}

            else if(ch == "9"){
                std::cout << "\n\t\t\tVoltando..." << std::endl;
                std::this_thread::sleep_for (std::chrono::seconds(2));
                return 0;
            }

        } while(ch != "9");
    }
    catch(std::invalid_argument& e){
        std::cout << "Caracter Inválido!" << std::endl;
        std::cout << "\nDigite 'b' para voltar: ";

        std::string ch;
        std::cin >> ch;

        system("clear");

        if(ch == "m"){
            return 0;
        }
        else if(ch == "b"){
             show_adm_menu();;
        }
    }
    catch(InvalidIdException& e){
        std::cout << e.what() << std::endl;
        std::this_thread::sleep_for (std::chrono::seconds(4));     
        system("clear");

        std::string ch;
        std::cout << e.what() << "\nDigite 'm' voltar para o Menu ou 'b' para voltar: ";

        std::cin >> ch;
        system("clear");

        if(ch == "m"){
            return 0;
        }
        else if(ch == "b"){
             show_adm_menu();
        }
    }

    return 0;
}

//! Mosta na tela de o menu principal com opções 1- Empréstimo de Livro, 2- Devolução de Livro, 3- Menu de Admininstração ,4- Sair

int System::show_menu() {
    std::string ch;

    do {
        system("clear");
        std::cout << " #################################################";
        std::cout << "\n##\t\tMENU PRINCIPAL                   ##";
        std::cout << "\n##\t\t\t\t\t\t ##\n##\t01. Empréstimo de Livro                  ##";
        std::cout << "\n##\t\t\t\t\t\t ##\n##\t02. Devolução de Livro                   ##";
        std::cout << "\n##\t\t\t\t\t\t ##\n##\t03. Menu de Admininstração               ##";
        std::cout << "\n##\t\t\t\t\t\t ##\n##\t04. Sair                                 ##\n";
        std::cout << " #################################################\n";
        std::cout << "\n ==> Por favor selecione uma das opções(1-4): ";
        std::cin >> ch;

        if(ch == "1"){
            borrow_book();
        }
        else if(ch == "2"){
            return_book();
        }
        else if(ch == "3"){
            show_adm_menu();
        }
        else if(ch == "4"){
            std::cout << "\n\t\tSAINDO..." << std::endl;
            std::this_thread::sleep_for (std::chrono::seconds(2));   
        }

    } while(ch != "4");

    return 0;
}
