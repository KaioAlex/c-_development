// Implementacao das funcoes
#include "func_auxiliares.hpp"

int busca_num_operandos_simbolo(tipo_simbolo simb){
  switch(simb){
    case SIMB_ERROR:
    case SIMB_HALT:
    case SIMB_RET:
    case SIMB_END:
      return 1;
    case SIMB_READ:
    case SIMB_WRITE:
    case SIMB_PUSH:
    case SIMB_POP:
    case SIMB_NOT:
    case SIMB_JUMP:
    case SIMB_JZ:
    case SIMB_JN:
    case SIMB_CALL:
    case SIMB_WORD:
      return 2;
    default:
      return 3;
  }
}

int busca_espaco_memoria_simbolo(tipo_simbolo simb){
  switch(simb){
    case SIMB_END:
      return 0;
    case SIMB_WORD:
      return 1;
    default:
      return busca_num_operandos_simbolo(simb);
  }
}

std::string remove_espacos(std::string str){
  return str.substr(str.find_first_not_of(" \r\n"), std::string::npos);
}

std::string busca_elemento(std::string& str){
  str = remove_espacos(str);

  size_t espaco_apos = str.find_first_of(" \r\n");
  std::string ele = str.substr(0, espaco_apos);
  str = espaco_apos != std::string::npos ? str.substr(espaco_apos, std::string::npos): "";

  return ele;
}

tipo_simbolo busca_tipo_simbolo(std::string simbolo){
  if(simbolo == "HALT") return SIMB_HALT;
  if(simbolo == "LOAD") return SIMB_LOAD;
  if(simbolo == "STORE") return SIMB_STORE;
  if(simbolo == "READ") return SIMB_READ;
  if(simbolo == "WRITE") return SIMB_WRITE;
  if(simbolo == "COPY") return SIMB_COPY;
  if(simbolo == "PUSH") return SIMB_PUSH;
  if(simbolo == "POP") return SIMB_POP;
  if(simbolo == "ADD") return SIMB_ADD;
  if(simbolo == "SUB") return SIMB_SUB;
  if(simbolo == "MUL") return SIMB_MUL;
  if(simbolo == "DIV") return SIMB_DIV;
  if(simbolo == "MOD") return SIMB_MOD;
  if(simbolo == "AND") return SIMB_AND;
  if(simbolo == "OR") return SIMB_OR;
  if(simbolo == "NOT") return SIMB_NOT;
  if(simbolo == "JUMP") return SIMB_JUMP;
  if(simbolo == "JZ") return SIMB_JZ;
  if(simbolo == "JN") return SIMB_JN;
  if(simbolo == "CALL") return SIMB_CALL;
  if(simbolo == "RET") return SIMB_RET;
  if(simbolo == "WORD") return SIMB_WORD;
  if(simbolo == "END") return SIMB_END;

  return SIMB_ERROR;
}

int busca_codigo_simbolo(tipo_simbolo simbolo){
  switch(simbolo){
    case SIMB_HALT: return 0;
    case SIMB_LOAD: return 1;
    case SIMB_STORE: return 2;
    case SIMB_READ: return 3;
    case SIMB_WRITE: return 4;
    case SIMB_COPY: return 5;
    case SIMB_PUSH: return 6;
    case SIMB_POP: return 7;
    case SIMB_ADD: return 8;
    case SIMB_SUB: return 9;
    case SIMB_MUL: return 10;
    case SIMB_DIV: return 11;
    case SIMB_MOD: return 12;
    case SIMB_AND: return 13;
    case SIMB_OR: return 14;
    case SIMB_NOT: return 15;
    case SIMB_JUMP: return 16;
    case SIMB_JZ: return 17;
    case SIMB_JN: return 18;
    case SIMB_CALL: return 19;
    case SIMB_RET: return 20;

    default: return -1;
  }
}

int busca_codigo_arg(std::string arg, std::unordered_map<std::string, int>& tabela_simbolos){
  if(arg == "R0") return 0;
  if(arg == "R1") return 1;
  if(arg == "R2") return 2;
  if(arg == "R3") return 3;

  std::unordered_map<std::string, int>::iterator it = tabela_simbolos.find(arg);

  if (it != tabela_simbolos.end()) return it->second;

  return -1;
}

std::tuple<std::string, std::string> buscal_label_e_simbolo(std::string linha_comentarios){
	size_t colon = linha_comentarios.find(":");
	bool eh_label = colon != std::string::npos;

	if(eh_label)	return std::make_tuple(remove_espacos(linha_comentarios.substr(0, colon)), remove_espacos(linha_comentarios.substr(colon+1, std::string::npos)));
	else	return std::make_tuple("", remove_espacos(linha_comentarios));
}