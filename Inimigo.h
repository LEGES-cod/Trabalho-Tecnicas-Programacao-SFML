#ifndef INIMIGO_H
#define INIMIGO_H

#include "Personagem.h"

class Jogador; // Declaracao antecipada quebra o ciclo de includes

class Inimigo : public Personagem {
protected:
    int dano;
    Jogador* pJog;
    bool vivo;
    float velocidadeY;
    const float GRAVIDADE = 980.f;

public:
    Inimigo(const sf::Vector2f& posicao, const sf::Color& cor,
            Jogador* pJogador = nullptr);

    void executar() override;
    virtual void inverterDirecao() {}
    void aplicarGravidade(float deltaTime);
    void aterrar(float alturaY);

    int getDano() const { return dano; }
    void setJogador(Jogador* pJ) { pJog = pJ; }

    void receberDano(int quantidade);
    bool estaVivo() const { return vivo; }
};

#endif
