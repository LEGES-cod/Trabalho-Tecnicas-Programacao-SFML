#include "FaseHawkins.h"
#include "Demogorgon.h"
#include "Demodog.h"
#include "TroncoCaido.h"

FaseHawkins::FaseHawkins() { carregar(); } //Construtor que invoca automaticamento o método carregar() para instanciar os elementos na crianção
void FaseHawkins::carregar() { //Implementa o carregamento criando dinamicamente instãncias através de std::make_unique e posicionando elas nas coordenadas verticais indicadas
    adicionarInimigo(std::make_unique<Demogorgon>(sf::Vector2f(350.f, 500.f)));
    adicionarInimigo(std::make_unique<Demodog>(sf::Vector2f(600.f, 500.f)));
    adicionarObstaculo(std::make_unique<TroncoCaido>(sf::Vector2f(230.f, 510.f)));
}
