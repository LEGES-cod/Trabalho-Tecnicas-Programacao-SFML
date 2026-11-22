#include "TroncoCaido.h"

TroncoCaido::TroncoCaido(const sf::Vector2f& posicao) // Implementa o construtor da classe: repassa a posi��o recebida, define um tamanho fixo, define uma cor
    : Obstaculo(posicao, sf::Vector2f(110.f, 25.f), sf::Color(110, 65, 25), false) {} // Marrom escuro

void TroncoCaido::obstacular(Jogador* pJog) { // Colis�o inteligente com o Tronco
    if (!pJog) return;
    float deltaTime = pGG ? pGG->getDeltaTime() : 0.016f;
    sf::FloatRect rectJogador = pJog->getLimites();     // Caixa delimitadora do jogador
    sf::FloatRect rectObstaculo = getLimites();         // Caixa delimitadora do tronco

    // 1. Aterragem no topo do tronco (se o jogador estiver caindo e vindo de cima)
    if (pJog->getVelocidadeY() > 0.f &&
        (rectJogador.top + rectJogador.height - pJog->getVelocidadeY() * deltaTime) <= rectObstaculo.top + 10.f) {
        pJog->aterrar(rectObstaculo.top - rectJogador.height);
    }
    // 2. Bloqueio lateral esquerdo (indo para a direita contra o tronco)
    else if (rectJogador.left < rectObstaculo.left) {
        pJog->setPosicao(sf::Vector2f(rectObstaculo.left - rectJogador.width, rectJogador.top));
    }
    // 3. Bloqueio lateral direito (indo para a esquerda contra o tronco)
    else if (rectJogador.left > rectObstaculo.left) {
        pJog->setPosicao(sf::Vector2f(rectObstaculo.left + rectObstaculo.width, rectJogador.top));
    }
}
