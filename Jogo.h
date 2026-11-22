#ifndef JOGO_H
#define JOGO_H

#include <SFML/Graphics.hpp>
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

    sf::Font fonteGameOver;
    sf::Text textoGameOver;
    sf::Text textoTentarNovamente;
    sf::Text textoSair;

    sf::RectangleShape fundoGameOver;
    sf::RectangleShape botaoTentarNovamente;
    sf::RectangleShape botaoSair;

public:
    Jogo();
    ~Jogo();
    void executar();
};

#endif
