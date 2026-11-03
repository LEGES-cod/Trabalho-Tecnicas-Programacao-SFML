#include "Ente.h"

GerenciadorGrafico* Ente::pGG = nullptr;

Ente::Ente(){
    id = 0;
}
Ente::~Ente(){
}

void Ente::setGerenciadorGrafico(GerenciadorGrafico* pGrafico)
{
    pGG = pGrafico;
}

