#include "Demodog.h"
#include <cmath>

Demodog::Demodog(const sf::Vector2f& posicao, Jogador* pJogador)
    : Inimigo(posicao, sf::Color(80, 40, 20), pJogador),
      limiteEsquerdo(posicao.x - 100.f),
      limiteDireito(posicao.x + 100.f),
      indoDireita(true),
      raioVisao(180.f),
      velocidadeAtaque(200.f) {

    corpo.setSize(sf::Vector2f(60.f, 60.f));

    if (textura.loadFromFile("demodog.png")) {
        sprite.setTexture(textura);

        sf::Vector2u tamanho = textura.getSize();

        sprite.setScale(
            60.f / tamanho.x,
            60.f / tamanho.y
        );
    }
}

void Demodog::desenhar() {
    if (pGG && estaVivo()) {
        sprite.setPosition(getPosicao().x, getPosicao().y - 20.f);
        pGG->desenharElemento(sprite);
    }
}

void Demodog::inverterDirecao() {
    indoDireita = !indoDireita;
}

void Demodog::executar() {
    if (!estaVivo()) return;

    float deltaTime = pGG ? pGG->getDeltaTime() : 0.016f;
    sf::Vector2f posAtual = getPosicao();
    sf::Vector2f posJogador = pJog ? pJog->getPosicao() : sf::Vector2f(-1000.f, -1000.f);
    float distanciax = posJogador.x - posAtual.x;

    if (pJog && std::abs(distanciax) <= raioVisao) {
        if (distanciax > 0.f) {
            mover(velocidadeAtaque * deltaTime * 0.6f, 0.f);
        } else {
            mover(-velocidadeAtaque * deltaTime * 0.6f, 0.f);
        }
    } else {
        float velPatrulhia = 80.f;
        if (indoDireita) {
            mover(velPatrulhia * deltaTime, 0.f);
            if (getPosicao().x >= limiteDireito || getPosicao().x >= 765.f) {
                indoDireita = false;
            }
        } else {
            mover(-velPatrulhia * deltaTime, 0.f);
            if (getPosicao().x <= limiteEsquerdo || getPosicao().x <= 0.f) {
                indoDireita = true;
            }
        }
    }
}
