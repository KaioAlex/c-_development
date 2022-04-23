// Programa principal do Ligador
#include <iostream>
#include "ligador.hpp"

int main(int argc, char* argv[]){
    std::vector<std::string> nome_arquivos;

    for(int i = 1; i < argc; i++)
        nome_arquivos.push_back(argv[i]);

    Ligador l = Ligador(nome_arquivos);
    l.resolve_rotulos();
    l.linca();

    return 0;
}