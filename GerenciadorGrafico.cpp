#include "GerenciadorGrafico.h"

GerenciadorGrafico::GerenciadorGrafico() // Construtor cria uma janela com resolu��o de 800x600 pixels, com o t�tulo "Jogo - Hawkins" e limita a taxa de atualiza��o a 60 fotogramas por segundo
    : janela(sf::VideoMode(800, 600), "Jogo - Hawkins"), deltaTime(0.f) {
    janela.setFramerateLimit(60);
}

GerenciadorGrafico* GerenciadorGrafico::getInstancia() { // Declara uma vari�vel est�tica local que � criada apenas na primeira chamada e retornada em todas as outras
    static GerenciadorGrafico instancia;
    return &instancia;
}

sf::RenderWindow& GerenciadorGrafico::getJanela() { return janela; } // Retorna a refer�ncia da janela
bool GerenciadorGrafico::janelaAberta() const { return janela.isOpen(); } // Retorna o estado de abertura da janela
void GerenciadorGrafico::limpar() { janela.clear(sf::Color::White); } // Limpa a janela pintando o fundo de branco
void GerenciadorGrafico::mostrar() { janela.display(); } // Atualiza o ecr� mostrando o conte�do renderizado
void GerenciadorGrafico::fechar() { janela.close(); } // Fecha a janela da aplica��o

void GerenciadorGrafico::desenharElemento(const sf::Drawable& drawable) { // Desenha um objeto SFML na janela
    janela.draw(drawable);
}

void GerenciadorGrafico::atualizarDeltaTime() { // Calcula o tempo decorrido desde o �ltimo frame
    deltaTime = relogio.restart().asSeconds();
    if (deltaTime > 0.05f) deltaTime = 0.05f;
}

float GerenciadorGrafico::getDeltaTime() const { // Retorna o deltaTime calculado
    return deltaTime;
}
