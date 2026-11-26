#include "Demodog.h"
#include "Jogador.h"
#include <cmath>

Demodog::Demodog(const sf::Vector2f& posicao, Jogador* pJogador)
    : Inimigo(posicao, sf::Color(80, 40, 20), pJogador, 1),
      limiteEsquerdo(posicao.x - 100.f),
      limiteDireito(posicao.x + 100.f),
      indoDireita(true),
      raioVisao(180.f),
      velocidadeAtaque(200.f) {

    corpo.setSize(sf::Vector2f(40.f, 35.f));
    vidas = 5;
    dano = 1;

    if (textura.loadFromFile("demodog.png")) {
        textura.setSmooth(false);
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
        sf::FloatRect limites = getLimites();
        sf::FloatRect imagem = sprite.getLocalBounds();
        float largura = imagem.width * sprite.getScale().x;
        float altura = imagem.height * sprite.getScale().y;

        sprite.setPosition(
            limites.left + (limites.width - largura) / 2.f,
            limites.top + limites.height - altura + 11.f
        );
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
            if (getPosicao().x >= limiteDireito || getPosicao().x >= 760.f) {
                indoDireita = false;
            }
        } else {
            mover(-velPatrulhia * deltaTime, 0.f);
            if (getPosicao().x <= limiteEsquerdo || getPosicao().x <= 0.f) {
                indoDireita = true;
            }
        }
    }
    aplicarGravidade(deltaTime);
}
