#ifndef MENU_H
#define MENU_H
#include "Ente.h"

class Menu : public Ente { // Declara a classe Menu que herda de Ente conforme o UML
private:
    int opcaoSelecionada;
    bool ativo;
    sf::RectangleShape fundoMenu;
    sf::RectangleShape botaoFase1;
    sf::RectangleShape botaoFase2;

public:
    Menu();
    void executar() override;
    void desenhar() override;
    bool estaAtivo() const;
    int getOpcaoSelecionada() const;
};
#endif
