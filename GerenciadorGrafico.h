#ifndef GERENCIADORGRAFICO_H
#define GERENCIADORGRAFICO_H
#include <SFML/Graphics.hpp>

class GerenciadorGrafico {
private:
    sf::RenderWindow janela; // Refere-se ao objeto concreto criado em memória a partir da classe sf::RenderWindow.
    sf::Clock relogio;       // Relógio interno para calcular o tempo entre frames
    float deltaTime;         // Tempo decorrido no frame atual

    GerenciadorGrafico();    // Construtor declarado na seção privada para impedir que instâncias externas criem objetos novos
public:
    static GerenciadorGrafico* getInstancia(); // Fornece o ponto de acesso global a uma única instância do gestor gráfico
    sf::RenderWindow& getJanela();             // Retorna a referência para a janela gráfica
    bool janelaAberta() const;                 // Verifica se a janela está aberta
    void limpar();                             // Limpa o conteúdo da janela (preenche com cor de fundo a cada frame)
    void mostrar();                            // Apresenta no ecrã tudo que foi renderizado no frame atual
    void fechar();                             // Fecha a janela gráfica

    void desenharElemento(const sf::Drawable& drawable); // Desenha qualquer elemento gráfico da SFML
    void atualizarDeltaTime();                           // Atualiza o deltaTime a cada frame
    float getDeltaTime() const;                          // Retorna o deltaTime atual
};
#endif
