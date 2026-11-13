#include "Demodog.h"
#include <cmath> // Para std::abs(calcular distancia)
Demodog::Demodog(const sf::Vector2f& posicao) //Inicia o construtor da classe Demodog, aceitando a posição inicial
    : Inimigo(posicao, sf::Color(80, 40, 20)),//Marrom escuro //Chama o construtor da classe Inimigo, passando a posição e um cor (RGB)
      limiteEsquerdo(posicao.x - 100.f),//Patrulha 100 pixel a esquerda
      limiteDireito(posicao.x + 100.f),//Patrulha 100 pixel a direita
      indoDireita(true),
      raioVisao(180.f), // distancia que o demodog visualiza
      velocidadeAtaque(200.f){}// velocidade do ataque


    void Demodog::inverterDirecao()
    {
        indoDireita = !indoDireita;
    }


     void Demodog::executar(float deltaTime, const sf::Vector2f& posJogador)
     {
         sf::Vector2f posAtual = getPosicao();
         float distanciax = posJogador.x - posAtual.x;


         if(std::abs(distanciax)<= raioVisao)//ataque/perseguição
         {
             if(distanciax > 0.f)
             {
                 mover(velocidadeAtaque * deltaTime * 0.6f, 0.f);//corre pra direita
             }
             else{
                mover(-velocidadeAtaque * deltaTime * 0.6f, 0.f);//corre pra esquerda
             }
         }
         else{
            float velPatrulhia = 80.f;//vai e vem
            if(indoDireita)
            {
                mover(velPatrulhia * deltaTime, 0.f);
                if(getPosicao().x >= limiteDireito || getPosicao().x >= 765.f)
                {
                    indoDireita = false;
                }
            }
            else{
                mover(-velPatrulhia * deltaTime, 0.f);
                if(getPosicao().x <= limiteEsquerdo || getPosicao().x <= 0.f)
                {
                    indoDireita = true;
                }
            }
         }
     }
