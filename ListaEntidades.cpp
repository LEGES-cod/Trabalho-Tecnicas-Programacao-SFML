#include "ListaEntidades.h"

ListaEntidades::ListaEntidades() {}

ListaEntidades::~ListaEntidades() { // Destrutor que libera a mem�ria das entidades
    limpar();
}

void ListaEntidades::incluir(Entidade* pE) { // Adiciona uma entidade na lista interna
    LEs.incluir(pE);
}

void ListaEntidades::remover(Entidade* pE) { // Remove uma entidade da lista interna
    LEs.remover(pE);
}

void ListaEntidades::percorrer() { // Percorre todos os n�s atualizando a l�gica e desenhando
    Lista<Entidade>::Elemento<Entidade>* pAux = LEs.getPrimeiro();
    while (pAux != nullptr) {
        Entidade* pEnt = pAux->getInfo();
        if (pEnt != nullptr) {
            pEnt->executar();
            pEnt->desenhar();
        }
        pAux = pAux->getProx();
    }
}

void ListaEntidades::limpar() { // Deleta todas as entidades alocadas dinamicamente e limpa os n�s
    Lista<Entidade>::Elemento<Entidade>* pAux = LEs.getPrimeiro();
    while (pAux != nullptr) {
        Entidade* pEnt = pAux->getInfo();
        delete pEnt;
        pAux = pAux->getProx();
    }
    LEs.limpar();
}

int ListaEntidades::getTamanho() const {
    return LEs.getTamanho();
}
