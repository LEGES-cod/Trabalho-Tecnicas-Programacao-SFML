#ifndef PLATAFORMAESTATICA_H
#define PLATAFORMAESTATICA_H

#include "Obstaculo.h"

class PlataformaEstatica : public Obstaculo {
private:
    float largura;
    float altura;
    float tempoPerigo;

public:
    PlataformaEstatica(const sf::Vector2f& posicao, const sf::Vector2f& tamanho);
    ~PlataformaEstatica() override = default;

    void executar() override;
    void obstacular(Jogador* pJog) override;

    float getLargura() const { return largura; }
    float getAltura() const { return altura; }
};

#endif
