#include "PlataformaEstatica.h"
#include <cmath>

PlataformaEstatica::PlataformaEstatica(
    const sf::Vector2f& posicao,
    const sf::Vector2f& tamanho)
    : Obstaculo(posicao, tamanho, sf::Color(100, 100, 100), false) {}

void PlataformaEstatica::obstacular(Jogador* pJog) {
    if (!pJog) return;

    float deltaTime = pGG ? pGG->getDeltaTime() : 0.016f;

    sf::FloatRect rectJogador = pJog->getLimites();
    sf::FloatRect rectPlataforma = getLimites();

    float velocidadeY = pJog->getVelocidadeY();

    float topoPlataforma = rectPlataforma.top;
    float basePlataforma =
        rectPlataforma.top + rectPlataforma.height;

    float baseJogador =
        rectJogador.top + rectJogador.height;

    float baseAnterior =
        baseJogador - velocidadeY * deltaTime;

    float topoAnterior =
        rectJogador.top - velocidadeY * deltaTime;

    // Verifica se o jogador está horizontalmente sobre a plataforma.
    bool alinhadoHorizontalmente =
        rectJogador.left + rectJogador.width > rectPlataforma.left &&
        rectJogador.left < rectPlataforma.left + rectPlataforma.width;

    // Verifica se o jogador está apoiado ou acabou de aterrissar.
    bool apoiado =
        alinhadoHorizontalmente &&
        velocidadeY >= 0.f &&
        std::abs(baseJogador - topoPlataforma) <= 6.f;

    bool aterrissando =
        alinhadoHorizontalmente &&
        velocidadeY > 0.f &&
        baseAnterior <= topoPlataforma + 2.f &&
        baseJogador >= topoPlataforma - 2.f;

    if (apoiado || aterrissando) {

        // Ajusta a posição para manter o jogador sobre a plataforma.
        pJog->aterrar(topoPlataforma - rectJogador.height);

        // Interrompe o dano contínuo e recupera vida.
        pJog->curarGradualmente(deltaTime);

        return;
    }

    // Se não existe interseção, não há colisão lateral ou inferior.
    if (!rectJogador.intersects(rectPlataforma)) {
        return;
    }

    // Colisão por baixo da plataforma.
    if (velocidadeY < 0.f &&
        topoAnterior >= basePlataforma - 10.f) {

        pJog->baterCabeca(basePlataforma);
    }

    // Colisão lateral esquerda.
    else if (rectJogador.left < rectPlataforma.left) {

        pJog->setPosicao(sf::Vector2f(
            rectPlataforma.left - rectJogador.width,
            rectJogador.top
        ));
    }

    // Colisão lateral direita.
    else if (rectJogador.left > rectPlataforma.left) {

        pJog->setPosicao(sf::Vector2f(
            rectPlataforma.left + rectPlataforma.width,
            rectJogador.top
        ));
    }
}
