#include "Inimigo.h"

Inimigo::Inimigo(const sf::Vector2f& posicao, const sf::Color& cor,
                 Jogador* pJogador, int nivelMaldade)
    : Personagem(posicao, sf::Vector2f(35.f, 35.f), cor, 0.f, 20),
      dano(1),
      nivel_maldade(nivelMaldade),
      pJog(pJogador),
      vivo(true),
      velocidadeY(0.f) {}

void Inimigo::executar() {
    if (!vivo) return;
    float deltaTime = pGG ? pGG->getDeltaTime() : 0.016f;
    aplicarGravidade(deltaTime);
}

void Inimigo::aplicarGravidade(float deltaTime) {
    velocidadeY += GRAVIDADE * deltaTime;
    mover(0.f, velocidadeY * deltaTime);
}

void Inimigo::aterrar(float alturaY) {
    sf::Vector2f p = getPosicao();
    p.y = alturaY;
    setPosicao(p);
    velocidadeY = 0.f;
}

void Inimigo::receberDano(int quantidade) {
    if (!vivo) return;

    vidas -= quantidade;

    if (vidas <= 0) {
        vidas = 0;
        vivo = false;
    }
}
