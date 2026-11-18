#include "Demogorgon.h"

Demogorgon::Demogorgon(const sf::Vector2f& posicao, Jogador* pJogador) // Implementa o construtor da classe Demogorgon.
    : Inimigo(posicao, sf::Color(120, 0, 0), pJogador) { // Vermelho escuro
    dano = 10;
    pontos = 30;
}
