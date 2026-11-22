#ifndef ESPINHOSTENTACULO_H
#define ESPINHOSTENTACULO_H
#include "Obstaculo.h"

class EspinhosTentaculo : public Obstaculo { // Declara a classe EspinhosTentaculo, herdando de Obstaculo
private:
    int danoEspinhos;

public:
    explicit EspinhosTentaculo(const sf::Vector2f& posicao); // Declara o construtor que recebe a posi��o onde o obst�culo ser� colocado
    void obstacular(Jogador* pJog) override; // Aplica dano ao jogador ao tocar nos espinhos
};
#endif
