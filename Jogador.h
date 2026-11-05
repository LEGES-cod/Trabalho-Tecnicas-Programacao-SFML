#ifndef JOGADOR_H
#define JOGADOR_H
#include "Personagem.h"

class Jogador : public Personagem { //Declara a classe Jogador que herda de Personagem
public:
    Jogador(); //Construtor padrão
    void executar(float deltaTime) override; //Sobrescreve o método de atualização lógica para processar os controles do utilizador
    void limitarNaTela(); //Impede que o jogador saia dos limites da janela do jogo
};
#endif
