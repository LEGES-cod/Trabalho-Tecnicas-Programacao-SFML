
#include "TroncoCaido.h"

TroncoCaido::TroncoCaido(const sf::Vector2f& posicao)
    : Obstaculo(
        sf::Vector2f(posicao.x, posicao.y - 35.f),
        sf::Vector2f(40.f, 60.f),
        sf::Color(110, 65, 25),
        false
    ) {}

void TroncoCaido::obstacular(Jogador* pJog) {
    if (!pJog) return;

    float deltaTime = pGG ? pGG->getDeltaTime() : 0.016f;

    sf::FloatRect rectJogador = pJog->getLimites();
    sf::FloatRect rectObstaculo = getLimites();

    // Aterrissagem no topo do tronco.
    if (pJog->getVelocidadeY() > 0.f &&
        (rectJogador.top + rectJogador.height -
         pJog->getVelocidadeY() * deltaTime)
         <= rectObstaculo.top + 10.f) {

        pJog->aterrar(rectObstaculo.top - rectJogador.height);
    }
    // Bloqueio lateral esquerdo.
    else if (rectJogador.left < rectObstaculo.left) {
        pJog->setPosicao(sf::Vector2f(
            rectObstaculo.left - rectJogador.width,
            rectJogador.top
        ));
    }
    // Bloqueio lateral direito.
    else if (rectJogador.left > rectObstaculo.left) {
        pJog->setPosicao(sf::Vector2f(
            rectObstaculo.left + rectObstaculo.width,
            rectJogador.top
        ));
    }
}
