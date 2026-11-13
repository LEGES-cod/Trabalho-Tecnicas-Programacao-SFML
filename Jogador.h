#ifndef JOGADOR_H
#define JOGADOR_H
#include "Personagem.h"

class Jogador : public Personagem { //Declara a classe Jogador que herda de Personagem
private:
    float velocidadeY;
    bool noChao; //controlar o estado do pulo(pro jogador n�o voar)
    const float GRAVIDADE = 980.f; //gravidade
    const float FORCA_PULO = -450.f; // forca do pulo
    float tempoInvencivel; // tempo de prote�ao apos o golpe

public:
    Jogador(); //Construtor padr�o
    void executar(float deltaTime) override; //Sobrescreve o m�todo de atualiza��o l�gica para processar os controles do utilizador
    void limitarNaTela(); //Impede que o jogador saia dos limites da janela do jogo
    void pular(); //execut�vel do pulo
    void aterrar(float alturaY);
    float getVelocidadeY() const { return velocidadeY; }
    void receberDano(int dano);
};
#endif
