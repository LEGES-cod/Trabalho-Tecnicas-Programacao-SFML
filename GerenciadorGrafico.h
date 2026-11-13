#ifndef GERENCIADORGRAFICO_H
#define GERENCIADORGRAFICO_H
#include <SFML/Graphics.hpp>

class GerenciadorGrafico {
private:
    sf::RenderWindow janela; //refere-se ao objeto concreto criado em memória a partir da classe sf::RenderWindow.
    GerenciadorGrafico(); //Construtor declarado na seção privada para impedir que inst^]ancias externas criem objetos novos
public:
    static GerenciadorGrafico& getInstancia(); //Fornece o ponto de acesso global a uma única instância do gestor gráfico
    sf::RenderWindow& getJanela(); //Retorna a referência para a janela gráfica
    bool janelaAberta() const; //Verifica se a janela está aberta
    void limpar(); //Limpa o conteúdo da janela (preenche com cor de fundo a cada frame)
    void mostrar(); //Apresenta no ecrã tudo que foi renderizado no frame atual
    void fechar(); //Fecha a janela gráfica
};
#endif
