#pragma once
#include "Obstaculo.h"
#include <SFML/Graphics.hpp>

class EspinhosTentaculo : public Obstaculo {
private:
    sf::Texture textura;
    sf::Sprite sprite;
    bool texturaCarregada;
    short int danosidade;
    float tempoPulso;

public:
    EspinhosTentaculo(const sf::Vector2f& posicao);
    ~EspinhosTentaculo() override = default;

    void executar() override;
    void obstacular(Jogador* pJog) override;
    void desenhar() override;
};
