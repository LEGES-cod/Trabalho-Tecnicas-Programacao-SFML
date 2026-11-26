#include "FaseHawkins.h"
#include "Demogorgon.h"
#include "Demodog.h"
#include "TroncoCaido.h"
#include "PlataformaEstatica.h"
#include <cstdlib>

FaseHawkins::FaseHawkins(bool carregando) : Fase("hawkins.png", sf::Color(40, 50, 35)) {
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

    criarTroncosCaidos();
    criarDemodog();

    int qtdDemogorgons = (qtdPlataformas >= 7) ? 4 : 3;
    sf::Vector2f posDemo[4] = {
        sf::Vector2f(65.f,  295.f),
        sf::Vector2f(675.f, 295.f),
        sf::Vector2f(190.f, 205.f),
        sf::Vector2f(520.f, 205.f)
    };
    for (int i = 0; i < qtdDemogorgons; i++) {
        adicionarInimigo(new Demogorgon(posDemo[i], pJog1));
    }
}

void FaseHawkins::criarDemodog() {
    int qtd = 3 + (std::rand() % 2);
    sf::Vector2f posDog[4] = {
        sf::Vector2f(350.f, 480.f),
        sf::Vector2f(660.f, 480.f),
        sf::Vector2f(450.f, 390.f),
        sf::Vector2f(270.f, 300.f)
    };
    for (int i = 0; i < qtd; i++) {
        adicionarInimigo(new Demodog(posDog[i], pJog1));
    }
}

void FaseHawkins::criarTroncosCaidos() {
    int qtd = 3 + (std::rand() % 3);
    sf::Vector2f posTronco[5] = {
        sf::Vector2f(210.f, 517.f),
        sf::Vector2f(520.f, 517.f),
        sf::Vector2f(550.f, 427.f),
        sf::Vector2f(360.f, 337.f),
        sf::Vector2f(155.f, 247.f)
    };
    for (int i = 0; i < qtd; i++) {
        adicionarObstaculo(new TroncoCaido(posTronco[i]));
    }
}
