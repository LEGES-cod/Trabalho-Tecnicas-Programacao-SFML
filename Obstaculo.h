#ifndef OBSTACULO_H
#define OBSTACULO_H
#include "Entidade.h"
#include "Jogador.h"

class Obstaculo : public Entidade { // Declara a classe Obstaculo que herda de Entidade.
protected:
    bool danoso; // Indica se o obstáculo causa dano ao jogador

public:
    Obstaculo(const sf::Vector2f& posicao, const sf::Vector2f& tamanho, // Declara o construtor da classe recebendo posição, tamanho e cor.
              const sf::Color& cor, bool ehDanoso = false);
    void executar() override; // Declara a sobreposição do método de execução lógica.
    virtual void obstacular(Jogador* pJog) = 0; // Método virtual puro para tratar a interação com o jogador
};
#endif
