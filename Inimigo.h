#ifndef INIMIGO_H
#define INIMIGO_H
#include "Personagem.h"
#include "Jogador.h"

class Inimigo : public Personagem { // Declara a classe Inimigo que herda de Personagem
protected:
    int dano;         // Variável para o dano do inimigo
    Jogador* pJog;    // Ponteiro para o jogador (para perseguição/ataque)

public:
    Inimigo(const sf::Vector2f& posicao, const sf::Color& cor, Jogador* pJogador = nullptr); // Declara o construtor da classe, que recebe a posição inicial, a cor e o ponteiro do jogador
    void executar() override; // Declara a função virtual executar para atualizar a lógica do inimigo a cada frame
    virtual void inverterDirecao() {}
    int getDano() const { return dano; }
    void setJogador(Jogador* pJ) { pJog = pJ; }
};
#endif
