#include "TroncoCaido.h"
TroncoCaido::TroncoCaido(const sf::Vector2f& posicao) //Implementa o construtor da classe:Repassa a posição recebida, define um tamanho fixo, define uma cor
    : Obstaculo(posicao, sf::Vector2f(110.f, 25.f), sf::Color(110, 65, 25)) {} //marrom escuro
