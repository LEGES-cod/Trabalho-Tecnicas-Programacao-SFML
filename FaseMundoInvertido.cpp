#include "FaseMundoInvertido.h"
#include "Vecna.h"
#include "Demodog.h"
#include "EspinhosTentaculo.h"
#include "PlataformaEstatica.h"
#include <cstdlib>

FaseMundoInvertido::FaseMundoInvertido(bool carregando) : Fase("mundo_invertido.png", sf::Color(65, 20, 25)) {
    exigirDerrotaInimigos = true;

    inicializar();

    if (carregando) return;

    int qtdPlataformas = 6 + (std::rand() % 3);
    sf::Vector2f posPlat[8] = {
        sf::Vector2f(95.f,  445.f),
        sf::Vector2f(430.f, 445.f),
        sf::Vector2f(25.f,  355.f),
        sf::Vector2f(255.f, 355.f),
        sf::Vector2f(620.f, 355.f),
        sf::Vector2f(135.f, 265.f),
        sf::Vector2f(455.f, 265.f),
        sf::Vector2f(275.f, 165.f)
    };
    sf::Vector2f tamPlat[8] = {
        sf::Vector2f(155.f, 16.f),
        sf::Vector2f(195.f, 16.f),
        sf::Vector2f(145.f, 16.f),
        sf::Vector2f(180.f, 16.f),
        sf::Vector2f(155.f, 16.f),
        sf::Vector2f(160.f, 16.f),
        sf::Vector2f(185.f, 16.f),
        sf::Vector2f(170.f, 16.f)
    };

    for (int i = 0; i < qtdPlataformas; i++) {
        adicionarObstaculo(new PlataformaEstatica(posPlat[i], tamPlat[i]));
    }

    criarEspinhosTentaculo();
    criarDemodog();
    criarVecna();
}

void FaseMundoInvertido::criarDemodog() {
    int qtd = 3 + (std::rand() % 2);
    sf::Vector2f posDog[4] = {
        sf::Vector2f(350.f, 480.f),
        sf::Vector2f(660.f, 480.f),
        sf::Vector2f(445.f, 390.f),
        sf::Vector2f(265.f, 300.f)
    };
    for (int i = 0; i < qtd; i++) {
        adicionarInimigo(new Demodog(posDog[i], pJog1));
    }
}

void FaseMundoInvertido::criarVecna() {
    int qtd = 3;
    sf::Vector2f posVecna[3] = {
        sf::Vector2f(65.f,  285.f),
        sf::Vector2f(675.f, 285.f),
        sf::Vector2f(215.f, 195.f)
    };
    for (int i = 0; i < qtd; i++) {
        adicionarInimigo(new Vecna(posVecna[i], pJog1));
    }
}

void FaseMundoInvertido::criarEspinhosTentaculo() {
    int qtd = 3 + (std::rand() % 3);
    sf::Vector2f posEspinhos[5] = {
        sf::Vector2f(210.f, 513.f),
        sf::Vector2f(520.f, 513.f),
        sf::Vector2f(555.f, 423.f),
        sf::Vector2f(365.f, 333.f),
        sf::Vector2f(145.f, 243.f)
    };
    for (int i = 0; i < qtd; i++) {
        adicionarObstaculo(new EspinhosTentaculo(posEspinhos[i]));
    }
}
