
#include "FaseHawkins.h"
#include "Demogorgon.h"
#include "Demodog.h"
#include "TroncoCaido.h"
#include "PlataformaEstatica.h"

FaseHawkins::FaseHawkins() : Fase("hawkins.png") {
    exigirDerrotaInimigos = true;

    chao.setFillColor(sf::Color(40, 50, 35));
    inicializar();
}

void FaseHawkins::criarInimigos() {
    adicionarInimigo(new Demodog(sf::Vector2f(500.f, 500.f), pJog1));
    adicionarInimigo(new Demodog(sf::Vector2f(300.f, 500.f), pJog1));
}

void FaseHawkins::criarObstaculos() {
    adicionarObstaculo(new TroncoCaido(sf::Vector2f(100.f, 510.f)));
    adicionarObstaculo(new TroncoCaido(sf::Vector2f(600.f, 510.f)));
    adicionarObstaculo(new PlataformaEstatica(sf::Vector2f(325.f, 410.f), sf::Vector2f(150.f, 20.f)));//adiciona a plataforma no meio da primeira fase
}

