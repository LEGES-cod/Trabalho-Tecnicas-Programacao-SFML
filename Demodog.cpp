#include "Demodog.h"
Demodog::Demodog(const sf::Vector2f& posicao) //Inicia o construtor da classe Demodog, aceitando a posição inicial
    : Inimigo(posicao, sf::Color(80, 40, 20)) {} //Marrom escuro
     //Chama o construtor da classe Inimigo, passando a posição e um cor (RGB)
