#ifndef MENU_H
#define MENU_H

#include "Ente.h"
#include <string>
#include <vector>

class Menu : public Ente {
private:
    int opcaoSelecionada; // 1 = Hawkins, 2 = Mundo Invertido, 3 = Ranking, 4 = Sair
    bool ativo;
    bool sairSolicitado;

    bool selecionandoModo;
    bool doisJogadores;
    bool selecionandoPersonagem;
    bool vendoRanking;
    bool teclaAnterior;
    int personagemSelecionado; // 0 = Mike, 1 = Eleven

    bool fundoCarregado;
    bool fonteCarregada;

    sf::Texture texturaFundo;
    sf::Sprite fundoMenu;
    sf::Font fonte;

    sf::RectangleShape botoesPrincipais[4];
    sf::Text textosPrincipais[4];

    // Selecao de 1 ou 2 jogadores
    sf::RectangleShape botoesModo[2];
    sf::Text textosModo[2];
    sf::Text tituloModo;

    sf::Texture texturasPersonagens[2];
    sf::Sprite spritesPersonagens[2];
    sf::RectangleShape cartoesPersonagens[2];
    sf::Text nomesPersonagens[2];
    bool imagensCarregadas[2];

    sf::Text tituloPersonagens;
    sf::Text subtituloPersonagens;
    sf::Text textoVoltar;

    sf::RectangleShape painelRanking;
    sf::Text tituloRanking;
    sf::Text textoLinhasRanking;

    void atualizarDestaquePrincipal();
    void atualizarDestaqueModo();
    void atualizarDestaquePersonagem();
    void carregarRanking();

public:
    Menu();

    void executar() override;
    void desenhar() override;

    bool estaAtivo() const;
    bool querSair() const;
    bool isDoisJogadores() const;
    bool estaSelecionandoPersonagem() const;

    int getOpcaoSelecionada() const;
    int getPersonagemSelecionado() const;

    void reiniciar(int opcao = 1);
    static void salvarPontuacao(int indicePersonagem, int pontos, bool coop = false);
};

#endif
