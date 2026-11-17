#ifndef INIMIGO_H
#define INIMIGO_H
#include "Personagem.h"
#include "Jogador.h"

class Inimigo : public Personagem {
protected:
    int dano;
    Jogador* pJog;
    bool vivo;

public:
    Inimigo(const sf::Vector2f& posicao, const sf::Color& cor,
            Jogador* pJogador = nullptr);

    void executar() override;
    virtual void inverterDirecao() {}

    int getDano() const { return dano; }
    void setJogador(Jogador* pJ) { pJog = pJ; }

    void receberDano(int quantidade);
    bool estaVivo() const { return vivo; }
};
#endif
