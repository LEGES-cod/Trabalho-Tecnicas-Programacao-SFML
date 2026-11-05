#include "Vecna.h"
Vecna::Vecna(const sf::Vector2f& posicao) //Implementa o construtor da classe: passa a posição recebida, define uma cor
    : Inimigo(posicao, sf::Color(90, 0, 110)) {} //roxo escuro
