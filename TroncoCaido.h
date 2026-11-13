#ifndef TRONCOCAIDO_H
#define TRONCOCAIDO_H
#include "Obstaculo.h"
class TroncoCaido : public Obstaculo { //Declara a classe TroncoCaido que herda de Obstaculo.
public:
    explicit TroncoCaido(const sf::Vector2f& posicao); //Declara o construtor explícito que recebe apenas a posição vetorial onde o tronco será colocado no cenário.
};
#endif
