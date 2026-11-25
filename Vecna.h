#ifndef VECNA_H
#define VECNA_H

#include "Inimigo.h"
#include <SFML/Graphics.hpp>

class Vecna : public Inimigo {
private:
    float tempoAtaque;
    bool ataqueSolicitado;
    sf::Texture textura;
    sf::Sprite sprite;
    bool texturaCarregada;

public:
    explicit Vecna(const sf::Vector2f& posicao, Jogador* pJogador = nullptr);

    void executar() override;
    void desenhar() override;
    bool consumirAtaque();
};

#endif
