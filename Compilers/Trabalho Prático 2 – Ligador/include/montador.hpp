// Prototipos das funcoes do montador
#ifndef MONTADOR_HPP
#define MONTADOR_HPP

#include "func_auxiliares.hpp"

void completa_tabela_simbolos(std::string linha, std::unordered_map<std::string, int>& tabela_simbolos, int& pos_atual);

std::string segunda_passagem(std::string linha, std::unordered_map<std::string, int>& tabela_simbolos, int& pos_PC);

#endif
