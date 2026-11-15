#ifndef JOGADOR_H
#define JOGADOR_H
#include "Personagem.h"

class Jogador : public Personagem { // Declara a classe Jogador que herda de Personagem
private:
    float velocidadeY;
    bool noChao;                     // Controlar o estado do pulo (pro jogador não voar)
    const float GRAVIDADE = 980.f;   // Gravidade
    const float FORCA_PULO = -450.f; // Força do pulo
    float tempoInvencivel;           // Tempo de proteção após o golpe
    int pontos;                      // Pontuação do jogador

public:
    Jogador();                       // Construtor padrão
    void executar() override;        // Sobrescreve o método de atualização lógica para processar os controles do utilizador
    void limitarNaTela();            // Impede que o jogador saia dos limites da janela do jogo
    void pular();                    // Executável do pulo
    void aterrar(float alturaY);
    float getVelocidadeY() const { return velocidadeY; }
    void receberDano(int dano);
    void adicionarPontos(int p);
    int getPontos() const;
};
#endif
