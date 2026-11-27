#include "Obstaculo.h"

Obstaculo::Obstaculo(const sf::Vector2f& posicao, const sf::Vector2f& tamanho,
                     const sf::Color& cor, bool ehDanoso)
    : Entidade(posicao, tamanho, cor), danoso(ehDanoso) {}

void Obstaculo::executar() {
    float deltaTime = pGG ? pGG->getDeltaTime() : 0.016f;
    aplicarGravidade(deltaTime);
    corpo.move(0.f, -velocidadeY * deltaTime);
    velocidadeY = 0.f;
}
