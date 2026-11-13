#ifndef OBSTACULO_H
#define OBSTACULO_H
#include "Entidade.h"
class Obstaculo : public Entidade { //Declara a classe Obstaculo que herda de Entidade.
public:
    Obstaculo(const sf::Vector2f& posicao, const sf::Vector2f& tamanho, //Declara o construtor da classe recebendo posição, tamanho e cor.
              const sf::Color& cor);
    void executar(float deltaTime) override; //Declara a sobreposição do método de execução lógica.
};
#endif
