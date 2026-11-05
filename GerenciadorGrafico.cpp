#include "GerenciadorGrafico.h"

GerenciadorGrafico::GerenciadorGrafico() //Construtor. cria uma janela com resolução de 800x600 pixels, com o título "Jogo - Hawkins" e limita a taxa de atualização a 60 fotogramas por segundo
    : janela(sf::VideoMode(800, 600), "Jogo - Hawkins") {
    janela.setFramerateLimit(60);
}
GerenciadorGrafico& GerenciadorGrafico::getInstancia() { //Declara uma variável estática local que é criada apenas na primeira chamada e retornada em todas as outras
    static GerenciadorGrafico instancia;
    return instancia;
}
sf::RenderWindow& GerenciadorGrafico::getJanela() { return janela; } //Retorna a referência da janela
bool GerenciadorGrafico::janelaAberta() const { return janela.isOpen(); } //Retorna o estado de abertura da janela
void GerenciadorGrafico::limpar() { janela.clear(sf::Color::White); } //Limpa a janela pintando o fundo de branco
void GerenciadorGrafico::mostrar() { janela.display(); } //Atualiza o ecrã mostrando o conteúdo renderizado
void GerenciadorGrafico::fechar() { janela.close(); } //Fecha a janela da aplicação
