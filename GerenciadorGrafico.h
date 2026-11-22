#ifndef GERENCIADORGRAFICO_H
#define GERENCIADORGRAFICO_H
#include <SFML/Graphics.hpp>

class GerenciadorGrafico {
private:
    sf::RenderWindow janela; // Refere-se ao objeto concreto criado em mem�ria a partir da classe sf::RenderWindow.
    sf::Clock relogio;       // Rel�gio interno para calcular o tempo entre frames
    float deltaTime;         // Tempo decorrido no frame atual

    GerenciadorGrafico();    // Construtor declarado na se��o privada para impedir que inst�ncias externas criem objetos novos
public:
    static GerenciadorGrafico* getInstancia(); // Fornece o ponto de acesso global a uma �nica inst�ncia do gestor gr�fico
    sf::RenderWindow& getJanela();             // Retorna a refer�ncia para a janela gr�fica
    bool janelaAberta() const;                 // Verifica se a janela est� aberta
    void limpar();                             // Limpa o conte�do da janela (preenche com cor de fundo a cada frame)
    void mostrar();                            // Apresenta no ecr� tudo que foi renderizado no frame atual
    void fechar();                             // Fecha a janela gr�fica

    void desenharElemento(const sf::Drawable& drawable); // Desenha qualquer elemento gr�fico da SFML
    void atualizarDeltaTime();                           // Atualiza o deltaTime a cada frame
    float getDeltaTime() const;                          // Retorna o deltaTime atual
};
#endif
