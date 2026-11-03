#ifndef ENTIDADE_H
#define ENTIDADE_H

#include "Ente.h"

class Entidade : public Ente {
protected:
    float x;
    float y;

public:
    Entidade();
    virtual ~Entidade();

    virtual void executar() = 0;
    virtual void salvar();
};

#endif
