#ifndef MENU_H
#define MENU_H
#include "Ente.h"

class Menu : public Ente { // Declara a classe Menu que herda de Ente conforme o UML
private:
    int opcaoSelecionada;
    bool ativo;
    sf::Texture texturaFundo;
    sf::Sprite fundoMenu;
    sf::RectangleShape botaoFase1;
    sf::RectangleShape botaoFase2;

    sf::Font fonte;
    sf::Text textoFase1;
    sf::Text textoFase2;

public:
    Menu();
    void executar() override;
    void desenhar() override;
    bool estaAtivo() const;
    int getOpcaoSelecionada() const;
    void reiniciar(int opcao = 1);
};
#endif

