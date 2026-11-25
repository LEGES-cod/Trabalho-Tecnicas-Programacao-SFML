#pragma once
#include "Obstaculo.h"
#include <SFML/Graphics.hpp>

class EspinhosTentaculo : public Obstaculo {
private:
    sf::Texture textura;
    sf::Sprite sprite;
    bool texturaCarregada;

public:
    EspinhosTentaculo(const sf::Vector2f& posicao);
    ~EspinhosTentaculo() override = default;

    void obstacular(Jogador* pJog) override;
    void desenhar() override;
};
