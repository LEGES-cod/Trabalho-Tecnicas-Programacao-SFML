#include "Vecna.h"
#include "Jogador.h"
#include <algorithm>
#include <cmath>

Vecna::Vecna(const sf::Vector2f& posicao, Jogador* pJogador)
    : Inimigo(posicao, sf::Color(90, 0, 110), pJogador),
      tempoAtaque(2.2f),
      ataqueSolicitado(false),
      texturaCarregada(false) {

    // Hitbox compacta ajustada ao corpo visivel do Vecna
    corpo.setSize(sf::Vector2f(36.f, 52.f));
    vidas = 50;
    velocidade = 75.f;
    dano = 15;

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
        float dx = pJog->getPosicao().x - getPosicao().x;
        if (std::abs(dx) > 120.f) {
            mover((dx > 0.f ? 1.f : -1.f) * velocidade * deltaTime, 0.f);
        }

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
