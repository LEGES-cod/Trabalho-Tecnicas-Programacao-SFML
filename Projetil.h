#ifndef PROJETIL_H
#define PROJETIL_H
#include "Entidade.h"

class Projetil : public Entidade {
private:
    float velocidadeX;
    int dano;
    bool ativo;

public:
    Projetil(const sf::Vector2f& posicao, float velX,
             int danoProjetil = 5,
             const sf::Color& cor = sf::Color::Magenta);

    void executar() override;
    void desenhar() override;
    int getDano() const;
    bool getAtivo() const;
    void desativar();
};
#endif
