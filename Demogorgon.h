#ifndef DEMOGORGON_H
#define DEMOGORGON_H
#include "Inimigo.h"

class Demogorgon : public Inimigo { // Declara a classe Demogorgon e herda publicamente Inimigo.
public:
    explicit Demogorgon(const sf::Vector2f& posicao, Jogador* pJogador = nullptr); // Declara um construtor Demogorgon que recebe a posi��o do Demogorgon.
};
#endif
