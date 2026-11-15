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

class GerenciadorColisoes { // Declara a classe conforme o diagrama UML
private:
    std::vector<Inimigo*> LIs;   // Vetor de ponteiros para inimigos
    std::list<Obstaculo*> LOs;   // Lista de ponteiros para obstáculos
    std::set<Projetil*> LPs;     // Conjunto de ponteiros para projéteis
    Jogador* pJog1;              // Ponteiro para o jogador principal

    const bool verificarColisao(Entidade* pe1, Entidade* pe2) const; // Verifica interseção entre duas entidades
    void tratarColisoesJogsObstacs();   // Resolve colisões entre jogador e obstáculos
    void tratarColisoesJogsInimgs();    // Resolve colisões entre jogador e inimigos
    void tratarColisoesJogsProjeteis(); // Resolve colisões entre jogador e projéteis
    void tratarColisoesInimgsObstacs(); // Resolve colisões entre inimigos e obstáculos

public:
    GerenciadorColisoes();
    ~GerenciadorColisoes();

    void setJogador(Jogador* pJ);          // Define o ponteiro para o jogador
    void incluirInimigo(Inimigo* pi);      // Inclui um inimigo no vetor
    void incluirObstaculo(Obstaculo* po);  // Inclui um obstáculo na lista
    void incluirProjetil(Projetil* pj);    // Inclui um projétil no conjunto
    void limpar();                         // Limpa todos os contêineres

    void executar(); // Executa todas as verificações e tratamentos de colisão
};
#endif
