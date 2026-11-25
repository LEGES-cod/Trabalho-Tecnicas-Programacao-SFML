#include "Demogorgon.h"
#include "Jogador.h"
#include <algorithm>

Demogorgon::Demogorgon(
    const sf::Vector2f& posicao,
    Jogador* pJogador
)
    : Inimigo(posicao, sf::Color(120, 0, 0), pJogador),
      tempoDisparo(1.8f),
      disparoSolicitado(false),
      texturaCarregada(false) {

    // Hitbox compacta ajustada ao corpo visivel do Demogorgon
    corpo.setSize(sf::Vector2f(34.f, 48.f));
    vidas = 30;
    velocidade = 50.f;
    dano = 10;

    if (textura.loadFromFile("demogorgon.png")) {
        textura.setSmooth(false);
        sprite.setTexture(textura);
        sf::Vector2u tamanho = textura.getSize();

        if (tamanho.x > 0 && tamanho.y > 0) {
            float escala = std::min(
                60.f / tamanho.x,
                60.f / tamanho.y
            );
            sprite.setScale(escala, escala);
            texturaCarregada = true;
        }
    }
}

void Demogorgon::executar() {
    if (!estaVivo() || !pGG) return;

    float deltaTime = pGG->getDeltaTime();

    if (pJog) {
        tempoDisparo -= deltaTime;

        if (tempoDisparo <= 0.f) {
            disparoSolicitado = true;
            tempoDisparo = 1.8f;
        }
    }

    aplicarGravidade(deltaTime);
}

void Demogorgon::mover() {
    if (!pJog || !estaVivo()) return;

    float deltaTime = pGG->getDeltaTime();

    sf::Vector2f posicaoDemogorgon = corpo.getPosition();
    sf::Vector2f posicaoJogador = pJog->getLimites().getPosition();

    if (posicaoDemogorgon.x < posicaoJogador.x) {
        posicaoDemogorgon.x += velocidade * deltaTime;
    }
    else if (posicaoDemogorgon.x > posicaoJogador.x) {
        posicaoDemogorgon.x -= velocidade * deltaTime;
    }

    corpo.setPosition(posicaoDemogorgon);
}

void Demogorgon::desenhar() {
    if (!pGG || !estaVivo()) return;

    if (texturaCarregada) {
        sf::FloatRect limites = getLimites();
        sf::FloatRect imagem = sprite.getLocalBounds();

        float largura = imagem.width * sprite.getScale().x;
        float altura = imagem.height * sprite.getScale().y;

        sprite.setPosition(
            limites.left + (limites.width - largura) / 2.f,
            limites.top + limites.height - altura + 5.f
        );

        pGG->desenharElemento(sprite);
    }
    else {
        pGG->desenharElemento(corpo);
    }
}

bool Demogorgon::consumirDisparo() {
    if (!disparoSolicitado) return false;

    disparoSolicitado = false;
    return true;
}
