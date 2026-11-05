#ifndef DEMODOG_H
#define DEMODOG_H
#include "Inimigo.h"
class Demodog : public Inimigo { //declara a classe que herda da classe Inimigo
public:
    explicit Demodog(const sf::Vector2f& posicao); //Declara o construtor de classe que recebe uma posição bidimensional por referÊncia constante
};
#endif
