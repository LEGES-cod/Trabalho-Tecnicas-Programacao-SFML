#ifndef JOGO_H
#define JOGO_H

#include "GerenciadorGrafico.h"
#include "Menu.h"
#include "FaseHawkins.h"
#include "FaseMundoInvertido.h"

class Jogo { // Classe principal que gerencia o ciclo de vida e estados do jogo conforme o UML
private:
    GerenciadorGrafico* pGG;
    Menu menu;
    Fase* faseAtual;
    bool segundaFase;

public:
    Jogo();
    ~Jogo();
    void executar();
};
#endif
