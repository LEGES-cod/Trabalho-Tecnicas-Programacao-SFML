#include "BolaDeFogo.h"

BolaDeFogo::BolaDeFogo(const sf::Vector2f& posicao, float velX,
                   int danoProjetil, const sf::Color& cor)
    : Entidade(posicao, sf::Vector2f(16.f, 16.f), cor),
      velocidadeX(velX),
      dano(danoProjetil),
      ativo(true) {}

void BolaDeFogo::executar() {
    if (!ativo) return;

    float deltaTime = pGG ? pGG->getDeltaTime() : 0.016f;
    corpo.move(velocidadeX * deltaTime, 0.f);

    if (getPosicao().x < 0.f || getPosicao().x > 800.f) {
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
