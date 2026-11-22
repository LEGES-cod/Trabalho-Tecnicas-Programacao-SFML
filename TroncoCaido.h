#ifndef TRONCOCAIDO_H
#define TRONCOCAIDO_H
#include "Obstaculo.h"

class TroncoCaido : public Obstaculo { // Declara a classe TroncoCaido que herda de Obstaculo.
public:
    explicit TroncoCaido(const sf::Vector2f& posicao); // Declara o construtor expl�cito que recebe apenas a posi��o vetorial onde o tronco ser� colocado no cen�rio.
    void obstacular(Jogador* pJog) override; // Trata a colis�o com o tronco (aterrissagem e bloqueio lateral)
};
#endif
