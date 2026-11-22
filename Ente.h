#ifndef ENTE_H
#define ENTE_H
#include "GerenciadorGrafico.h"

class Ente {
protected:
    int id;                            // Identificador �nico do ente
    static int contId;                 // Contador est�tico para gerar IDs
    static GerenciadorGrafico* pGG;    // Ponteiro est�tico para o gerenciador gr�fico

public:
    Ente();                            // Construtor padr�o
    virtual ~Ente() = default;         // Destrutor virtual padr�o
    virtual void executar() = 0;       // Virtual pura, atualiza a l�gica do ente a cada frame
    virtual void desenhar() = 0;       // Fun��o virtual pura que desenha o ente na janela do jogo

    int getId() const;
    static void setGG(GerenciadorGrafico* pG); // Define o gerenciador gr�fico compartilhado
};
#endif
