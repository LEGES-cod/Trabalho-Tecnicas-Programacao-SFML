#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "Entidade.h"
#include "Jogador.h"

class Obstaculo : public Entidade {
protected:
    bool danoso;

public:
    Obstaculo(const sf::Vector2f& posicao, const sf::Vector2f& tamanho,
              const sf::Color& cor, bool ehDanoso = false);
    void executar() override;
    virtual void obstacular(Jogador* pJog) = 0;
    virtual bool podeColidir() const { return true; }
};

#endif
