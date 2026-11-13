#include "FaseMundoInvertido.h"
#include "Vecna.h"
#include "Demodog.h"
#include "EspinhosTentaculo.h"

FaseMundoInvertido::FaseMundoInvertido() : Fase("mundo_invertido.png") {
    chao.setFillColor(sf::Color(65, 20, 25)); // Tom de terra/vermelho escuro
    carregar();
} //Construtor que inicializa a fase chamando carregar()



void FaseMundoInvertido::carregar() { //Adiciona os inimigos e o obstáculo em posições específicas
    adicionarInimigo(std::make_unique<Demodog>(sf::Vector2f(320.f, 500.f)));
    adicionarInimigo(std::make_unique<Vecna>(sf::Vector2f(620.f, 500.f)));
    adicionarObstaculo(std::make_unique<EspinhosTentaculo>(sf::Vector2f(470.f, 510.f)));
}
