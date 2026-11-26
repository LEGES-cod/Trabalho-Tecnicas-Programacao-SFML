#ifndef JOGO_H
#define JOGO_H

#include <SFML/Graphics.hpp>
#include <string>
#include "GerenciadorGrafico.h"
#include "Menu.h"
#include "FaseHawkins.h"
#include "FaseMundoInvertido.h"

class Jogo {
private:
    GerenciadorGrafico* pGG;
    Menu menu;
    Fase* faseAtual;
    bool segundaFase;

    bool gameOver;
    int opcaoGameOver;

    bool pausado;
    int opcaoPausa;
    std::string mensagemPausa;

    bool vitoria;
    int opcaoVitoria;
    int pontuacaoFinal;

    bool teclaMenuAnterior;

    sf::Font fonteUI;
    sf::RectangleShape fundoSobreposicao;

    sf::Text textoTituloTela;
    sf::Text textoSubtituloTela;

    sf::RectangleShape botoesTela[4];
    sf::Text textosBotoesTela[4];

    void configurarBotao(int indice, const std::string& texto, float y);
    void desenharTelaOpcoes(const std::string& titulo, sf::Color corTitulo,
                            const std::string& subtitulo, int qtdBotoes, int opcaoAtual);
    void salvarJogo();
    bool carregarJogo();

public:
    Jogo();
    ~Jogo();
    void executar();
};

#endif
