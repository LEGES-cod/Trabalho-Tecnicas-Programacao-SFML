#include "Projetil.h"

Projetil::Projetil(const sf::Vector2f& posicao, float velX, int danoProjetil)
    : Entidade(posicao, sf::Vector2f(12.f, 12.f), sf::Color::Magenta),
      velocidadeX(velX), dano(danoProjetil), ativo(true) {}

void Projetil::executar() {
    if (!ativo) return;
    float deltaTime = pGG ? pGG->getDeltaTime() : 0.016f;
    corpo.move(velocidadeX * deltaTime, 0.f);

    if (getPosicao().x < 0.f || getPosicao().x > 800.f) {
        ativo = false;
    }
}

int Projetil::getDano() const { return dano; }
bool Projetil::getAtivo() const { return ativo; }
void Projetil::desativar() { ativo = false; }
