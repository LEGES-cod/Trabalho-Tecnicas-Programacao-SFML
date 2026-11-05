#include "Inimigo.h"

Inimigo::Inimigo(const sf::Vector2f& posicao, const sf::Color& cor) //Construtor da classe. Defini a posição recebida, o tamanho fixo, a cor do inimigo, uma velocidade estática e 1 vida inicial
    : Personagem(posicao, sf::Vector2f(35.f, 35.f), cor, 0.f, 1) {}
void Inimigo::executar(float) { //Immplemeta a função de execução.
    // Os inimigos ficam parados nesta versão inicial do jogo.
}
