#include "Chao.h"

Chao::Chao(const sf::Vector2f& posicao, const sf::Vector2f& tamanho,
           const sf::Color& cor)
    : Entidade(posicao, tamanho, cor) {}

void Chao::executar() {}

void Chao::colidir(Jogador* pJog) {
    if (!pJog) return;
    float deltaTime = pGG ? pGG->getDeltaTime() : 0.016f;
    sf::FloatRect rectJogador = pJog->getLimites();
    sf::FloatRect rectChao = getLimites();

    // O chao apenas sustenta o jogador quando ele chega por cima.
    if (pJog->getVelocidadeY() > 0.f &&
        (rectJogador.top + rectJogador.height - pJog->getVelocidadeY() * deltaTime) <= rectChao.top + 10.f) {
        pJog->aterrar(rectChao.top - rectJogador.height);
    }
}
