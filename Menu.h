#ifndef MENU_H
#define MENU_H

#include "Ente.h"
#include <string>
#include <utility>
#include <vector>

class Menu : public Ente {
private:
    int opcaoSelecionada;
    bool ativo;
    bool sairSolicitado;
    bool carregarSolicitado;

    bool selecionandoModo;
    bool doisJogadores;
    bool selecionandoPersonagem;
    bool vendoRanking;
    bool teclaAnterior;
    int personagemSelecionado;

    bool fundoCarregado;
    bool fonteCarregada;

    sf::Texture texturaFundo;
    sf::Sprite fundoMenu;
    sf::Font fonte;

    sf::RectangleShape botoesPrincipais[5];
    sf::Text textosPrincipais[5];

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
    std::vector<std::pair<int, std::string>> registrosRanking;
    size_t offsetRanking;

    void atualizarDestaquePrincipal();
    void atualizarDestaqueModo();
    void atualizarDestaquePersonagem();
    void carregarRanking();
    void atualizarTextoRanking();

public:
    Menu();

    void executar() override;
    void desenhar() override;

    bool estaAtivo() const;
    bool querSair() const;
    bool querCarregar() const;
    bool isDoisJogadores() const;
    bool estaSelecionandoPersonagem() const;

    int getOpcaoSelecionada() const;
    int getPersonagemSelecionado() const;

    void reiniciar(int opcao = 1);
    void desativar() { ativo = false; carregarSolicitado = false; }
    static void salvarPontuacao(const std::string& nomeJogador, int pontos);
};

#endif
