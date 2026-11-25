#include "TroncoCaido.h"
#include <cmath>

TroncoCaido::TroncoCaido(const sf::Vector2f& posicao)
    : Obstaculo(
        sf::Vector2f(posicao.x, posicao.y),
        sf::Vector2f(65.f, 18.f),
        sf::Color(110, 65, 25),
        false
      ),
      texturaCarregada(false) {

    if (textura.loadFromFile("tronco.png")) {
        textura.setSmooth(false);
        sprite.setTexture(textura);

        sf::Vector2u tam = textura.getSize();
        if (tam.x > 0 && tam.y > 0) {
            // 75.f faz o tronco visivel (~87% da imagem) bater exatamente com os 65px da hitbox
            float escala = 75.f / static_cast<float>(tam.x);
            sprite.setScale(escala, escala);
            texturaCarregada = true;
        }
    }
}

void TroncoCaido::obstacular(Jogador* pJog) {
    if (!pJog) return;

    float deltaTime = pGG ? pGG->getDeltaTime() : 0.016f;

    sf::FloatRect rectJogador = pJog->getLimites();
    sf::FloatRect rectObstaculo = getLimites();

    float velocidadeY = pJog->getVelocidadeY();
    float baseJogador = rectJogador.top + rectJogador.height;
    float baseAnterior = baseJogador - velocidadeY * deltaTime;

    if (velocidadeY >= 0.f && baseAnterior <= rectObstaculo.top + 8.f) {
        pJog->aterrar(rectObstaculo.top - rectJogador.height);
        return;
    }

    sf::FloatRect intersecao;
    if (!rectJogador.intersects(rectObstaculo, intersecao)) {
        return;
    }

    if (intersecao.width < intersecao.height) {
        float centroJog = rectJogador.left + rectJogador.width / 2.f;
        float centroObs = rectObstaculo.left + rectObstaculo.width / 2.f;

        if (centroJog < centroObs) {
            pJog->setPosicao(sf::Vector2f(
                rectObstaculo.left - rectJogador.width,
                rectJogador.top
            ));
        }
        else {
            pJog->setPosicao(sf::Vector2f(
                rectObstaculo.left + rectObstaculo.width,
                rectJogador.top
            ));
        }
    }
}

void TroncoCaido::desenhar() {
    if (!pGG) return;

    if (texturaCarregada) {
        sf::FloatRect limites = getLimites();
        sf::FloatRect img = sprite.getLocalBounds();

        float largura = img.width * sprite.getScale().x;
        float altura = img.height * sprite.getScale().y;

        // +12.f compensa a margem transparente inferior do novo tronco.png
        sprite.setPosition(
            limites.left + (limites.width - largura) / 2.f,
            limites.top + limites.height - altura + 12.f
        );

        pGG->desenharElemento(sprite);
    }
    else {
        pGG->desenharElemento(corpo);
    }
}
