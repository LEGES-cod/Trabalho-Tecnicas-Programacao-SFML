
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

class Fase : public Ente {
protected:
    ListaEntidades LEnts;
    GerenciadorColisoes gColisoes;
    Jogador* pJog1;
    bool concluida;

    std::vector<Inimigo*> inimigos;
    bool exigirDerrotaInimigos;

    sf::Texture texturaFundo;
    sf::Sprite spriteFundo;
    sf::RectangleShape chao;

    void adicionarInimigo(Inimigo* inimigo);
    void adicionarObstaculo(Obstaculo* obstaculo);
    virtual void criarInimigos() = 0;
    virtual void criarObstaculos() = 0;

public:
    Fase(const std::string& caminhoFundo);
    virtual ~Fase();
    void inicializar();
    void executar() override;
    void desenhar() override;
    bool terminou() const;
    bool jogadorMorreu() const;
};
#endif
