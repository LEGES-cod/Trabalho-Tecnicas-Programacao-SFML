#ifndef ENTIDADE_H
#define ENTIDADE_H
#include "Ente.h"

class Entidade : public Ente { // Declara a classe Entidade que herda de Ente.
protected:
    sf::RectangleShape corpo;  // Declara um ret�ngulo da SFML
public:
    Entidade(const sf::Vector2f& posicao, const sf::Vector2f& tamanho,
             const sf::Color& cor); // Construtor que inicializa a entidade aceitando posi��o, tamanho e cor (RGB).
    virtual ~Entidade() = default;  // Destrutor virtual padr�o
    sf::FloatRect getLimites() const; // Retorna os limites espaciais globais do ret�ngulo (para detec��o de colis�es).
    sf::Vector2f getPosicao() const;  // Retorna a posi��o atual da entidade
    void setPosicao(const sf::Vector2f& posicao); // Altera a posi��o da Entidade
    void desenhar() override; // Sobrescreve o m�todo de desenho da classe Ente para desenhar o ret�ngulo via pGG
};
#endif

