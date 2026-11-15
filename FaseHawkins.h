#ifndef FASEHAWKINS_H
#define FASEHAWKINS_H
#include "Fase.h"

class FaseHawkins : public Fase { // Declara a fase Hawkins que herda de Fase
protected:
    void criarInimigos() override;   // Cria os inimigos específicos de Hawkins
    void criarObstaculos() override; // Cria os obstáculos específicos de Hawkins

public:
    FaseHawkins(); // Construtor da fase Hawkins
};
#endif
