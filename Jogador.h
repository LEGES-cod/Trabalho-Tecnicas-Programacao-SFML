#ifndef JOGADOR_H
#define JOGADOR_H

#include "Personagem.h"
#include <SFML/Graphics.hpp>

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

    bool sangrando;
    float tempoDanoContinuo;
    float acumuladorCura;

    // Imagem do personagem selecionado.
    sf::Texture texturaPersonagem;
    sf::Sprite spritePersonagem;
    bool personagemCarregado;

public:
    Jogador();

    void executar() override;
    void desenhar() override;

    void limitarNaTela();
    void pular();
    void aterrar(float alturaY);
    void baterCabeca(float alturaY);

    bool consumirDisparo();

    // Escolhe a aparência do jogador.
    void setPersonagem(int indice);

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
