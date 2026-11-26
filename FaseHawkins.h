#ifndef FASEHAWKINS_H
#define FASEHAWKINS_H
#include "Fase.h"

class FaseHawkins : public Fase {
protected:
    void criarDemodog();
    void criarTroncosCaidos();

public:
    FaseHawkins(bool carregando = false);
};
#endif
