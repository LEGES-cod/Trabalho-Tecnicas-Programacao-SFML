#ifndef GERENCIADORCOLISOES_H
#define GERENCIADORCOLISOES_H

#include <vector>
#include <list>
#include <set>
#include "Entidade.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "Obstaculo.h"
#include "Projetil.h"

class GerenciadorColisoes {
private:
    std::vector<Inimigo*> LIs;
    std::list<Obstaculo*> LOs;

    std::set<Projetil*> LPs;
    std::set<Projetil*> projeteisJogador;

    Jogador* pJog1;

    const bool verificarColisao(Entidade* pe1, Entidade* pe2) const;

    void tratarColisoesJogsObstacs();
    void tratarColisoesJogsInimgs();
    void tratarColisoesJogsProjeteis();
    void tratarColisoesProjeteisInimgs();
    void tratarColisoesInimgsObstacs();

public:
    GerenciadorColisoes();
    ~GerenciadorColisoes();

    void setJogador(Jogador* pJ);
    void incluirInimigo(Inimigo* pi);
    void incluirObstaculo(Obstaculo* po);
    void incluirProjetil(Projetil* pj);
    void incluirProjetilJogador(Projetil* pj);

    void limpar();
    void executar();
};
#endif
