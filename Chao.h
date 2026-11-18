#ifndef CHAO_H
#define CHAO_H
#include "Entidade.h"
#include "Jogador.h"

class Chao : public Entidade {
public:
    Chao(const sf::Vector2f& posicao, const sf::Vector2f& tamanho,
         const sf::Color& cor);
    void executar() override;
    void colidir(Jogador* pJog);
};
#endif
