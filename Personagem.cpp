#include "Personagem.h"

Personagem::Personagem(const sf::Vector2f& posicao, const sf::Vector2f& tamanho, //Implementa o construtor: inicializa a parte gráfica chamando o construtor de Entidade e atribui os valores locais de velocidade e vidas.
                       const sf::Color& cor, float velocidade, int vidas)
    : Entidade(posicao, tamanho, cor), velocidade(velocidade), vidas(vidas) {}


int Personagem::getVidas() const { return vidas; } //Retorna o valor atual da variável vidas.
void Personagem::perderVida() { if (vidas > 0) --vidas; } //Decrementa o número de vidas em uma unidade, desde que o personagem ainda tenha mais do que zero vidas.
void Personagem::mover(float dx, float dy) { corpo.move(dx, dy); } //Utiliza o método nativo move do retângulo da SFML (corpo) para alterar a posição espacial adicionando as variações dx e dy.
