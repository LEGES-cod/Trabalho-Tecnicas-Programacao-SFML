#include "Demogorgon.h"
Demogorgon::Demogorgon(const sf::Vector2f& posicao) //Implementa o construtor da classe Demogorgon.
    : Inimigo(posicao, sf::Color(120, 0, 0)) {} //vermelho escuro
    //Chama o construtor da classe Inimigo, e passa a posição e a cor (RGB)
