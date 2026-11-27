#include "Entidade.h"

Entidade::Entidade(const sf::Vector2f& posicao, const sf::Vector2f& tamanho,
                   const sf::Color& cor)
    : velocidadeY(0.f) {
    corpo.setPosition(posicao);
    corpo.setSize(tamanho);
    corpo.setFillColor(cor);
}

sf::FloatRect Entidade::getLimites() const {
    return corpo.getGlobalBounds();
}

sf::Vector2f Entidade::getPosicao() const {
    return corpo.getPosition();
}

void Entidade::setPosicao(const sf::Vector2f& posicao) {
    corpo.setPosition(posicao);
}

void Entidade::aplicarGravidade(float deltaTime, float fator) {
    velocidadeY += GRAVIDADE * fator * deltaTime;
    corpo.move(0.f, velocidadeY * deltaTime);
}

void Entidade::desenhar() {
    if (pGG) pGG->desenharElemento(corpo);
}
