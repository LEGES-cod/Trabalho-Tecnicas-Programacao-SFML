#include "PlataformaEstatica.h"

PlataformaEstatica::PlataformaEstatica(const sf::Vector2f& posicao, // Implementa o construtor da classe passando a posição e o tamanho recebidos, e definindo uma cor.
                                       const sf::Vector2f& tamanho)
    : Obstaculo(posicao, tamanho, sf::Color(100, 100, 100), false) {}

void PlataformaEstatica::obstacular(Jogador* pJog) { // Trata o apoio no topo e bloqueio lateral da plataforma
    if (!pJog) return;
    float deltaTime = pGG ? pGG->getDeltaTime() : 0.016f;
    sf::FloatRect rectJogador = pJog->getLimites();
    sf::FloatRect rectObstaculo = getLimites();

    if (pJog->getVelocidadeY() > 0.f &&
        (rectJogador.top + rectJogador.height - pJog->getVelocidadeY() * deltaTime) <= rectObstaculo.top + 10.f) {
        pJog->aterrar(rectObstaculo.top - rectJogador.height);
    } else if (rectJogador.left < rectObstaculo.left) {
        pJog->setPosicao(sf::Vector2f(rectObstaculo.left - rectJogador.width, rectJogador.top));
    } else if (rectJogador.left > rectObstaculo.left) {
        pJog->setPosicao(sf::Vector2f(rectObstaculo.left + rectObstaculo.width, rectJogador.top));
    }
}
