#ifndef PERSONAGEM_H
#define PERSONAGEM_H
#include "Entidade.h"

class Personagem : public Entidade {
protected:
    float velocidade;
    int vidas;
public:
    Personagem(const sf::Vector2f& posicao, const sf::Vector2f& tamanho,
               const sf::Color& cor, float velocidade, int vidas);
    int getVidas() const;
    void setVidas(int v) { vidas = v; }
    void perderVida();
    void mover(float dx, float dy);
};
#endif
