#ifndef JOGADOR_H
#define JOGADOR_H
#include "Personagem.h"

class Jogador : public Personagem { //Declara a classe Jogador que herda de Personagem
private:
    float velocidadeY;
    bool noChao; //controlar o estado do pulo(pro jogador não voar)
    const float GRAVIDADE = 980.f; //gravidade
    const float FORCA_PULO = -450.f; // forca do pulo
    float tempoInvencivel; // tempo de proteçao apos o golpe

public:
    Jogador(); //Construtor padrão
    void executar(float deltaTime) override; //Sobrescreve o método de atualização lógica para processar os controles do utilizador
    void limitarNaTela(); //Impede que o jogador saia dos limites da janela do jogo
    void pular(); //executável do pulo
    void aterrar(float alturaY);
    float getVelocidadeY() const { return velocidadeY; }
    void receberDano(int dano);
};
#endif
