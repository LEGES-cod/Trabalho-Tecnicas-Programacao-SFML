#include "Jogador.h"
#include <iostream>
Jogador::Jogador() //COnstrutor que inicializa o jogador, chamando a classe base com posi��o inicial, tamanho, cor, velocidade de pix�is por segundo, 3 vidas iniciais
: Personagem(sf::Vector2f(80.f, 500.f), sf::Vector2f(35.f, 35.f),
                 sf::Color::Red, 250.f, 100),
      velocidadeY(0.f), noChao(true), tempoInvencivel(0.f) {} //Inicializa��o das vari�veis de pulo

void Jogador::pular() { //Executa o pulo se estiver no ch�o
    if (noChao) {
        velocidadeY = FORCA_PULO;
        noChao = false;
    }
}

void Jogador::executar(float deltaTime) { //Inicia o m�todo que processa os inputs do jogador a cada frame
    float dx = 0.f;

    if(tempoInvencivel > 0.f)
    {
        tempoInvencivel -= deltaTime;
    }

    //Deslocamento Horizontal
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        dx -= velocidade * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        dx += velocidade * deltaTime;
    }

    // Acionar Pulo (Tecla Espa�o ou Seta para Cima)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        pular();
    }

    // Aplica��o da Gravidade
    velocidadeY += GRAVIDADE * deltaTime;
    float dy = velocidadeY * deltaTime;


    mover(dx, dy);

    //Verifica��o de Colis�o com o Ch�o (Y = 500.f)
    sf::Vector2f p = getPosicao();
    if (p.y >= 500.f) {
        p.y = 500.f;
        velocidadeY = 0.f;
        noChao = true;
        setPosicao(p);
    }

    limitarNaTela(); //Chama a fun��o para restringir a posi��o do jogador dentro dos limites da tela
}

void Jogador::limitarNaTela() { //Inicia a fun��o de restri��o de ecr�
    sf::Vector2f p = getPosicao(); //Obt�m a posi��o atual do jogador
    if (p.x < 0.f) p.x = 0.f;  //Se o lado esquerdo ultrapassar o limite 0.f da janela, fixa-o em 0.f; se a largura total do jogador ultrapassar os 800.f pixels da largura da janela, prende a posi��o em 765.f
    if (p.x + 35.f > 800.f) p.x = 765.f;
    setPosicao(p); //Aplica a nova posi��o corrigida do jogador
}
void Jogador::aterrar(float alturaY)
{
    sf::Vector2f p = getPosicao();
    p.y = alturaY;
    setPosicao(p);
    velocidadeY = 0.f;
    noChao = true;
}
void Jogador::receberDano(int dano)
{
    if(tempoInvencivel <= 0.f)
    {
        vidas -= dano;//tira vida do personagem
        tempoInvencivel = 1.0f;//aumenta o tempo apos o ataque para que personagem n�o tome um monte de rit
        std::cout << "vidas atual: " <<getVidas() << std::endl;
    }
}
