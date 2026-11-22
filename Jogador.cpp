#include "Jogador.h"
#include <iostream>
#include <algorithm>

Jogador::Jogador()
    : Personagem(sf::Vector2f(80.f, 500.f),
                 sf::Vector2f(35.f, 35.f),
                 sf::Color::Red, 250.f, 100),
      velocidadeY(0.f),
      noChao(true),
      tempoInvencivel(0.f),
      pontos(0),
      tempoDisparo(0.f),
      disparoSolicitado(false),
      direcao(1.f),
      sangrando(false),
      tempoDanoContinuo(0.f),
      acumuladorCura(0.f),
      personagemCarregado(false) {}

void Jogador::setPersonagem(int indice) {

    const char* arquivos[6] = {
        "dustin.jpg",
        "eleven.png",
        "lucas.jpg",
        "max.jpg",
        "mike.jpg",
        "will.png"
    };

    if (indice < 0 || indice >= 6) {
        return;
    }

    personagemCarregado =
        texturaPersonagem.loadFromFile(arquivos[indice]);

    if (personagemCarregado) {
        texturaPersonagem.setSmooth(true);
        spritePersonagem.setTexture(texturaPersonagem);
    }
}

void Jogador::desenhar() {

    if (!pGG) return;

    if (personagemCarregado) {

        sf::FloatRect limites = getLimites();
        sf::FloatRect imagem = spritePersonagem.getLocalBounds();

        if (imagem.width > 0.f && imagem.height > 0.f) {

            // Mantém a proporção da imagem.
            float escala = std::min(
                limites.width / imagem.width,
                limites.height / imagem.height
            );

            spritePersonagem.setScale(escala, escala);

            float largura = imagem.width * escala;
            float altura = imagem.height * escala;

            // Posiciona a imagem no lugar do retângulo do jogador.
            spritePersonagem.setPosition(
                limites.left + (limites.width - largura) / 2.f,
                limites.top + (limites.height - altura) / 2.f
            );

            pGG->desenharElemento(spritePersonagem);
            return;
        }
    }

    // Mantém o retângulo original caso não carregue uma imagem.
    pGG->desenharElemento(corpo);
}

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

    atualizarDanoContinuo(deltaTime);

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

void Jogador::baterCabeca(float alturaY) {
    sf::Vector2f p = getPosicao();
    p.y = alturaY;

    setPosicao(p);
    velocidadeY = 0.f;
    noChao = false;
}

void Jogador::receberDano(int dano) {
    if (tempoInvencivel <= 0.f && vidas > 0) {
        vidas -= dano;

        if (vidas < 0) {
            vidas = 0;
        }

        tempoInvencivel = 1.0f;

        std::cout << "vidas atual: "
                  << getVidas() << std::endl;
    }
}

void Jogador::iniciarDanoContinuo() {
    if (vidas > 0) {
        if (!sangrando) {
            sangrando = true;
            tempoDanoContinuo = 0.f;
        }
    }
}

void Jogador::atualizarDanoContinuo(float deltaTime) {
    if (!sangrando || vidas <= 0) return;

    tempoDanoContinuo += deltaTime;

    const float intervaloDano = 0.6f;

    while (tempoDanoContinuo >= intervaloDano && vidas > 0) {
        tempoDanoContinuo -= intervaloDano;
        vidas -= 1;

        if (vidas < 0) {
            vidas = 0;
        }

        std::cout << "vidas atual: "
                  << getVidas() << std::endl;
    }
}

void Jogador::curarGradualmente(float deltaTime) {
    if (vidas <= 0) return;

    sangrando = false;
    tempoDanoContinuo = 0.f;

    acumuladorCura += deltaTime;
    const float intervaloCura = 0.9f;

    if (acumuladorCura >= intervaloCura) {
        acumuladorCura -= intervaloCura;

        if (vidas < 100) {
            vidas += 1;

            std::cout << "vidas atual: "
                      << getVidas() << std::endl;
        }
    }
}

void Jogador::adicionarPontos(int p) {
    pontos += p;
}

int Jogador::getPontos() const {
    return pontos;
}
