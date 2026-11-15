#ifndef FASEMUNDOINVERTIDO_H
#define FASEMUNDOINVERTIDO_H
#include "Fase.h"

class FaseMundoInvertido : public Fase { // Declara a classe FaseMundoInvertido que herda de Fase
protected:
    void criarInimigos() override;   // Cria os inimigos específicos do Mundo Invertido
    void criarObstaculos() override; // Cria os obstáculos específicos do Mundo Invertido

public:
    FaseMundoInvertido(); // Construtor da classe
};
#endif
