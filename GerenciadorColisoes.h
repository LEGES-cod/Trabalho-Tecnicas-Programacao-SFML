#ifndef GERENCIADORCOLISOES_H
#define GERENCIADORCOLISOES_H
#include "Entidade.h"

class GerenciadorColisoes { //Declara a classe
public:
    static bool verificar(const Entidade& a, const Entidade& b); //Declara um método estático, que pode ser chamado diretamente sem precisar instanciar a classe GerenciadorColisoes. Retorna true se tiver interseção entre duas entidades
};
#endif
