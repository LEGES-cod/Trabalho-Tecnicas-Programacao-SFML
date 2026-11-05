#ifndef PLATAFORMAESTATICA_H
#define PLATAFORMAESTATICA_H
#include "Entidade.h"
class PlataformaEstatica : public Entidade { //Declara a classe PlataformaEstatica que herda de Entidade.
public:
    PlataformaEstatica(const sf::Vector2f& posicao, const sf::Vector2f& tamanho); //Declara o construtor da classe, recebendo a posição inicial e as dimensões (tamanho) da plataforma
    void executar(float deltaTime) override; //Declara a função virtual executar para atualizar a lógica da plataforma a cada frame.
};
#endif
