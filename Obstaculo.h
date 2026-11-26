#ifndef OBSTACULO_H
#define OBSTACULO_H
#include "Entidade.h"
#include "Jogador.h"

class Obstaculo : public Entidade { // Declara a classe Obstaculo que herda de Entidade.
protected:
    bool danoso; // Indica se o obst�culo causa dano ao jogador

public:
    Obstaculo(const sf::Vector2f& posicao, const sf::Vector2f& tamanho, // Declara o construtor da classe recebendo posi��o, tamanho e cor.
              const sf::Color& cor, bool ehDanoso = false);
    void executar() override; // Declara a sobreposi��o do m�todo de execu��o l�gica.
    virtual void obstacular(Jogador* pJog) = 0; // M�todo virtual puro para tratar a intera��o com o jogador
    virtual bool podeColidir() const { return true; }
};
#endif
