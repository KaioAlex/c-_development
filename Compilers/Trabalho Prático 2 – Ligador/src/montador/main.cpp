// TP2 - Montador
#include <fstream>
#include "montador.hpp"
#include "func_auxiliares.hpp"

int main(int argc, char* argv[]){
    if(argc != 2) {std::cout << "Sem arquivo de entrada..." << std::endl;  return -1;}

    std::ifstream arq;

    arq.open(argv[1]);
    if(!arq){std::cout << "ERRO: nao foi possivel abrir o arquivo" << std::endl;   return -1;} 
    else{
        int pos_inicial = 100;
        int pos_atual;
        //int valor_AP = 999;
        int pos_PC = pos_inicial;
        
        std::string linha;
        std::string saida;
        std::unordered_map<std::string, int> tabela_simbolos;

        arq.clear();
        arq.seekg(0, std::ios::beg);
        pos_atual = pos_inicial;

        // 1ª Passada
        while (std::getline(arq, linha)){completa_tabela_simbolos(linha, tabela_simbolos, pos_atual);}

        std::cout << pos_atual-pos_inicial << " " << tabela_simbolos.size(	) << std::endl;
        for (auto it = tabela_simbolos.begin(); it != tabela_simbolos.end(); it++) {
            std::cout << it->first << " " << it->second-pos_inicial << std::endl;
        }

        arq.clear();
        arq.seekg(0, std::ios::beg);

        // 2ª Passada
        while (std::getline(arq, linha)) {
            saida += segunda_passagem(linha, tabela_simbolos, pos_PC);
        }

        saida.pop_back();
        std::cout << saida << std::endl;
    }

    return 0;
}
