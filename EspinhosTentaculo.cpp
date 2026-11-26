#include "EspinhosTentaculo.h"
#include <algorithm>
#include <cmath>

EspinhosTentaculo::EspinhosTentaculo(const sf::Vector2f& posicao)
    : Obstaculo(
        sf::Vector2f(posicao.x, posicao.y),
        sf::Vector2f(60.f, 22.f),
        sf::Color(150, 20, 40),
        true
      ),
      texturaCarregada(false),
      danosidade(2),
      tempoPulso(0.f) {

    if (textura.loadFromFile("espinhos.png")) {
        textura.setSmooth(false);
        sprite.setTexture(textura);

        sf::Vector2u tam = textura.getSize();
        if (tam.x > 0 && tam.y > 0) {
            // Mantem a largura visual de 68px e altura proporcional
            float escala = 68.f / static_cast<float>(tam.x);
            sprite.setScale(escala, escala);
            texturaCarregada = true;
        }
    }
}

void EspinhosTentaculo::executar() {
    float deltaTime = pGG ? pGG->getDeltaTime() : 0.016f;
    Obstaculo::executar();

    tempoPulso += deltaTime * 4.f;
    sf::Uint8 brilho = static_cast<sf::Uint8>(215 + 40 * std::sin(tempoPulso));

    if (texturaCarregada) {
        sprite.setColor(sf::Color(255, brilho, brilho));
    }
    else {
        corpo.setFillColor(sf::Color(brilho, 20, 40));
    }
}

void EspinhosTentaculo::obstacular(Jogador* pJog) {
    if (!pJog) return;

    if (pJog->getLimites().intersects(getLimites())) {
        pJog->receberDano(danosidade);
        pJog->iniciarDanoContinuo();
    }
}

void EspinhosTentaculo::desenhar() {
    if (!pGG) return;

    if (texturaCarregada) {
        sf::FloatRect limites = getLimites();
        sf::FloatRect img = sprite.getLocalBounds();

        float largura = img.width * sprite.getScale().x;
        float altura = img.height * sprite.getScale().y;

        // Alinha a base dos tentaculos no chao e nas plataformas (+3.f compensa a margem inferior)
        sprite.setPosition(
            limites.left + (limites.width - largura) / 2.f,
            limites.top + limites.height - altura + 3.f
        );

        pGG->desenharElemento(sprite);
    }
    else {
        pGG->desenharElemento(corpo);
    }
}
