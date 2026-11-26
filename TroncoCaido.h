#pragma once
#include "Obstaculo.h"
#include <SFML/Graphics.hpp>

class TroncoCaido : public Obstaculo {
private:
    sf::Texture textura;
    sf::Sprite sprite;
    bool texturaCarregada;
    bool invisivel;
    float tempoInvisivel;


public:
    TroncoCaido(const sf::Vector2f& posicao);
    ~TroncoCaido() override = default;
    bool podeColidir() const override { return !invisivel; }

    void executar() override;
    void obstacular(Jogador* pJog) override;
    void desenhar() override;
};
