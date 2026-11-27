#ifndef BOLADEFOGO_H
#define BOLADEFOGO_H

#include "Entidade.h"

class BolaDeFogo : public Entidade {
private:
    sf::Vector2f velocidade;
    int dano;
    bool ativo;

public:
    BolaDeFogo(const sf::Vector2f& posicao, float velX,
               int danoProjetil = 5,
               const sf::Color& cor = sf::Color::Magenta,
               float velY = 0.f);

    void executar() override;
    void desenhar() override;
    int getDano() const;
    bool getAtivo() const;
    void desativar();
};

#endif
