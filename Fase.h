#ifndef FASE_H
#define FASE_H
#include <memory>
#include <vector>
#include "Ente.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "Obstaculo.h"
#include "GerenciadorColisoes.h"

class Fase {
protected:
    std::vector<std::unique_ptr<Ente>> objetos; //Vetor que armazena a posse de todos os entes genéricos da fase.
    std::vector<Inimigo*> inimigos; //Vetor de ponteiros que aponta para inimigos criados.
    std::vector<Obstaculo*> obstaculos; //Vetor de ponteiros que referencia os obstáculos da fase
    std::unique_ptr<Jogador> jogador; //POnteiro que guarda o jogador pincipal da fase
    bool concluida; //Variável que indica se a fase terminou (vitória ou derrota)
    void adicionarInimigo(std::unique_ptr<Inimigo> inimigo); //Para inserir inimigos nas listas internas das fases
    void adicionarObstaculo(std::unique_ptr<Obstaculo> obstaculo); //Para inserir obstáculos nas listas internas das fases
public:
    Fase(); //Declara o construtor da fase
    virtual ~Fase() = default; //Destrutor virtual padrao
    virtual void carregar() = 0; //Método virtual puro que obriga as subclasses a implementarem a lógica de carregamento dos elementos específicos do nível.
    void executar(float deltaTime, sf::RenderWindow& janela); //Responsável por atualizar a lógica da fase e desenhar os elementos a cada frame
    bool terminou() const; //Retorna o estado atual da fase (se terminou ou não)
};
#endif
