#ifndef FASEHAWKINS_H
#define FASEHAWKINS_H
#include "Fase.h"
class FaseHawkins : public Fase { //Declara a fase Hawkins que herda de Fase
public:
    FaseHawkins(); //Construtor da fase Hawkins
    void carregar() override; //Sobrescreve o método virtual puro para povoar essa fase
};
#endif
