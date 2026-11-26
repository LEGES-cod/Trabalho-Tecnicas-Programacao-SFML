#ifndef FASEMUNDOINVERTIDO_H
#define FASEMUNDOINVERTIDO_H

#include "Fase.h"

class FaseMundoInvertido : public Fase {
protected:
    void criarDemodog();
    void criarVecna();
    void criarEspinhosTentaculo();

public:
    FaseMundoInvertido(bool carregando = false);
};

#endif
