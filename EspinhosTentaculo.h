#ifndef ESPINHOSTENTACULO_H
#define ESPINHOSTENTACULO_H
#include "Obstaculo.h"
class EspinhosTentaculo : public Obstaculo { //Declara a classe EspinhosTentaculo, herdando de Obstaculo
public:
    explicit EspinhosTentaculo(const sf::Vector2f& posicao); //Declara o costrutor que recebe a posição onde o obstáculo será colocado
};
#endif
