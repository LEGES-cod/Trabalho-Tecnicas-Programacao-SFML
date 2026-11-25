#ifndef FASE_H
#define FASE_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Ente.h"
#include "ListaEntidades.h"
#include "GerenciadorColisoes.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "Obstaculo.h"
#include "Chao.h"

class Fase : public Ente {
protected:
    ListaEntidades LEnts;
    GerenciadorColisoes gColisoes;
    Jogador* pJog1;
    Jogador* pJog2;
    bool doisJogadores;
    bool concluida;

    std::vector<Inimigo*> inimigos;
    std::vector<bool> inimigoPontuado;
    bool exigirDerrotaInimigos;

    sf::Color corChao;
    sf::Texture texturaFundo;
    sf::Sprite spriteFundo;

    sf::Font fonteHUD;
    sf::Text textoHUD;
    sf::Text textoHUD2;
    bool fonteHUDCarregada;

    void adicionarInimigo(Inimigo* inimigo);
    void adicionarObstaculo(Obstaculo* obstaculo);
    void adicionarChao(Chao* chao);
    void desenharHUD();
    Jogador* getJogadorMaisProximo(sf::Vector2f origem) const;

public:
    Fase(const std::string& caminhoFundo, const sf::Color& corChao);
    virtual ~Fase();
    void inicializar();
    void executar() override;
    void desenhar() override;
    bool terminou() const;
    bool jogadorMorreu() const;
    void setPersonagem(int indice);
    void ativarSegundoJogador(int indicePersonagem);

    int getPontosJogador() const;
    void setPontosJogador(int pontos);
};

#endif
