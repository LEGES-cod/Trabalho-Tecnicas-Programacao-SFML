#ifndef ENTE_H
#define ENTE_H
#include "GerenciadorGrafico.h"

class Ente {
protected:
    int id;                            // Identificador único do ente
    static int contId;                 // Contador estático para gerar IDs
    static GerenciadorGrafico* pGG;    // Ponteiro estático para o gerenciador gráfico

public:
    Ente();                            // Construtor padrão
    virtual ~Ente() = default;         // Destrutor virtual padrão
    virtual void executar() = 0;       // Virtual pura, atualiza a lógica do ente a cada frame
    virtual void desenhar() = 0;       // Função virtual pura que desenha o ente na janela do jogo

    int getId() const;
    static void setGG(GerenciadorGrafico* pG); // Define o gerenciador gráfico compartilhado
};
#endif
