#ifndef DEMODOG_H
#define DEMODOG_H

#include "Inimigo.h"
class Jogador;

class Demodog : public Inimigo {
private:
    float limiteEsquerdo;
    float limiteDireito;
    bool indoDireita;
    float raioVisao;
    float velocidadeAtaque;

    sf::Texture textura;
    sf::Sprite sprite;

public:
    explicit Demodog(const sf::Vector2f& posicao, Jogador* pJogador = nullptr);

    void executar() override;
    void desenhar() override;
    void inverterDirecao() override;
};

#endif
