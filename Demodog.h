#ifndef DEMODOG_H
#define DEMODOG_H
#include "Inimigo.h"

class Demodog : public Inimigo { // Declara a classe que herda da classe Inimigo
private:
    float limiteEsquerdo;
    float limiteDireito;
    bool indoDireita;
    float raioVisao;
    float velocidadeAtaque;

public:
    explicit Demodog(const sf::Vector2f& posicao, Jogador* pJogador = nullptr); // Declara o construtor de classe que recebe uma posição bidimensional por referência constante
    void executar() override;
    void inverterDirecao() override;
};
#endif
