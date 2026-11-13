#include "Demogorgon.h"
Demogorgon::Demogorgon(const sf::Vector2f& posicao) //Implementa o construtor da classe Demogorgon.
    : Inimigo(posicao, sf::Color(120, 0, 0)) //vermelho escuro
    {
        dano = 10;
    }

    //Chama o construtor da classe Inimigo, e passa a posi��o e a cor (RGB)
