#include "PlataformaEstatica.h"
PlataformaEstatica::PlataformaEstatica(const sf::Vector2f& posicao, //Implementa o construtor da classe passando a posição e o tamanho recebidos, e definindo uma cpr.
                                       const sf::Vector2f& tamanho)
    : Entidade(posicao, tamanho, sf::Color(100, 100, 100)) {}
void PlataformaEstatica::executar(float) {} //Implementa o método executar de forma vazia, uma vez que as plataformas estáticas não necessitam de atualizar nenhuma lógica ou movimento ao longo do tempo.
