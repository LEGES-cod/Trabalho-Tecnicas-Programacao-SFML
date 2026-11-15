#ifndef ESPINHOSTENTACULO_H
#define ESPINHOSTENTACULO_H
#include "Obstaculo.h"

class EspinhosTentaculo : public Obstaculo { // Declara a classe EspinhosTentaculo, herdando de Obstaculo
private:
    int danoEspinhos;

public:
    explicit EspinhosTentaculo(const sf::Vector2f& posicao); // Declara o construtor que recebe a posição onde o obstáculo será colocado
    void obstacular(Jogador* pJog) override; // Aplica dano ao jogador ao tocar nos espinhos
};
#endif
