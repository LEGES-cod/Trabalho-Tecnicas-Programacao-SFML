#ifndef DEMOGORGON_H
#define DEMOGORGON_H

#include "Inimigo.h"
#include <SFML/Graphics.hpp>

class Demogorgon : public Inimigo {
private:
    int tamanho;
    float tempoDisparo;
    bool disparoSolicitado;

    sf::Texture textura;
    sf::Sprite sprite;
    bool texturaCarregada;

public:
    explicit Demogorgon(
        const sf::Vector2f& posicao,
        Jogador* pJogador = nullptr
    );

    void executar() override;
    void desenhar() override;
    bool consumirDisparo();

    void mover();
};

#endif
