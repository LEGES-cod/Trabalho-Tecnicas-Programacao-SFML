#include "BolaDeFogo.h"

BolaDeFogo::BolaDeFogo(const sf::Vector2f& posicao, float velX,
                       int danoProjetil, const sf::Color& cor, float velY)
    : Entidade(posicao, sf::Vector2f(16.f, 16.f), cor),
      velocidade(velX, velY),
      dano(danoProjetil),
      ativo(true) {
    velocidadeY = velY;
}

void BolaDeFogo::executar() {
    if (!ativo) return;

    float deltaTime = pGG ? pGG->getDeltaTime() : 0.016f;
    corpo.move(velocidade.x * deltaTime, 0.f);
    aplicarGravidade(deltaTime, 0.06f);

    sf::Vector2f p = getPosicao();

    if (p.x < -20.f || p.x > 820.f || p.y < -20.f || p.y > 620.f) {
        ativo = false;
    }
}

int BolaDeFogo::getDano() const {
    return dano;
}

bool BolaDeFogo::getAtivo() const {
    return ativo;
}

void BolaDeFogo::desativar() {
    ativo = false;
}

void BolaDeFogo::desenhar() {
    if (ativo) {
        Entidade::desenhar();
    }
}
