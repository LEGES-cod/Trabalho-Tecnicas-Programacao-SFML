
#include "Jogador.h"
#include <iostream>

Jogador::Jogador()
    : Personagem(sf::Vector2f(80.f, 500.f), sf::Vector2f(35.f, 35.f),
                 sf::Color::Red, 250.f, 100),
      velocidadeY(0.f),
      noChao(true),
      tempoInvencivel(0.f),
      pontos(0),
      tempoDisparo(0.f),
      disparoSolicitado(false),
      direcao(1.f) {}

void Jogador::pular() {
    if (noChao) {
        velocidadeY = FORCA_PULO;
        noChao = false;
    }
}

void Jogador::executar() {
    if (vidas <= 0) return;

    float deltaTime = pGG ? pGG->getDeltaTime() : 0.016f;
    float dx = 0.f;

    if (tempoInvencivel > 0.f)
        tempoInvencivel -= deltaTime;

    if (tempoDisparo > 0.f)
        tempoDisparo -= deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        dx -= velocidade * deltaTime;
        direcao = -1.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        dx += velocidade * deltaTime;
        direcao = 1.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        pular();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
        tempoDisparo <= 0.f) {
        disparoSolicitado = true;
        tempoDisparo = 0.35f;
    }

    velocidadeY += GRAVIDADE * deltaTime;
    float dy = velocidadeY * deltaTime;
    mover(dx, dy);

    sf::Vector2f p = getPosicao();

    if (p.y >= 500.f) {
        p.y = 500.f;
        velocidadeY = 0.f;
        noChao = true;
        setPosicao(p);
    }

    limitarNaTela();
}

bool Jogador::consumirDisparo() {
    if (disparoSolicitado) {
        disparoSolicitado = false;
        return true;
    }

    return false;
}

void Jogador::limitarNaTela() {
    sf::Vector2f p = getPosicao();

    if (p.x < 0.f) p.x = 0.f;
    if (p.x + 35.f > 800.f) p.x = 765.f;

    setPosicao(p);
}

void Jogador::aterrar(float alturaY) {
    sf::Vector2f p = getPosicao();
    p.y = alturaY;

    setPosicao(p);
    velocidadeY = 0.f;
    noChao = true;
}

void Jogador::receberDano(int dano) {
    if (tempoInvencivel <= 0.f && vidas > 0) {
        vidas -= dano;

        if (vidas < 0) {
            vidas = 0;
        }

        tempoInvencivel = 1.0f;

        std::cout << "vidas atual: " << getVidas() << std::endl;
    }
}

void Jogador::adicionarPontos(int p) {
    pontos += p;

    std::cout << "total de pontos: " << getPontos() << std::endl;
}

int Jogador::getPontos() const {
    return pontos;
}
