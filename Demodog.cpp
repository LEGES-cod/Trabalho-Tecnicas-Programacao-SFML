#include "Demodog.h"
#include <cmath> // Para std::abs (calcular distância)

Demodog::Demodog(const sf::Vector2f& posicao, Jogador* pJogador) // Inicia o construtor da classe Demodog, aceitando a posição inicial
    : Inimigo(posicao, sf::Color(80, 40, 20), pJogador), // Chama o construtor da classe Inimigo, passando a posição e uma cor (RGB)
      limiteEsquerdo(posicao.x - 100.f), // Patrulha 100 pixels à esquerda
      limiteDireito(posicao.x + 100.f),  // Patrulha 100 pixels à direita
      indoDireita(true),
      raioVisao(180.f),                  // Distância que o demodog visualiza
      velocidadeAtaque(200.f) {}         // Velocidade do ataque

void Demodog::inverterDirecao() {
    indoDireita = !indoDireita;
}

void Demodog::executar() {
    float deltaTime = pGG ? pGG->getDeltaTime() : 0.016f;
    sf::Vector2f posAtual = getPosicao();
    sf::Vector2f posJogador = pJog ? pJog->getPosicao() : sf::Vector2f(-1000.f, -1000.f);
    float distanciax = posJogador.x - posAtual.x;

    if (pJog && std::abs(distanciax) <= raioVisao) { // Ataque/perseguição
        if (distanciax > 0.f) {
            mover(velocidadeAtaque * deltaTime * 0.6f, 0.f); // Corre pra direita
        } else {
            mover(-velocidadeAtaque * deltaTime * 0.6f, 0.f); // Corre pra esquerda
        }
    } else {
        float velPatrulhia = 80.f; // Vai e vem
        if (indoDireita) {
            mover(velPatrulhia * deltaTime, 0.f);
            if (getPosicao().x >= limiteDireito || getPosicao().x >= 765.f) {
                indoDireita = false;
            }
        } else {
            mover(-velPatrulhia * deltaTime, 0.f);
            if (getPosicao().x <= limiteEsquerdo || getPosicao().x <= 0.f) {
                indoDireita = true;
            }
        }
    }
}
