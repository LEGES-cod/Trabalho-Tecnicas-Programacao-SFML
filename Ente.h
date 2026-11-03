#ifndef ENTE_H
#define ENTE_H

class GerenciadorGrafico;
class Ente{
protected:
    int id;
    static GerenciadorGrafico* pGG;
public:

    Ente();
    virtual ~Ente();
    virtual void Executar() = 0;
    virtual void desenhar() = 0;
    static void setGerenciadorGrafico(GerenciadorGrafico* pGrafico);
};
#endif
