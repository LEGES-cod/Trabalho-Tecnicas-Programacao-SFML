#include "Inimigo.h"

Inimigo::Inimigo(const sf::Vector2f& posicao, const sf::Color& cor,
                 Jogador* pJogador)
    : Personagem(posicao, sf::Vector2f(35.f, 35.f), cor, 0.f, 20),
      dano(3),
      pJog(pJogador),
      vivo(true) {}

void Inimigo::executar() {}

void Inimigo::receberDano(int quantidade) {
    if (!vivo) return;

    vidas -= quantidade;

    if (vidas <= 0) {
        vidas = 0;
        vivo = false;
    }
}
