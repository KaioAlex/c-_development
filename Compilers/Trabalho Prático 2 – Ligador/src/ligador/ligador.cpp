// .cpp Implementacao das funcoes do ligador
#include "ligador.hpp"
#include <bits/stdc++.h>

Ligador::Ligador(std::vector<std::string> &nome_arquivos){
    this->corpo_programa = "";
    this->inicio_programa = this->tam_programa = 0;

    std::string rotulo, programa;
    int tam, num_rotulos, pos_memoria;
    
    for(std::string arq : nome_arquivos){
        std::ifstream infile(arq.c_str());
        
        infile >> tam >> num_rotulos;
        for(int i = 0; i < num_rotulos; i++){
            infile >> rotulo >> pos_memoria;
            this->rotulos[rotulo] = this->tam_programa + pos_memoria;

            if(rotulo == "main") this->inicio_programa = this->rotulos["main"];
        }

        infile.ignore();
        std::getline(infile, programa);

        if(this->corpo_programa != "") this->corpo_programa += " ";
        
        this->corpo_programa += programa;
        this->tam_programa += tam;

        infile.close();
    }
}

void Ligador::resolve_rotulos(){
    std::string token;
    std::stringstream s(this->corpo_programa);

    int contador = 0;
    while(s >> token){
        contador++;
        if(this->rotulos.find(token) != this->rotulos.end()){
            int pos_memoria = this->rotulos[token] - contador;
            this->programa.push_back(pos_memoria);
        }
        else{
            this->programa.push_back(std::stoi(token));
        }
    }
}

void Ligador::linca(){
    int end_carregamento = 0;
    int tam_prog = this->programa.size();

    std::cout << "MV-EXE" << std::endl;
    std::cout << tam_prog << " ";
    std::cout << end_carregamento << " ";
    std::cout << tam_prog + 1000 << " ";
    std::cout << this->inicio_programa << std::endl;
    
    std::cout << this->programa[0];
    
    for(size_t i = 1; i < this->programa.size(); i++) std::cout << " " << this->programa[i];
    
    std::cout << std::endl;
}

Ligador::~Ligador() {}