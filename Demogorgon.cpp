#include "Demogorgon.h"
#include <algorithm>

Demogorgon::Demogorgon(
    const sf::Vector2f& posicao,
    Jogador* pJogador
)
    : Inimigo(posicao, sf::Color(120, 0, 0), pJogador),
      tempoDisparo(1.8f),
      disparoSolicitado(false),
      texturaCarregada(false),
      vidas(30),
      velocidade(50.f) {

    dano = 10;

    // Carrega a imagem PNG do Demogorgon.
    if (textura.loadFromFile("demogorgon.png")) {

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
    if (!vivo || !pGG) return;

    float deltaTime = pGG->getDeltaTime();

    // Persegue o jogador
    mover();

    // Sistema de disparo
    if (pJog) {
        tempoDisparo -= deltaTime;

        if (tempoDisparo <= 0.f) {
            disparoSolicitado = true;
            tempoDisparo = 1.8f;
        }
    }
}

void Demogorgon::mover() {
    if (!pJog || !vivo) return;

    float deltaTime = pGG->getDeltaTime();

    sf::Vector2f posicaoDemogorgon = corpo.getPosition();
    sf::Vector2f posicaoJogador = pJog->getLimites().getPosition();

    // Segue o jogador horizontalmente
    if (posicaoDemogorgon.x < posicaoJogador.x) {
        posicaoDemogorgon.x += velocidade * deltaTime;
    }
    else if (posicaoDemogorgon.x > posicaoJogador.x) {
        posicaoDemogorgon.x -= velocidade * deltaTime;
    }

    corpo.setPosition(posicaoDemogorgon);
}

void Demogorgon::receberDano(int danoRecebido) {
    if (!vivo || danoRecebido <= 0) return;

    vidas -= danoRecebido;

    if (vidas <= 0) {
        vidas = 0;
        vivo = false;
    }
}

int Demogorgon::getVidas() const {
    return vidas;
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
            limites.top + limites.height - altura
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
