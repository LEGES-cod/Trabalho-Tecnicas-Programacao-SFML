#ifndef PLATAFORMAESTATICA_H
#define PLATAFORMAESTATICA_H
#include "Obstaculo.h"

class PlataformaEstatica : public Obstaculo { // Declara a classe PlataformaEstatica que herda de Obstaculo conforme o UML.
public:
    PlataformaEstatica(const sf::Vector2f& posicao, const sf::Vector2f& tamanho); // Declara o construtor da classe, recebendo a posição inicial e as dimensões (tamanho) da plataforma
    void obstacular(Jogador* pJog) override; // Permite aterrissagem e bloqueio lateral
};
#endif
