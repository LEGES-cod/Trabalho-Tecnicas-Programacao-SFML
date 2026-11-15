#ifndef PERSONAGEM_H
#define PERSONAGEM_H
#include "Entidade.h"

class Personagem : public Entidade { // Declara a classe Personagem que herda de Entidade.
protected:
    float velocidade;
    int vidas;
public:
    Personagem(const sf::Vector2f& posicao, const sf::Vector2f& tamanho, // Construtor para inicializar as propriedades comuns a todos os personagens.
               const sf::Color& cor, float velocidade, int vidas);
    int getVidas() const;               // Retorna o número atual de vidas do personagem.
    void perderVida();                  // Reduz a quantidade de vidas quando o personagem sofre dano.
    void mover(float dx, float dy);     // Desloca o personagem no espaço de acordo com as variações dx e dy.
};
#endif
