#ifndef PROJETIL_H
#define PROJETIL_H
#include "Entidade.h"

class Projetil : public Entidade { // Declara a classe Projetil que herda de Entidade conforme o UML
private:
    float velocidadeX;
    int dano;
    bool ativo;

public:
    Projetil(const sf::Vector2f& posicao, float velX, int danoProjetil = 5);
    void executar() override;
    int getDano() const;
    bool getAtivo() const;
    void desativar();
};
#endif
