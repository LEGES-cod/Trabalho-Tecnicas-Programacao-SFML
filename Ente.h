#ifndef ENTE_H
#define ENTE_H
#include <SFML/Graphics.hpp>

class Ente {
public:
    virtual ~Ente() = default; //Destrutor virtual padrão
    virtual void executar(float deltaTime) = 0; //Virtual pura, atualiza a lógica do ente a cada frame, e recebe o tempo decorrido.
    virtual void desenhar(sf::RenderWindow& janela) = 0; //Função virtual pura que desenha o ente na janela do jogo.
};
#endif
