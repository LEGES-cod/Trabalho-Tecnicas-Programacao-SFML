
#include "FaseHawkins.h"
#include "Demogorgon.h"
#include "Demodog.h"
#include "TroncoCaido.h"

FaseHawkins::FaseHawkins() : Fase("hawkins.png", sf::Color(40, 50, 35)) {
    exigirDerrotaInimigos = true;

    inicializar();
    criarDemodog();
    criarTroncosCaidos();
}

void FaseHawkins::criarDemodog() {
    adicionarInimigo(new Demodog(sf::Vector2f(500.f, 500.f), pJog1));
}

void FaseHawkins::criarTroncosCaidos() {
    adicionarObstaculo(new TroncoCaido(sf::Vector2f(100.f, 510.f)));
    adicionarObstaculo(new TroncoCaido(sf::Vector2f(600.f, 510.f)));
}

