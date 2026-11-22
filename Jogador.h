#ifndef JOGADOR_H
#define JOGADOR_H
#include "Personagem.h"

class Jogador : public Personagem {
private:
    float velocidadeY;
    bool noChao;
    const float GRAVIDADE = 980.f;
    const float FORCA_PULO = -450.f;
    float tempoInvencivel;
    int pontos;

    float tempoDisparo;
    bool disparoSolicitado;
    float direcao;

public:
    Jogador();

    void executar() override;
    void limitarNaTela();
    void pular();
    void aterrar(float alturaY);

    bool consumirDisparo();

    float getVelocidadeY() const { return velocidadeY; }
    void receberDano(int dano);
    void adicionarPontos(int p);
    int getPontos() const;
    float getDirecao() const { return direcao; }
};
#endif
