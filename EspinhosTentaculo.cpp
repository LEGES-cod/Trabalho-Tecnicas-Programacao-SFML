#include "EspinhosTentaculo.h"
EspinhosTentaculo::EspinhosTentaculo(const sf::Vector2f& posicao) //Inicia a implementação do construtor
    : Obstaculo(posicao, sf::Vector2f(70.f, 30.f), sf::Color(30, 120, 50)) {} //verde escuro
    //Construção para a classe Obstaculo passando, a posição recebida, o tamanho fixo e a cor.
