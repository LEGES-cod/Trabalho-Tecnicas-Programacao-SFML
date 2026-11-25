#include "Jogador.h"
#include <iostream>
#include <algorithm>

Jogador::Jogador(int id)
    : Personagem(sf::Vector2f(id == 1 ? 80.f : 145.f, 499.f),
                 sf::Vector2f(40.f, 36.f),
                 id == 1 ? sf::Color::Red : sf::Color::Blue, 250.f, 100),
      idJogador(id),
      velocidadeY(0.f),
      noChao(true),
      tempoInvencivel(0.f),
      pontos(0),
      tempoDisparo(0.35f),
      disparoSolicitado(false),
      direcao(1.f),
      sangrando(false),
      tempoDanoContinuo(0.f),
      acumuladorCura(0.f),
      personagemCarregado(false) {}

void Jogador::setPersonagem(int indice) {
    const char* arquivos[2] = {
        "mike.jpg",
        "eleven.png"
    };

    if (indice < 0 || indice >= 2) {
        return;
    }

    personagemCarregado =
        texturaPersonagem.loadFromFile(arquivos[indice]);

    if (personagemCarregado) {
        texturaPersonagem.setSmooth(false);
        spritePersonagem.setTexture(texturaPersonagem);
    }
}

void Jogador::desenhar() {
    if (!pGG) return;

    if (personagemCarregado) {
        sf::FloatRect limites = getLimites();
        sf::FloatRect imagem = spritePersonagem.getLocalBounds();

        if (imagem.width > 0.f && imagem.height > 0.f) {
            const float tamanhoVisual = 55.f;
            float escala = std::min(
                tamanhoVisual / imagem.width,
                tamanhoVisual / imagem.height
            );

            spritePersonagem.setScale(escala, escala);

            float largura = imagem.width * escala;
            float altura = imagem.height * escala;

            // Mantem os pes no chao e o topo da hitbox alinhado com o cabelo
            spritePersonagem.setPosition(
                limites.left + (limites.width - largura) / 2.f,
                limites.top + limites.height - altura + 7.f
            );

            pGG->desenharElemento(spritePersonagem);
            return;
        }
    }

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

    if (idJogador == 1) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            dx -= velocidade * deltaTime;
            direcao = -1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            dx += velocidade * deltaTime;
            direcao = 1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            pular();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
            tempoDisparo <= 0.f) {
            disparoSolicitado = true;
            tempoDisparo = 0.35f;
        }
    }
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            dx -= velocidade * deltaTime;
            direcao = -1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            dx += velocidade * deltaTime;
            direcao = 1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            pular();
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) &&
            tempoDisparo <= 0.f) {
            disparoSolicitado = true;
            tempoDisparo = 0.35f;
        }
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
    float largura = getLimites().width;

    if (p.x < 0.f) p.x = 0.f;
    if (p.x + largura > 800.f) p.x = 800.f - largura;

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

        std::cout << "Jogador " << idJogador
                  << " vidas atual: " << getVidas() << std::endl;
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
        }
    }
}

void Jogador::adicionarPontos(int p) {
    pontos += p;
}

int Jogador::getPontos() const {
    return pontos;
}
