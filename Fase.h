
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
    bool concluida;

    std::vector<Inimigo*> inimigos;
    bool exigirDerrotaInimigos;

    sf::Color corChao;
    sf::Texture texturaFundo;
    sf::Sprite spriteFundo;


    void adicionarInimigo(Inimigo* inimigo);
    void adicionarObstaculo(Obstaculo* obstaculo);
    void adicionarChao(Chao* chao);

public:
    Fase(const std::string& caminhoFundo, const sf::Color& corChao);
    virtual ~Fase();
    void inicializar();
    void executar() override;
    void desenhar() override;
    bool terminou() const;
    bool jogadorMorreu() const;
};
#endif
