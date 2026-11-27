#ifndef ENTIDADE_H
#define ENTIDADE_H
#include "Ente.h"

class Entidade : public Ente {
protected:
    sf::RectangleShape corpo;
    float velocidadeY;
    const float GRAVIDADE = 980.f;

public:
    Entidade(const sf::Vector2f& posicao, const sf::Vector2f& tamanho,
             const sf::Color& cor);
    virtual ~Entidade() = default;

    sf::FloatRect getLimites() const;
    sf::Vector2f getPosicao() const;
    void setPosicao(const sf::Vector2f& posicao);
    virtual void aplicarGravidade(float deltaTime, float fator = 1.f);
    void desenhar() override;
};

#endif
