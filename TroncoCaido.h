#pragma once
#include "Obstaculo.h"
#include <SFML/Graphics.hpp>

class TroncoCaido : public Obstaculo {
private:
    sf::Texture textura;
    sf::Sprite sprite;
    bool texturaCarregada;

public:
    TroncoCaido(const sf::Vector2f& posicao);
    ~TroncoCaido() override = default;

    void obstacular(Jogador* pJog) override;
    void desenhar() override;
};
