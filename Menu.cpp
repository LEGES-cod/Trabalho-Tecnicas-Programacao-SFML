#include "Menu.h"

Menu::Menu() : Ente(), opcaoSelecionada(1), ativo(true) {
    if (texturaFundo.loadFromFile("fundostrangerthings.png")) {
    fundoMenu.setTexture(texturaFundo);

    fundoMenu.setScale(
        800.f / texturaFundo.getSize().x,
        600.f / texturaFundo.getSize().y
    );
}

    botaoFase1.setSize(sf::Vector2f(240.f, 50.f));
    botaoFase1.setPosition(280.f, 220.f);
    botaoFase1.setFillColor(sf::Color::Red);

    botaoFase2.setSize(sf::Vector2f(240.f, 50.f));
    botaoFase2.setPosition(280.f, 300.f);
    botaoFase2.setFillColor(sf::Color(80, 80, 80));

    fonte.loadFromFile("arial.ttf");

    textoFase1.setFont(fonte);
    textoFase1.setString("Hawkins");
    textoFase1.setCharacterSize(22);
    textoFase1.setFillColor(sf::Color::White);

    textoFase2.setFont(fonte);
    textoFase2.setString("Mundo Invertido");
    textoFase2.setCharacterSize(22);
    textoFase2.setFillColor(sf::Color::White);

    sf::FloatRect limites1 = textoFase1.getLocalBounds();
    textoFase1.setPosition(
        280.f + (240.f - limites1.width) / 2.f - limites1.left,
        220.f + (50.f - limites1.height) / 2.f - limites1.top
    );
    sf::FloatRect limites2 = textoFase2.getLocalBounds();
    textoFase2.setPosition(
        280.f + (240.f - limites2.width) / 2.f - limites2.left,
        300.f + (50.f - limites2.height) / 2.f - limites2.top
    );
}

void Menu::executar() {
    if (!ativo) return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        opcaoSelecionada = 1;
        botaoFase1.setFillColor(sf::Color::Red);
        botaoFase2.setFillColor(sf::Color(80, 80, 80));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        opcaoSelecionada = 2;
        botaoFase1.setFillColor(sf::Color(80, 80, 80));
        botaoFase2.setFillColor(sf::Color::Red);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        ativo = false;
    }

    desenhar();
}

void Menu::desenhar() {
    if (!pGG) return;
    pGG->desenharElemento(fundoMenu);
    pGG->desenharElemento(botaoFase1);
    pGG->desenharElemento(botaoFase2);
    pGG->desenharElemento(textoFase1);
    pGG->desenharElemento(textoFase2);
}

bool Menu::estaAtivo() const { return ativo; }
int Menu::getOpcaoSelecionada() const { return opcaoSelecionada; }

void Menu::reiniciar(int opcao) {
    opcaoSelecionada = opcao;
    ativo = true;

    botaoFase1.setFillColor(
        opcaoSelecionada == 1 ? sf::Color::Red : sf::Color(80, 80, 80)
    );

    botaoFase2.setFillColor(
        opcaoSelecionada == 2 ? sf::Color::Red : sf::Color(80, 80, 80)
    );
}
