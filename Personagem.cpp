#include "Personagem.h"

Personagem::Personagem(const sf::Vector2f& posicao, const sf::Vector2f& tamanho, //Implementa o construtor: inicializa a parte gr�fica chamando o construtor de Entidade e atribui os valores locais de velocidade e vidas.
                       const sf::Color& cor, float velocidade, int vidas)
    : Entidade(posicao, tamanho, cor), velocidade(velocidade), vidas(vidas) {}


int Personagem::getVidas() const { return vidas; } //Retorna o valor atual da vari�vel vidas.
void Personagem::perderVida() { if (vidas > 0) --vidas; } //Decrementa o n�mero de vidas em uma unidade, desde que o personagem ainda tenha mais do que zero vidas.
void Personagem::mover(float dx, float dy) { corpo.move(dx, dy); } //Utiliza o m�todo nativo move do ret�ngulo da SFML (corpo) para alterar a posi��o espacial adicionando as varia��es dx e dy.
