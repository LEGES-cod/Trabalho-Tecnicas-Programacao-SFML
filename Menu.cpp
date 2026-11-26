#include "Menu.h"
#include <algorithm>
#include <fstream>
#include <sstream>

Menu::Menu()
    : Ente(),
      opcaoSelecionada(1),
      ativo(true),
      sairSolicitado(false),
      carregarSolicitado(false),
      selecionandoModo(false),
      doisJogadores(false),
      selecionandoPersonagem(false),
      vendoRanking(false),
      teclaAnterior(false),
      personagemSelecionado(0),
      fundoCarregado(false),
      fonteCarregada(false) {

    fundoCarregado = texturaFundo.loadFromFile("fundostrangerthings.png");

    if (fundoCarregado) {
        fundoMenu.setTexture(texturaFundo);
        fundoMenu.setScale(
            800.f / texturaFundo.getSize().x,
            600.f / texturaFundo.getSize().y
        );
    }

    fonteCarregada = fonte.loadFromFile("arial.ttf");

    const char* rotulos[5] = {
        "Hawkins",
        "Mundo Invertido",
        "Carregar Jogo",
        "Ranking",
        "Sair"
    };

    for (int i = 0; i < 5; i++) {
        float y = 160.f + i * 66.f;

        botoesPrincipais[i].setSize(sf::Vector2f(260.f, 48.f));
        botoesPrincipais[i].setPosition(270.f, y);
        botoesPrincipais[i].setFillColor(i == 0 ? sf::Color::Red : sf::Color(80, 80, 80));

        textosPrincipais[i].setString(rotulos[i]);

        if (fonteCarregada) {
            textosPrincipais[i].setFont(fonte);
            textosPrincipais[i].setCharacterSize(22);
            textosPrincipais[i].setFillColor(sf::Color::White);

            sf::FloatRect limites = textosPrincipais[i].getLocalBounds();
            textosPrincipais[i].setPosition(
                270.f + (260.f - limites.width) / 2.f - limites.left,
                y + (48.f - limites.height) / 2.f - limites.top
            );
        }
    }

    const char* modos[2] = { "1 Jogador", "2 Jogadores" };
    for (int i = 0; i < 2; i++) {
        float y = 230.f + i * 75.f;

        botoesModo[i].setSize(sf::Vector2f(260.f, 52.f));
        botoesModo[i].setPosition(270.f, y);
        botoesModo[i].setFillColor(i == 0 ? sf::Color::Red : sf::Color(80, 80, 80));

        textosModo[i].setString(modos[i]);

        if (fonteCarregada) {
            textosModo[i].setFont(fonte);
            textosModo[i].setCharacterSize(22);
            textosModo[i].setFillColor(sf::Color::White);

            sf::FloatRect lim = textosModo[i].getLocalBounds();
            textosModo[i].setPosition(
                270.f + (260.f - lim.width) / 2.f - lim.left,
                y + (52.f - lim.height) / 2.f - lim.top
            );
        }
    }

    if (fonteCarregada) {
        tituloModo.setFont(fonte);
        tituloModo.setString("Modo de Jogo");
        tituloModo.setCharacterSize(30);
        tituloModo.setFillColor(sf::Color::White);
        sf::FloatRect limModo = tituloModo.getLocalBounds();
        tituloModo.setPosition(
            (800.f - limModo.width) / 2.f - limModo.left,
            120.f
        );

        tituloPersonagens.setFont(fonte);
        tituloPersonagens.setString("Escolha seu personagem");
        tituloPersonagens.setCharacterSize(30);
        tituloPersonagens.setFillColor(sf::Color::White);
        sf::FloatRect limitesTitulo = tituloPersonagens.getLocalBounds();
        tituloPersonagens.setPosition(
            (800.f - limitesTitulo.width) / 2.f - limitesTitulo.left,
            80.f
        );

        subtituloPersonagens.setFont(fonte);
        subtituloPersonagens.setString("J1 escolhe (J2 joga com o outro)");
        subtituloPersonagens.setCharacterSize(18);
        subtituloPersonagens.setFillColor(sf::Color(120, 200, 255));
        sf::FloatRect limSub = subtituloPersonagens.getLocalBounds();
        subtituloPersonagens.setPosition(
            (800.f - limSub.width) / 2.f - limSub.left,
            130.f
        );

        textoVoltar.setFont(fonte);
        textoVoltar.setString("Pressione ESC para voltar");
        textoVoltar.setCharacterSize(16);
        textoVoltar.setFillColor(sf::Color(200, 200, 200));
        textoVoltar.setPosition(295.f, 530.f);

        painelRanking.setSize(sf::Vector2f(460.f, 340.f));
        painelRanking.setPosition(170.f, 130.f);
        painelRanking.setFillColor(sf::Color(20, 20, 20, 230));
        painelRanking.setOutlineThickness(2.f);
        painelRanking.setOutlineColor(sf::Color::Red);

        tituloRanking.setFont(fonte);
        tituloRanking.setString("TOP 5 - RANKING");
        tituloRanking.setCharacterSize(28);
        tituloRanking.setFillColor(sf::Color::Red);
        sf::FloatRect limRank = tituloRanking.getLocalBounds();
        tituloRanking.setPosition(
            (800.f - limRank.width) / 2.f - limRank.left,
            150.f
        );

        textoLinhasRanking.setFont(fonte);
        textoLinhasRanking.setCharacterSize(22);
        textoLinhasRanking.setFillColor(sf::Color::White);
        textoLinhasRanking.setPosition(210.f, 215.f);
    }

    const char* nomes[2] = { "Mike", "Eleven" };
    const char* arquivos[2] = { "mike.jpg", "eleven.png" };
    const float posicoesX[2] = { 215.f, 435.f };
    const float y = 210.f;

    for (int i = 0; i < 2; i++) {
        float x = posicoesX[i];

        cartoesPersonagens[i].setSize(sf::Vector2f(150.f, 180.f));
        cartoesPersonagens[i].setPosition(x, y);
        cartoesPersonagens[i].setFillColor(sf::Color(30, 30, 30, 220));
        cartoesPersonagens[i].setOutlineThickness(3.f);
        cartoesPersonagens[i].setOutlineColor(sf::Color(120, 120, 120));

        imagensCarregadas[i] = texturasPersonagens[i].loadFromFile(arquivos[i]);

        if (imagensCarregadas[i]) {
            spritesPersonagens[i].setTexture(texturasPersonagens[i]);
            sf::FloatRect imagem = spritesPersonagens[i].getLocalBounds();

            float escala = std::min(110.f / imagem.width, 110.f / imagem.height);
            spritesPersonagens[i].setScale(escala, escala);

            float largura = imagem.width * escala;
            float altura = imagem.height * escala;

            spritesPersonagens[i].setPosition(
                x + (150.f - largura) / 2.f,
                y + 10.f + (110.f - altura) / 2.f
            );
        }

        nomesPersonagens[i].setString(nomes[i]);

        if (fonteCarregada) {
            nomesPersonagens[i].setFont(fonte);
            nomesPersonagens[i].setCharacterSize(20);
            nomesPersonagens[i].setFillColor(sf::Color::White);

            sf::FloatRect limitesNome = nomesPersonagens[i].getLocalBounds();
            nomesPersonagens[i].setPosition(
                x + (150.f - limitesNome.width) / 2.f - limitesNome.left,
                y + 140.f
            );
        }
    }

    atualizarDestaquePrincipal();
    atualizarDestaqueModo();
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

    bool enter = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
    bool esc = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

    bool algumaTecla = cima || baixo || esquerda || direita || enter || esc;

    if (algumaTecla && !teclaAnterior) {
        if (vendoRanking) {
            if (esc || enter) {
                vendoRanking = false;
            }
        }
        else if (!selecionandoModo && !selecionandoPersonagem) {
            if (cima && opcaoSelecionada > 1) {
                opcaoSelecionada--;
                atualizarDestaquePrincipal();
            }
            else if (baixo && opcaoSelecionada < 5) {
                opcaoSelecionada++;
                atualizarDestaquePrincipal();
            }
            else if (enter) {
                if (opcaoSelecionada == 1 || opcaoSelecionada == 2) {
                    selecionandoModo = true;
                    atualizarDestaqueModo();
                }
                else if (opcaoSelecionada == 3) {
                    carregarSolicitado = true;
                }
                else if (opcaoSelecionada == 4) {
                    carregarRanking();
                    vendoRanking = true;
                }
                else if (opcaoSelecionada == 5) {
                    sairSolicitado = true;
                }
            }
        }
        else if (selecionandoModo) {
            if (esc) {
                selecionandoModo = false;
            }
            else if (cima) {
                doisJogadores = false;
                atualizarDestaqueModo();
            }
            else if (baixo) {
                doisJogadores = true;
                atualizarDestaqueModo();
            }
            else if (enter) {
                selecionandoModo = false;
                selecionandoPersonagem = true;
                atualizarDestaquePersonagem();
            }
        }
        else {
            if (esc) {
                selecionandoPersonagem = false;
                selecionandoModo = true;
            }
            else if (enter) {
                ativo = false;
            }
            else {
                if (esquerda && personagemSelecionado > 0) {
                    personagemSelecionado--;
                }
                else if (direita && personagemSelecionado < 1) {
                    personagemSelecionado++;
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

    if (vendoRanking) {
        pGG->desenharElemento(painelRanking);
        if (fonteCarregada) {
            pGG->desenharElemento(tituloRanking);
            pGG->desenharElemento(textoLinhasRanking);
            pGG->desenharElemento(textoVoltar);
        }
    }
    else if (!selecionandoModo && !selecionandoPersonagem) {
        for (int i = 0; i < 5; i++) {
            pGG->desenharElemento(botoesPrincipais[i]);
            if (fonteCarregada) {
                pGG->desenharElemento(textosPrincipais[i]);
            }
        }
    }
    else if (selecionandoModo) {
        if (fonteCarregada) {
            pGG->desenharElemento(tituloModo);
            pGG->desenharElemento(textoVoltar);
        }
        for (int i = 0; i < 2; i++) {
            pGG->desenharElemento(botoesModo[i]);
            if (fonteCarregada) {
                pGG->desenharElemento(textosModo[i]);
            }
        }
    }
    else {
        if (fonteCarregada) {
            pGG->desenharElemento(tituloPersonagens);
            if (doisJogadores) {
                pGG->desenharElemento(subtituloPersonagens);
            }
            pGG->desenharElemento(textoVoltar);
        }

        for (int i = 0; i < 2; i++) {
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

void Menu::atualizarDestaquePrincipal() {
    for (int i = 0; i < 5; i++) {
        botoesPrincipais[i].setFillColor(
            (i + 1) == opcaoSelecionada ? sf::Color::Red : sf::Color(80, 80, 80)
        );
    }
}

void Menu::atualizarDestaqueModo() {
    botoesModo[0].setFillColor(!doisJogadores ? sf::Color::Red : sf::Color(80, 80, 80));
    botoesModo[1].setFillColor(doisJogadores ? sf::Color::Red : sf::Color(80, 80, 80));
}

void Menu::atualizarDestaquePersonagem() {
    for (int i = 0; i < 2; i++) {
        if (i == personagemSelecionado) {
            cartoesPersonagens[i].setOutlineColor(sf::Color::Red);
            cartoesPersonagens[i].setOutlineThickness(4.f);
        }
        else {
            cartoesPersonagens[i].setOutlineColor(sf::Color(120, 120, 120));
            cartoesPersonagens[i].setOutlineThickness(2.f);
        }
    }
}

void Menu::carregarRanking() {
    std::ifstream arquivo("ranking.txt");
    std::vector<std::pair<int, std::string>> registros;

    std::string nome;
    int pontos;
    while (arquivo >> nome >> pontos) {
        registros.push_back({ pontos, nome });
    }
    arquivo.close();

    std::sort(registros.rbegin(), registros.rend());

    std::ostringstream ss;
    if (registros.empty()) {
        ss << "Nenhuma pontuacao registrada ainda.";
    }
    else {
        int limite = std::min(5, static_cast<int>(registros.size()));
        for (int i = 0; i < limite; i++) {
            ss << (i + 1) << ". " << registros[i].second
               << "  -  " << registros[i].first << " pts\n\n";
        }
    }

    textoLinhasRanking.setString(ss.str());
}

void Menu::salvarPontuacao(int indicePersonagem, int pontos, bool coop) {
    if (pontos <= 0) return;

    std::ofstream arquivo("ranking.txt", std::ios::app);
    if (arquivo.is_open()) {
        std::string nome = coop ? "Dupla(2P)" : ((indicePersonagem == 1) ? "Eleven" : "Mike");
        arquivo << nome << " " << pontos << "\n";
        arquivo.close();
    }
}

bool Menu::estaAtivo() const {
    return ativo;
}

bool Menu::querSair() const {
    return sairSolicitado;
}

bool Menu::querCarregar() const {
    return carregarSolicitado;
}

bool Menu::isDoisJogadores() const {
    return doisJogadores;
}

bool Menu::estaSelecionandoPersonagem() const {
    return selecionandoPersonagem;
}

int Menu::getOpcaoSelecionada() const {
    return opcaoSelecionada;
}

int Menu::getPersonagemSelecionado() const {
    return personagemSelecionado;
}

void Menu::reiniciar(int opcao) {
    opcaoSelecionada = opcao;
    ativo = true;
    sairSolicitado = false;
    carregarSolicitado = false;

    selecionandoModo = false;
    selecionandoPersonagem = false;
    vendoRanking = false;
    personagemSelecionado = 0;
    teclaAnterior = true;

    atualizarDestaquePrincipal();
    atualizarDestaqueModo();
    atualizarDestaquePersonagem();
}
