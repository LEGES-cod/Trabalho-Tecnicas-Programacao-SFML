#ifndef FASE_H
#define FASE_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Ente.h"
#include "ListaEntidades.h"
#include "GerenciadorColisoes.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "Obstaculo.h"

class Fase : public Ente { // Fase herda publicamente de Ente conforme o diagrama UML
protected:
    ListaEntidades LEnts;         // Lista encadeada própria que gerencia todas as entidades da fase
    GerenciadorColisoes gColisoes;// Gerenciador de colisões da fase
    Jogador* pJog1;               // Ponteiro para o jogador principal da fase
    bool concluida;               // Variável que indica se a fase terminou (vitória ou derrota)

    sf::Texture texturaFundo;
    sf::Sprite spriteFundo;
    sf::RectangleShape chao;

    void adicionarInimigo(Inimigo* inimigo);     // Para inserir inimigos na lista e no gerenciador de colisões
    void adicionarObstaculo(Obstaculo* obstaculo); // Para inserir obstáculos na lista e no gerenciador de colisões
    virtual void criarInimigos() = 0;            // Método virtual puro para criar os inimigos específicos de cada fase
    virtual void criarObstaculos() = 0;          // Método virtual puro para criar os obstáculos específicos de cada fase

public:
    Fase(const std::string& caminhoFundo); // Declara o construtor da fase (recebe o caminho da imagem)
    virtual ~Fase();                       // Destrutor virtual
    void inicializar();                    // Inicializa o jogador e chama os métodos de criação da fase
    void executar() override;              // Responsável por atualizar a lógica da fase e colisões a cada frame
    void desenhar() override;              // Desenha o cenário e as entidades da fase
    bool terminou() const;                 // Retorna o estado atual da fase (se terminou ou não)
};
#endif
