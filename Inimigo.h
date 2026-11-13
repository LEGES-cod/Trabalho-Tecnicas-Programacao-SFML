#ifndef INIMIGO_H
#define INIMIGO_H
#include "Personagem.h"

class Inimigo : public Personagem {//Declara a classe Inimigo que herda de Personagem
protected:
    int dano;//variavel para o dano de demodog

public:
    Inimigo(const sf::Vector2f& posicao, const sf::Color& cor); //Declara o construtor da classe, que recebe a posi��o inicial e a cor do inimigo
    virtual void executar(float deltaTime, const sf::Vector2f& posJogador);
    void executar(float deltaTime) override; //Declara a fun��o virtual executar para atualizar a l�gica do inimigo a cada frame com base no tempo decorrido
    virtual void inverterDirecao(){};
    int getDano()const{return dano;}

};
#endif
