#ifndef FASEHAWKINS_H
#define FASEHAWKINS_H
#include "Fase.h"

class FaseHawkins : public Fase { // Declara a fase Hawkins que herda de Fase
protected:
    void criarDemodog();       // Cria o Demodog da fase Hawkins
    void criarTroncosCaidos(); // Cria os troncos caídos da fase Hawkins

public:
    FaseHawkins(); // Construtor da fase Hawkins
};
#endif
