#include "Vecna.h"
#include "Jogador.h"
#include <algorithm>
#include <cmath>

Vecna::Vecna(const sf::Vector2f& posicao, Jogador* pJogador)
    : Inimigo(posicao, sf::Color(90, 0, 110), pJogador, 3),
      forca(1),
      tempoAtaque(2.2f),
      ataqueSolicitado(false),
      indoDireita(false),
      texturaCarregada(false) {

    corpo.setSize(sf::Vector2f(36.f, 52.f));
    vidas = 15;
    velocidade = 85.f;
    dano = 1;

    if (textura.loadFromFile("vecna.png")) {
        textura.setSmooth(false);
        sprite.setTexture(textura);
        sf::Vector2u tam = textura.getSize();
        if (tam.x > 0 && tam.y > 0) {
            float escala = std::min(55.f / tam.x, 65.f / tam.y);
            sprite.setScale(escala, escala);
            texturaCarregada = true;
        }
    }
}

void Vecna::executar() {
    if (!estaVivo() || !pGG) return;

    float deltaTime = pGG->getDeltaTime();

    if (pJog) {
        float posX = getPosicao().x;
        float dx = pJog->getPosicao().x - posX;
        float distancia = std::abs(dx);
        float deslocamentoX = 0.f;

        if (distancia > 200.f) {
            deslocamentoX = (dx > 0.f ? 1.f : -1.f) * velocidade * deltaTime;
        }
        else if (distancia < 110.f) {
            deslocamentoX = (dx > 0.f ? -1.f : 1.f) * (velocidade * 0.85f) * deltaTime;
        }
        else {
            deslocamentoX = (indoDireita ? 1.f : -1.f) * (velocidade * 0.5f) * deltaTime;
        }

        float proximoX = posX + deslocamentoX;
        if (proximoX < 20.f) {
            deslocamentoX = 20.f - posX;
            indoDireita = true;
        }
        else if (proximoX > 740.f) {
            deslocamentoX = 740.f - posX;
            indoDireita = false;
        }

        mover(deslocamentoX, 0.f);

        tempoAtaque -= deltaTime;
        if (tempoAtaque <= 0.f) {
            ataqueSolicitado = true;
            tempoAtaque = 2.2f;
        }
    }

    aplicarGravidade(deltaTime);
}

void Vecna::desenhar() {
    if (!pGG || !estaVivo()) return;

    if (texturaCarregada) {
        sf::FloatRect limites = getLimites();
        sf::FloatRect img = sprite.getLocalBounds();
        float w = img.width * sprite.getScale().x;
        float h = img.height * sprite.getScale().y;
        sprite.setPosition(
            limites.left + (limites.width - w) / 2.f,
            limites.top + limites.height - h + 5.f
        );
        pGG->desenharElemento(sprite);
    } else {
        pGG->desenharElemento(corpo);
    }
}

bool Vecna::consumirAtaque() {
    if (!ataqueSolicitado) return false;
    ataqueSolicitado = false;
    return true;
}
