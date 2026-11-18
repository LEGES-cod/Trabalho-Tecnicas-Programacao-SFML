#include "Vecna.h"

Vecna::Vecna(const sf::Vector2f& posicao, Jogador* pJogador) // Implementa o construtor da classe: passa a posição recebida, define uma cor
    : Inimigo(posicao, sf::Color(90, 0, 110), pJogador) { // Roxo escuro
    dano = 15;
    pontos = 50;
}
