#include "Menu.h"

Menu::Menu() : Ente(), opcaoSelecionada(1), ativo(true) {
    if (texturaFundo.loadFromFile("fundostrangerthings.png")) {
    fundoMenu.setTexture(texturaFundo);

    fundoMenu.setScale(
        800.f / texturaFundo.getSize().x,
        600.f / texturaFundo.getSize().y
    );
}

    botaoHawkins.setSize(sf::Vector2f(240.f, 50.f));
    botaoHawkins.setPosition(280.f, 220.f);
    botaoHawkins.setFillColor(sf::Color::Red);

    botaoMundoInvertido.setSize(sf::Vector2f(240.f, 50.f));
    botaoMundoInvertido.setPosition(280.f, 300.f);
    botaoMundoInvertido.setFillColor(sf::Color(80, 80, 80));

    fonte.loadFromFile("arial.ttf");

    textoHawkins.setFont(fonte);
    textoHawkins.setString("Hawkins");
    textoHawkins.setCharacterSize(22);
    textoHawkins.setFillColor(sf::Color::White);

    textoMundoInvertido.setFont(fonte);
    textoMundoInvertido.setString("Mundo Invertido");
    textoMundoInvertido.setCharacterSize(22);
    textoMundoInvertido.setFillColor(sf::Color::White);

    sf::FloatRect limites1 = textoHawkins.getLocalBounds();
    textoHawkins.setPosition(
        280.f + (240.f - limites1.width) / 2.f - limites1.left,
        220.f + (50.f - limites1.height) / 2.f - limites1.top
    );
    sf::FloatRect limites2 = textoMundoInvertido.getLocalBounds();
    textoMundoInvertido.setPosition(
        280.f + (240.f - limites2.width) / 2.f - limites2.left,
        300.f + (50.f - limites2.height) / 2.f - limites2.top
    );
}

void Menu::executar() {
    if (!ativo) return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        opcaoSelecionada = 1;
        botaoHawkins.setFillColor(sf::Color::Red);
        botaoMundoInvertido.setFillColor(sf::Color(80, 80, 80));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        opcaoSelecionada = 2;
        botaoHawkins.setFillColor(sf::Color(80, 80, 80));
        botaoMundoInvertido.setFillColor(sf::Color::Red);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        ativo = false;
    }

    desenhar();
}

void Menu::desenhar() {
    if (!pGG) return;
    pGG->desenharElemento(fundoMenu);
    pGG->desenharElemento(botaoHawkins);
    pGG->desenharElemento(botaoMundoInvertido);
    pGG->desenharElemento(textoHawkins);
    pGG->desenharElemento(textoMundoInvertido);
}

bool Menu::estaAtivo() const { return ativo; }
int Menu::getOpcaoSelecionada() const { return opcaoSelecionada; }

void Menu::reiniciar(int opcao) {
    opcaoSelecionada = opcao;
    ativo = true;

    botaoHawkins.setFillColor(
        opcaoSelecionada == 1 ? sf::Color::Red : sf::Color(80, 80, 80)
    );

    botaoMundoInvertido.setFillColor(
        opcaoSelecionada == 2 ? sf::Color::Red : sf::Color(80, 80, 80)
    );
}
