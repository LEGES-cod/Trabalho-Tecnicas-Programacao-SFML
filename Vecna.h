#ifndef VECNA_H
#define VECNA_H
#include "Inimigo.h"
class Vecna : public Inimigo { //Declara a classe Vecna que herda de Inimigo.
public:
    explicit Vecna(const sf::Vector2f& posicao); //Declara o construtor explícito que aceita a posição inicial do chefe no mundo do jogo.
};
#endif
