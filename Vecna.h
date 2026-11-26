#ifndef VECNA_H
#define VECNA_H

#include "Inimigo.h"
#include <SFML/Graphics.hpp>

class Vecna : public Inimigo {
private:
    short int forca;
    float tempoAtaque;
    bool ataqueSolicitado;
    bool indoDireita;
    sf::Texture textura;
    sf::Sprite sprite;
    bool texturaCarregada;

public:
    explicit Vecna(const sf::Vector2f& posicao, Jogador* pJogador = nullptr);

    void executar() override;
    void desenhar() override;
    void inverterDirecao() override { indoDireita = !indoDireita; }
    bool consumirAtaque();
    int getDano() const override { return (dano * nivel_maldade) + forca; }
};

#endif
