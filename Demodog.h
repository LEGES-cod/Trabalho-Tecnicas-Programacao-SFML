#ifndef DEMODOG_H
#define DEMODOG_H
#include "Inimigo.h"
class Demodog : public Inimigo { //declara a classe que herda da classe Inimigo
private:
    float limiteEsquerdo;
    float limiteDireito;
    bool indoDireita;
    float raioVisao;
    float velocidadeAtaque;
public:
    explicit Demodog(const sf::Vector2f& posicao); //Declara o construtor de classe que recebe uma posição bidimensional por referÊncia constante
    void executar(float deltaTime, const sf::Vector2f& posJogador) override;
    virtual void inverterDirecao()override;
};
#endif
