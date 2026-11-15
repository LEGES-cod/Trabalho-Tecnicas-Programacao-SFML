#include "Entidade.h"

Entidade::Entidade(const sf::Vector2f& posicao, const sf::Vector2f& tamanho,
                   const sf::Color& cor) { // Implementa o construtor
    corpo.setPosition(posicao); // Define a posição inicial do retângulo
    corpo.setSize(tamanho);     // Define o tamanho
    corpo.setFillColor(cor);    // Define a cor
}

sf::FloatRect Entidade::getLimites() const { return corpo.getGlobalBounds(); } // Retorna as coordenadas e dimensões globais (para colisões)
sf::Vector2f Entidade::getPosicao() const { return corpo.getPosition(); } // Retorna a posição atual do corpo
void Entidade::setPosicao(const sf::Vector2f& posicao) { corpo.setPosition(posicao); } // Atualiza a posição
void Entidade::desenhar() { if (pGG) pGG->desenharElemento(corpo); } // Desenha o retângulo na janela através do GerenciadorGrafico
