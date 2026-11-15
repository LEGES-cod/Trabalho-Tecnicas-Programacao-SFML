#include "Menu.h"

Menu::Menu() : Ente(), opcaoSelecionada(1), ativo(true) {
    fundoMenu.setSize(sf::Vector2f(800.f, 600.f));
    fundoMenu.setFillColor(sf::Color(20, 20, 30));

    botaoFase1.setSize(sf::Vector2f(240.f, 50.f));
    botaoFase1.setPosition(280.f, 220.f);
    botaoFase1.setFillColor(sf::Color::Red);

    botaoFase2.setSize(sf::Vector2f(240.f, 50.f));
    botaoFase2.setPosition(280.f, 300.f);
    botaoFase2.setFillColor(sf::Color(80, 80, 80));
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
}

bool Menu::estaAtivo() const { return ativo; }
int Menu::getOpcaoSelecionada() const { return opcaoSelecionada; }
