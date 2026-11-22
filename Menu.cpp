#include "Menu.h"
#include <algorithm>

Menu::Menu()
    : Ente(),
      opcaoSelecionada(1),
      ativo(true),
      selecionandoPersonagem(false),
      teclaAnterior(false),
      personagemSelecionado(0),
      fundoCarregado(false),
      fonteCarregada(false) {

    // Carrega o fundo do menu.
    fundoCarregado = texturaFundo.loadFromFile(
        "fundostrangerthings.png"
    );

    if (fundoCarregado) {
        fundoMenu.setTexture(texturaFundo);

        fundoMenu.setScale(
            800.f / texturaFundo.getSize().x,
            600.f / texturaFundo.getSize().y
        );
    }

    // Configura os botões das fases.
    botaoHawkins.setSize(sf::Vector2f(240.f, 50.f));
    botaoHawkins.setPosition(280.f, 220.f);
    botaoHawkins.setFillColor(sf::Color::Red);

    botaoMundoInvertido.setSize(sf::Vector2f(240.f, 50.f));
    botaoMundoInvertido.setPosition(280.f, 300.f);
    botaoMundoInvertido.setFillColor(sf::Color(80, 80, 80));

    // Carrega a fonte.
    fonteCarregada = fonte.loadFromFile("arial.ttf");

    textoHawkins.setString("Hawkins");
    textoMundoInvertido.setString("Mundo Invertido");

    if (fonteCarregada) {
        textoHawkins.setFont(fonte);
        textoHawkins.setCharacterSize(22);
        textoHawkins.setFillColor(sf::Color::White);

        textoMundoInvertido.setFont(fonte);
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

        tituloPersonagens.setFont(fonte);
        tituloPersonagens.setString("Escolha seu personagem");
        tituloPersonagens.setCharacterSize(30);
        tituloPersonagens.setFillColor(sf::Color::White);

        sf::FloatRect limitesTitulo =
            tituloPersonagens.getLocalBounds();

        tituloPersonagens.setPosition(
            (800.f - limitesTitulo.width) / 2.f - limitesTitulo.left,
            45.f
        );
    }

    // Nomes e imagens dos personagens.
    const char* nomes[6] = {
        "Dustin",
        "Eleven",
        "Lucas",
        "Max",
        "Mike",
        "Will"
    };

    const char* arquivos[6] = {
        "dustin.jpg",
        "eleven.png",
        "lucas.jpg",
        "max.jpg",
        "mike.jpg",
        "will.png"
    };

    // Posições dos seis cartões.
    const float posicoesX[3] = {
        150.f, 325.f, 500.f
    };

    const float posicoesY[2] = {
        130.f, 345.f
    };

    for (int i = 0; i < 6; i++) {

        int coluna = i % 3;
        int linha = i / 3;

        float x = posicoesX[coluna];
        float y = posicoesY[linha];

        // Cartão do personagem.
        cartoesPersonagens[i].setSize(
            sf::Vector2f(150.f, 180.f)
        );

        cartoesPersonagens[i].setPosition(x, y);
        cartoesPersonagens[i].setFillColor(
            sf::Color(30, 30, 30, 220)
        );

        cartoesPersonagens[i].setOutlineThickness(3.f);
        cartoesPersonagens[i].setOutlineColor(
            sf::Color(120, 120, 120)
        );

        // Carrega a imagem.
        imagensCarregadas[i] =
            texturasPersonagens[i].loadFromFile(arquivos[i]);

        if (imagensCarregadas[i]) {

            spritesPersonagens[i].setTexture(
                texturasPersonagens[i]
            );

            sf::FloatRect imagem =
                spritesPersonagens[i].getLocalBounds();

            // Mantém a proporção da imagem.
            float escala = std::min(
                110.f / imagem.width,
                110.f / imagem.height
            );

            spritesPersonagens[i].setScale(escala, escala);

            float largura = imagem.width * escala;
            float altura = imagem.height * escala;

            spritesPersonagens[i].setPosition(
                x + (150.f - largura) / 2.f,
                y + 10.f + (110.f - altura) / 2.f
            );
        }

        // Nome abaixo da imagem.
        nomesPersonagens[i].setString(nomes[i]);

        if (fonteCarregada) {
            nomesPersonagens[i].setFont(fonte);
            nomesPersonagens[i].setCharacterSize(20);
            nomesPersonagens[i].setFillColor(sf::Color::White);

            sf::FloatRect limitesNome =
                nomesPersonagens[i].getLocalBounds();

            nomesPersonagens[i].setPosition(
                x + (150.f - limitesNome.width) / 2.f
                    - limitesNome.left,
                y + 140.f
            );
        }
    }

    atualizarDestaquePersonagem();
}

void Menu::executar() {

    if (!ativo) return;

    bool cima =
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::W);

    bool baixo =
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::S);

    bool esquerda =
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A);

    bool direita =
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::D);

    bool enter =
        sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);

    bool algumaTecla =
        cima || baixo || esquerda || direita || enter;

    // Evita repetir a seleção enquanto a tecla estiver pressionada.
    if (algumaTecla && !teclaAnterior) {

        if (!selecionandoPersonagem) {

            // Primeira tela: escolha da fase.
            if (cima) {
                opcaoSelecionada = 1;
            }
            else if (baixo) {
                opcaoSelecionada = 2;
            }

            botaoHawkins.setFillColor(
                opcaoSelecionada == 1
                    ? sf::Color::Red
                    : sf::Color(80, 80, 80)
            );

            botaoMundoInvertido.setFillColor(
                opcaoSelecionada == 2
                    ? sf::Color::Red
                    : sf::Color(80, 80, 80)
            );

            // Confirma a fase e abre a seleção de personagens.
            if (enter) {
                selecionandoPersonagem = true;
                atualizarDestaquePersonagem();
            }
        }
        else {

            // Segunda tela: escolha do personagem.
            if (enter) {
                ativo = false;
            }
            else {

                int coluna = personagemSelecionado % 3;
                int linha = personagemSelecionado / 3;

                if (esquerda && coluna > 0) {
                    personagemSelecionado--;
                }
                else if (direita && coluna < 2) {
                    personagemSelecionado++;
                }
                else if (cima && linha > 0) {
                    personagemSelecionado -= 3;
                }
                else if (baixo && linha < 1) {
                    personagemSelecionado += 3;
                }

                atualizarDestaquePersonagem();
            }
        }
    }

    teclaAnterior = algumaTecla;

    desenhar();
}

void Menu::desenhar() {

    if (!pGG) return;

    if (fundoCarregado) {
        pGG->desenharElemento(fundoMenu);
    }

    if (!selecionandoPersonagem) {

        // Desenha a escolha das fases.
        pGG->desenharElemento(botaoHawkins);
        pGG->desenharElemento(botaoMundoInvertido);

        if (fonteCarregada) {
            pGG->desenharElemento(textoHawkins);
            pGG->desenharElemento(textoMundoInvertido);
        }
    }
    else {

        // Desenha a escolha dos personagens.
        if (fonteCarregada) {
            pGG->desenharElemento(tituloPersonagens);
        }

        for (int i = 0; i < 6; i++) {

            pGG->desenharElemento(cartoesPersonagens[i]);

            if (imagensCarregadas[i]) {
                pGG->desenharElemento(spritesPersonagens[i]);
            }

            if (fonteCarregada) {
                pGG->desenharElemento(nomesPersonagens[i]);
            }
        }
    }
}

void Menu::atualizarDestaquePersonagem() {

    for (int i = 0; i < 6; i++) {

        if (i == personagemSelecionado) {
            cartoesPersonagens[i].setOutlineColor(sf::Color::Red);
            cartoesPersonagens[i].setOutlineThickness(4.f);
        }
        else {
            cartoesPersonagens[i].setOutlineColor(
                sf::Color(120, 120, 120)
            );

            cartoesPersonagens[i].setOutlineThickness(2.f);
        }
    }
}

bool Menu::estaAtivo() const {
    return ativo;
}

bool Menu::estaSelecionandoPersonagem() const {
    return selecionandoPersonagem;
}

int Menu::getOpcaoSelecionada() const {
    return opcaoSelecionada;
}

int Menu::getPersonagemSelecionado() const {
    // 0 = Dustin, 1 = Eleven, 2 = Lucas,
    // 3 = Max, 4 = Mike, 5 = Will.
    return personagemSelecionado;
}

void Menu::reiniciar(int opcao) {

    opcaoSelecionada = opcao;
    ativo = true;

    selecionandoPersonagem = false;
    personagemSelecionado = 0;
    teclaAnterior = false;

    botaoHawkins.setFillColor(
        opcaoSelecionada == 1
            ? sf::Color::Red
            : sf::Color(80, 80, 80)
    );

    botaoMundoInvertido.setFillColor(
        opcaoSelecionada == 2
            ? sf::Color::Red
            : sf::Color(80, 80, 80)
    );

    atualizarDestaquePersonagem();
}
