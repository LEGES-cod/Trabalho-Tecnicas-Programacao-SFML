#include "Inimigo.h"

Inimigo::Inimigo(const sf::Vector2f& posicao, const sf::Color& cor) //Construtor da classe. Defini a posição recebida, o tamanho fixo, a cor do inimigo, uma velocidade estática e 1 vida inicial, dano inimigo facil
    : Personagem(posicao, sf::Vector2f(35.f, 35.f), cor, 0.f, 1),dano(3) {}
void Inimigo::executar(float deltaTime, const sf::Vector2f& posJogador) {

}
void Inimigo::executar(float deltaTime)
{

}
