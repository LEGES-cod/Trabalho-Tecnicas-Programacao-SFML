#ifndef FASEMUNDOINVERTIDO_H
#define FASEMUNDOINVERTIDO_H
#include "Fase.h"
class FaseMundoInvertido : public Fase { //Declara a classe FaseMundoInvertido que herda de Fase
public:
    FaseMundoInvertido(); //Construtor da classe
    void carregar() override; //Sobrescre o método de carregamento da fase
};
#endif
