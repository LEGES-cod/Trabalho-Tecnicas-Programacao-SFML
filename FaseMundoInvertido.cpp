#include "FaseMundoInvertido.h"
#include "Vecna.h"
#include "Demodog.h"
#include "EspinhosTentaculo.h"
#include "Demogorgon.h"

FaseMundoInvertido::FaseMundoInvertido() : Fase("mundo_invertido.png", sf::Color(65, 20, 25)) {
    inicializar(); // Inicializa jogador, chão e plataforma
    criarDemogorgon();
    criarVecna();
    criarEspinhosTentaculo();
}

void FaseMundoInvertido::criarDemogorgon() {
    adicionarInimigo(new Demogorgon(sf::Vector2f(320.f, 500.f), pJog1));
}

void FaseMundoInvertido::criarVecna() {
    adicionarInimigo(new Vecna(sf::Vector2f(620.f, 500.f), pJog1));
}

void FaseMundoInvertido::criarEspinhosTentaculo() {
    adicionarObstaculo(new EspinhosTentaculo(sf::Vector2f(470.f, 510.f)));
}
