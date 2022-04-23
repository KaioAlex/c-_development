// Implementacao das funcoes do montador
#include "montador.hpp"

void completa_tabela_simbolos(std::string line, std::unordered_map<std::string, int>& tabela_simbolos, int& pos_atual){
  std::string linha_comentarios = line.substr(0, line.find(";"));
  bool soh_espacos = linha_comentarios.find_first_not_of(" \r\n") == std::string::npos;

  if(soh_espacos)  return;

  std::string simb_args;
  std::string label;
  std::string simbolo;
  tipo_simbolo simb;
  auto label_simb_e_args = buscal_label_e_simbolo(linha_comentarios);
  label = std::get<0>(label_simb_e_args);
  simb_args = std::get<1>(label_simb_e_args);
  simbolo = busca_elemento(simb_args);
  simb = busca_tipo_simbolo(simbolo);

  if(label != ""){tabela_simbolos.insert(std::make_pair(label, pos_atual));}
  pos_atual += busca_espaco_memoria_simbolo(simb);
}

std::string segunda_passagem(std::string linha, std::unordered_map<std::string, int>& tabela_simbolos, int& pos_PC){
  std::string linha_comentarios = linha.substr(0, linha.find(";"));
  bool soh_espacos = linha_comentarios.find_first_not_of(" \r\n") == std::string::npos;

  if(soh_espacos) return "";

  std::string simbolo_e_args;
  std::string label;
  std::string simbolo;
  std::string commandCodeStr;
  tipo_simbolo simb;
  std::string arg1;
  std::string arg2;
  int codigo_simbolo, cod_1, code_2;
  std::stringstream codigo;

  auto label_simb_e_args = buscal_label_e_simbolo(linha_comentarios);
  label = std::get<0>(label_simb_e_args);
  simbolo_e_args = std::get<1>(label_simb_e_args);
  simbolo = busca_elemento(simbolo_e_args);
  simb = busca_tipo_simbolo(simbolo);
  switch(busca_num_operandos_simbolo(simb)){
    case 2:
      arg1 = busca_elemento(simbolo_e_args);
      break;
    case 3:
      arg1 = busca_elemento(simbolo_e_args);
      arg2 = busca_elemento(simbolo_e_args);
    default:
      break;
  }

  codigo_simbolo = busca_codigo_simbolo(simb);
  cod_1 = busca_codigo_arg(arg1, tabela_simbolos);
  code_2 = busca_codigo_arg(arg2, tabela_simbolos);

  pos_PC += busca_espaco_memoria_simbolo(simb);
  switch(simb){
    case SIMB_HALT:
    case SIMB_RET:
      codigo << codigo_simbolo << " ";
      break;
    case SIMB_LOAD:
    case SIMB_STORE:
      codigo << codigo_simbolo << " " << cod_1 << " " << (code_2 - pos_PC) << " ";
      break;
    case SIMB_READ:
    case SIMB_WRITE:
    case SIMB_PUSH:
    case SIMB_POP:
    case SIMB_NOT:
      codigo << codigo_simbolo << " " << cod_1 << " ";
      break;
    case SIMB_COPY:
    case SIMB_ADD:
    case SIMB_SUB:
    case SIMB_MUL:
    case SIMB_DIV:
    case SIMB_MOD:
    case SIMB_AND:
    case SIMB_OR:
      codigo << codigo_simbolo << " " << cod_1 << " " << code_2 << " ";
      break;
    case SIMB_JUMP:
    case SIMB_JZ:
    case SIMB_JN:
    case SIMB_CALL:
      codigo << codigo_simbolo << " " << (cod_1 - pos_PC) << " ";
      break;
    case SIMB_WORD:
      codigo << arg1 << " ";
      break;
    case SIMB_END:
    default:
      break;
  }

  return codigo.str();
}
