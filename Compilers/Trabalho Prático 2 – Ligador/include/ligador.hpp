// .hpp Prototipo das funcoes do ligador
#include <bits/stdc++.h>
#ifndef LIGADOR_HPP
#define LIGADOR_HPP

class Ligador{
    private:
        std::string corpo_programa;
        unsigned int inicio_programa;
        unsigned int tam_programa;

        std::vector<int> programa;
        std::map<std::string, int> rotulos; // labels memory position table

    public:
        Ligador(std::vector<std::string> &nome_arquivos);
        ~Ligador();

        void resolve_rotulos();
        void linca();
};

#endif
