#ifndef FASEMUNDOINVERTIDO_H
#define FASEMUNDOINVERTIDO_H
#include "Fase.h"

class FaseMundoInvertido : public Fase { // Declara a classe FaseMundoInvertido que herda de Fase
protected:
    void criarDemogorgon();        // Cria o Demogorgon do Mundo Invertido
    void criarVecna();             // Cria o Vecna do Mundo Invertido
    void criarEspinhosTentaculo(); // Cria os espinhos-tentáculo do Mundo Invertido

public:
    FaseMundoInvertido(); // Construtor da classe
};
#endif
