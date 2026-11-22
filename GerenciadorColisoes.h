#ifndef GERENCIADORCOLISOES_H
#define GERENCIADORCOLISOES_H

#include <vector>
#include <list>
#include <set>
#include "Entidade.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "Obstaculo.h"
#include "Chao.h"
#include "BolaDeFogo.h"

class GerenciadorColisoes {
private:
    std::vector<Inimigo*> LIs;
    std::list<Obstaculo*> LOs;
    std::list<Chao*> LCs;

    std::set<BolaDeFogo*> LPs;
    std::set<BolaDeFogo*> projeteisJogador;

    Jogador* pJog1;

    const bool verificarColisao(Entidade* pe1, Entidade* pe2) const;

    void tratarColisoesJogsObstacs();
    void tratarColisoesJogsChao();
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
    void incluirChao(Chao* pc);
    void incluirProjetil(BolaDeFogo* pj);
    void incluirProjetilJogador(BolaDeFogo* pj);

    void limpar();
    void executar();
};
#endif
