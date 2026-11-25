#ifndef JOGADOR_H
#define JOGADOR_H

#include "Personagem.h"
#include <SFML/Graphics.hpp>

class Jogador : public Personagem {
private:
    int idJogador;
    float velocidadeY;
    bool noChao;

    const float GRAVIDADE = 980.f;
    const float FORCA_PULO = -450.f;

    float tempoInvencivel;
    int pontos;

    float tempoDisparo;
    bool disparoSolicitado;
    float direcao;

    bool sangrando;
    float tempoDanoContinuo;
    float acumuladorCura;

    sf::Texture texturaPersonagem;
    sf::Sprite spritePersonagem;
    bool personagemCarregado;

public:
    Jogador(int id = 1);

    void executar() override;
    void desenhar() override;

    void limitarNaTela();
    void pular();
    void aterrar(float alturaY);
    void baterCabeca(float alturaY);

    bool consumirDisparo();
    void setPersonagem(int indice);

    bool estaVivo() const {
        return vidas > 0;
    }

    float getVelocidadeY() const {
        return velocidadeY;
    }

    void receberDano(int dano);
    void iniciarDanoContinuo();
    void atualizarDanoContinuo(float deltaTime);
    void curarGradualmente(float deltaTime);

    void adicionarPontos(int p);
    int getPontos() const;

    float getDirecao() const {
        return direcao;
    }
};

#endif
