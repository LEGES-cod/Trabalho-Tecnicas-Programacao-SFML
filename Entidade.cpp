#include "Entidade.h"

Entidade::Entidade(const sf::Vector2f& posicao, const sf::Vector2f& tamanho,
                   const sf::Color& cor) { // Implementa o construtor
    corpo.setPosition(posicao); // Define a posi��o inicial do ret�ngulo
    corpo.setSize(tamanho);     // Define o tamanho
    corpo.setFillColor(cor);    // Define a cor
}

sf::FloatRect Entidade::getLimites() const { return corpo.getGlobalBounds(); } // Retorna as coordenadas e dimens�es globais (para colis�es)
sf::Vector2f Entidade::getPosicao() const { return corpo.getPosition(); } // Retorna a posi��o atual do corpo
void Entidade::setPosicao(const sf::Vector2f& posicao) { corpo.setPosition(posicao); } // Atualiza a posi��o
void Entidade::desenhar() { if (pGG) pGG->desenharElemento(corpo); } // Desenha o ret�ngulo na janela atrav�s do GerenciadorGrafico
