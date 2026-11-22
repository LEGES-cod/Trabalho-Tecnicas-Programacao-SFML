#ifndef DEMOGORGON_H
#define DEMOGORGON_H

#include "Inimigo.h"
#include <SFML/Graphics.hpp>

class Demogorgon : public Inimigo {
private:
    float tempoDisparo;
    bool disparoSolicitado;

    sf::Texture textura;
    sf::Sprite sprite;
    bool texturaCarregada;

    // Sistema de vidas
    int vidas;

    // Movimentação para perseguir o jogador
    float velocidade;

public:
    explicit Demogorgon(
        const sf::Vector2f& posicao,
        Jogador* pJogador = nullptr
    );

    void executar() override;
    void desenhar() override;
    bool consumirDisparo();

    void receberDano(int dano);
    int getVidas() const;

    void mover();
};

#endif
