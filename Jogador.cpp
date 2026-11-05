#include "Jogador.h"

Jogador::Jogador() //COnstrutor que inicializa o jogador, chamando a classe base com posição inicial, tamanho, cor, velocidade de pixéis por segundo, 3 vidas iniciais
    : Personagem(sf::Vector2f(80.f, 500.f), sf::Vector2f(35.f, 35.f),
                 sf::Color::Red, 250.f, 3) {}
void Jogador::executar(float deltaTime) { //Inicia o método que processa os inputs do jogador a cada frame
    float deslocamento = velocidade * deltaTime; //Calcula o deslocamento proporcional ao tempo decorrido
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || //Verifica se a seta para a esquerda ou a tecla A está apertadada. Se sim, desloca o jogador para a esquerda.
        sf::Keyboard::isKeyPressed(sf::Keyboard::A)) mover(-deslocamento, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || //Verifica se a seta para a direita ou a tecla D está apertadada. Se sim, desloca o jogador para a direita.
        sf::Keyboard::isKeyPressed(sf::Keyboard::D)) mover(deslocamento, 0.f);
    limitarNaTela(); //Chama a função para restringir a posição do jogadors dentro dos limites da tela
}
void Jogador::limitarNaTela() { //Inicia a função de restrição de ecrã
    sf::Vector2f p = getPosicao(); //Obtém a posição atual do jogador
    if (p.x < 0.f) p.x = 0.f;  //Se o lado esquerdo ultrapassar o limite 0.f da janela, fixa-o em 0.f; se a largura total do jogador ultrapassar os 800.f pixels da largura da janela, prende a posição em 765.f
    if (p.x + 35.f > 800.f) p.x = 765.f;
    setPosicao(p); //Aplica a nova posição corrigida do jogador
}
