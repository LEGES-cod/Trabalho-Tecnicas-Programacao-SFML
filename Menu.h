#ifndef MENU_H
#define MENU_H

#include "Ente.h"

class Menu : public Ente {
private:
    int opcaoSelecionada;
    bool ativo;

    // Controle das telas do menu
    bool selecionandoPersonagem;
    bool teclaAnterior;
    int personagemSelecionado;

    bool fundoCarregado;
    bool fonteCarregada;

    sf::Texture texturaFundo;
    sf::Sprite fundoMenu;

    sf::RectangleShape botaoHawkins;
    sf::RectangleShape botaoMundoInvertido;

    sf::Font fonte;
    sf::Text textoHawkins;
    sf::Text textoMundoInvertido;

    // Elementos da seleção de personagens
    sf::Texture texturasPersonagens[6];
    sf::Sprite spritesPersonagens[6];
    sf::RectangleShape cartoesPersonagens[6];
    sf::Text nomesPersonagens[6];

    bool imagensCarregadas[6];

    sf::Text tituloPersonagens;

    void atualizarDestaquePersonagem();

public:
    Menu();

    void executar() override;
    void desenhar() override;

    bool estaAtivo() const;
    bool estaSelecionandoPersonagem() const;

    int getOpcaoSelecionada() const;
    int getPersonagemSelecionado() const;

    void reiniciar(int opcao = 1);
};

#endif
