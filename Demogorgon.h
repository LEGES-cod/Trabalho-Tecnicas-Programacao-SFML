#ifndef DEMOGORGON_H
#define DEMOGORGON_H
#include "Inimigo.h"
class Demogorgon : public Inimigo { //Declara a classe Demogorgon e herda publicamente Inimigo.
public:
    explicit Demogorgon(const sf::Vector2f& posicao); //Declara um construtor Demogorgon que recebe a posição do Demogorgon.
};
#endif
