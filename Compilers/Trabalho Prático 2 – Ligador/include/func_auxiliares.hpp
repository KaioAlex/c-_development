// Prototipos das funcoes
#ifndef FUNC_AUXILIARES_HPP
#define FUNC_AUXILIARES_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <tuple>
#include "montador.hpp"

typedef enum simbolos{
  SIMB_HALT,
  SIMB_LOAD,
  SIMB_STORE,
  SIMB_READ,
  SIMB_WRITE,
  SIMB_COPY,
  SIMB_PUSH,
  SIMB_POP,
  SIMB_ADD,
  SIMB_SUB,
  SIMB_MUL,
  SIMB_DIV,
  SIMB_MOD,
  SIMB_AND,
  SIMB_OR,
  SIMB_NOT,
  SIMB_JUMP,
  SIMB_JZ,
  SIMB_JN,
  SIMB_CALL,
  SIMB_RET,
  SIMB_WORD,
  SIMB_END,
  SIMB_ERROR
} tipo_simbolo;

std::string remove_espacos(std::string str);
std::string busca_elemento(std::string& str);
tipo_simbolo busca_tipo_simbolo(std::string simbolo_str);
int busca_codigo_simbolo(tipo_simbolo simb);
int busca_codigo_arg(std::string arg, std::unordered_map<std::string, int>& tabela_simbolos);
std::tuple<std::string, std::string> buscal_label_e_simbolo(std::string linha_comentarios);
int busca_num_operandos_simbolo(tipo_simbolo simb);
int busca_espaco_memoria_simbolo(tipo_simbolo simb);

#endif