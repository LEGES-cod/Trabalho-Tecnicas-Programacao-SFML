#include "FaseHawkins.h"
#include "Demogorgon.h"
#include "Demodog.h"
#include "TroncoCaido.h"

FaseHawkins::FaseHawkins() : Fase("hawkins.png") {
    chao.setFillColor(sf::Color(40, 50, 35)); // Tom esverdeado/asfalto escuro
    inicializar(); // Invoca o método inicializar() para instanciar os elementos
}

void FaseHawkins::criarInimigos() { // Instancia os inimigos de Hawkins
    adicionarInimigo(new Demodog(sf::Vector2f(500.f, 500.f), pJog1));
}

void FaseHawkins::criarObstaculos() { // Instancia os obstáculos de Hawkins
    adicionarObstaculo(new TroncoCaido(sf::Vector2f(100.f, 510.f)));
    adicionarObstaculo(new TroncoCaido(sf::Vector2f(600.f, 510.f)));
}
