#ifndef BOLADEFOGO_H
#define BOLADEFOGO_H
#include "Entidade.h"

class BolaDeFogo : public Entidade {
private:
    float velocidadeX;
    int dano;
    bool ativo;

public:
    BolaDeFogo(const sf::Vector2f& posicao, float velX,
             int danoProjetil = 5,
             const sf::Color& cor = sf::Color::Magenta);

    void executar() override;
    void desenhar() override;
    int getDano() const;
    bool getAtivo() const;
    void desativar();
};
#endif
