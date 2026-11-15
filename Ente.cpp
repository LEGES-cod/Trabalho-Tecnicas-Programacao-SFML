#include "Ente.h"

int Ente::contId = 0;
GerenciadorGrafico* Ente::pGG = GerenciadorGrafico::getInstancia();

Ente::Ente() : id(++contId) {} // Inicializa o ID único do ente

int Ente::getId() const { return id; }

void Ente::setGG(GerenciadorGrafico* pG) { pGG = pG; }
