#include "Inimigo.h"

Inimigo::Inimigo(const sf::Vector2f& posicao, const sf::Color& cor, Jogador* pJogador) // Construtor da classe. Define a posição recebida, o tamanho fixo, a cor do inimigo, uma velocidade estática, 1 vida inicial e dano base
    : Personagem(posicao, sf::Vector2f(35.f, 35.f), cor, 0.f, 1), dano(3), pJog(pJogador) {}

void Inimigo::executar() {}
