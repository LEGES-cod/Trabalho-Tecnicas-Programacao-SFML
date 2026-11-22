#include "EspinhosTentaculo.h"

EspinhosTentaculo::EspinhosTentaculo(const sf::Vector2f& posicao) // Inicia a implementação do construtor
    : Obstaculo(posicao, sf::Vector2f(70.f, 30.f), sf::Color(30, 120, 50), true), // Verde escuro
      danoEspinhos(5) {} // Construção para a classe Obstaculo passando a posição recebida, o tamanho fixo e a cor.

void EspinhosTentaculo::obstacular(Jogador* pJog) { // Causa dano ao jogador ao encostar nos espinhos
    if (pJog) {
        pJog->receberDano(danoEspinhos);
    }
}
