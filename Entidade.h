#ifndef ENTIDADE_H
#define ENTIDADE_H
#include "Ente.h"

class Entidade : public Ente { // Declara a classe Entidade que herda de Ente.
protected:
    sf::RectangleShape corpo;  // Declara um retângulo da SFML
public:
    Entidade(const sf::Vector2f& posicao, const sf::Vector2f& tamanho,
             const sf::Color& cor); // Construtor que inicializa a entidade aceitando posição, tamanho e cor (RGB).
    virtual ~Entidade() = default;  // Destrutor virtual padrão
    sf::FloatRect getLimites() const; // Retorna os limites espaciais globais do retângulo (para detecção de colisões).
    sf::Vector2f getPosicao() const;  // Retorna a posição atual da entidade
    void setPosicao(const sf::Vector2f& posicao); // Altera a posição da Entidade
    void desenhar() override; // Sobrescreve o método de desenho da classe Ente para desenhar o retângulo via pGG
};
#endif
