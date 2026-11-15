#ifndef LISTAENTIDADES_H
#define LISTAENTIDADES_H

#include "Lista.h"
#include "Entidade.h"

class ListaEntidades { // Classe que gerencia a coleção de entidades da fase
private:
    Lista<Entidade> LEs; // Lista encadeada de entidades

public:
    ListaEntidades();
    ~ListaEntidades();

    void incluir(Entidade* pE); // Inclui uma entidade na lista
    void remover(Entidade* pE); // Remove uma entidade da lista
    void percorrer();           // Percorre a lista executando e desenhando cada entidade
    void limpar();              // Desaloca as entidades e limpa a lista
    int getTamanho() const;
};

#endif
