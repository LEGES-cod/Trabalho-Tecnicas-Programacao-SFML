#include "FaseMundoInvertido.h"
#include "Vecna.h"
#include "Demodog.h"
#include "EspinhosTentaculo.h"
#include "Demogorgon.h"

FaseMundoInvertido::FaseMundoInvertido() : Fase("mundo_invertido.png") {
    chao.setFillColor(sf::Color(65, 20, 25)); // Tom de terra/vermelho escuro
    inicializar(); // Construtor que inicializa a fase
}

void FaseMundoInvertido::criarInimigos() { // Adiciona os inimigos em posições específicas
    adicionarInimigo(new Demogorgon(sf::Vector2f(320.f, 500.f), pJog1));
    adicionarInimigo(new Vecna(sf::Vector2f(620.f, 500.f), pJog1));
}

void FaseMundoInvertido::criarObstaculos() { // Adiciona os obstáculos em posições específicas
    adicionarObstaculo(new EspinhosTentaculo(sf::Vector2f(470.f, 510.f)));
}
