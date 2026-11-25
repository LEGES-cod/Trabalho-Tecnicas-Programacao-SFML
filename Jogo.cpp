#include "Jogo.h"

Jogo::Jogo()
    : pGG(GerenciadorGrafico::getInstancia()),
      faseAtual(nullptr),
      segundaFase(false),
      gameOver(false),
      opcaoGameOver(1),
      pausado(false),
      opcaoPausa(1),
      vitoria(false),
      opcaoVitoria(1),
      pontuacaoFinal(0),
      teclaMenuAnterior(false) {

    Ente::setGG(pGG);

    fundoSobreposicao.setSize(sf::Vector2f(800.f, 600.f));
    fundoSobreposicao.setFillColor(sf::Color(0, 0, 0, 220));

    fonteUI.loadFromFile("arial.ttf");

    textoTituloTela.setFont(fonteUI);
    textoTituloTela.setCharacterSize(46);

    textoSubtituloTela.setFont(fonteUI);
    textoSubtituloTela.setCharacterSize(22);
    textoSubtituloTela.setFillColor(sf::Color::White);

    for (int i = 0; i < 3; i++) {
        botoesTela[i].setSize(sf::Vector2f(300.f, 52.f));
        textosBotoesTela[i].setFont(fonteUI);
        textosBotoesTela[i].setCharacterSize(22);
        textosBotoesTela[i].setFillColor(sf::Color::White);
    }
}

Jogo::~Jogo() {
    delete faseAtual;
}

void Jogo::configurarBotao(int indice, const std::string& texto, float y) {
    botoesTela[indice].setPosition(250.f, y);
    textosBotoesTela[indice].setString(texto);

    sf::FloatRect limites = textosBotoesTela[indice].getLocalBounds();
    textosBotoesTela[indice].setPosition(
        400.f - (limites.width / 2.f + limites.left),
        y + 26.f - (limites.height / 2.f + limites.top)
    );
}

void Jogo::desenharTelaOpcoes(const std::string& titulo, sf::Color corTitulo,
                              const std::string& subtitulo, int qtdBotoes, int opcaoAtual) {
    pGG->desenharElemento(fundoSobreposicao);

    textoTituloTela.setString(titulo);
    textoTituloTela.setFillColor(corTitulo);
    sf::FloatRect limTitulo = textoTituloTela.getLocalBounds();
    textoTituloTela.setPosition(
        400.f - (limTitulo.width / 2.f + limTitulo.left),
        140.f
    );
    pGG->desenharElemento(textoTituloTela);

    if (!subtitulo.empty()) {
        textoSubtituloTela.setString(subtitulo);
        sf::FloatRect limSub = textoSubtituloTela.getLocalBounds();
        textoSubtituloTela.setPosition(
            400.f - (limSub.width / 2.f + limSub.left),
            210.f
        );
        pGG->desenharElemento(textoSubtituloTela);
    }

    for (int i = 0; i < qtdBotoes; i++) {
        botoesTela[i].setFillColor(
            (i + 1) == opcaoAtual ? sf::Color::Red : sf::Color(80, 80, 80)
        );
        pGG->desenharElemento(botoesTela[i]);
        pGG->desenharElemento(textosBotoesTela[i]);
    }
}

void Jogo::executar() {
    while (pGG->janelaAberta()) {
        sf::Event evento;

        while (pGG->getJanela().pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                pGG->fechar();
            }
        }

        pGG->atualizarDeltaTime();
        pGG->limpar();

        bool cima = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        bool baixo = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
                     sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        bool enter = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
        bool esc = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
        bool algumaTecla = cima || baixo || enter || esc;

        // Tela de Game Over
        if (gameOver) {
            if (algumaTecla && !teclaMenuAnterior) {
                if (cima && opcaoGameOver > 1) opcaoGameOver--;
                else if (baixo && opcaoGameOver < 3) opcaoGameOver++;
                else if (enter) {
                    if (opcaoGameOver == 1) {
                        gameOver = false;
                        faseAtual = segundaFase
                            ? static_cast<Fase*>(new FaseMundoInvertido())
                            : static_cast<Fase*>(new FaseHawkins());

                        int p1 = menu.getPersonagemSelecionado();
                        faseAtual->setPersonagem(p1);
                        if (menu.isDoisJogadores()) {
                            faseAtual->ativarSegundoJogador(1 - p1);
                        }
                    }
                    else if (opcaoGameOver == 2) {
                        gameOver = false;
                        menu.reiniciar(1);
                    }
                    else {
                        pGG->fechar();
                    }
                }
            }

            configurarBotao(0, "Tentar Novamente", 270.f);
            configurarBotao(1, "Menu Principal", 340.f);
            configurarBotao(2, "Sair", 410.f);
            desenharTelaOpcoes(
                "GAME OVER",
                sf::Color::Red,
                "Pontuacao: " + std::to_string(pontuacaoFinal),
                3,
                opcaoGameOver
            );
        }

        // Tela de Vitoria
        else if (vitoria) {
            if (algumaTecla && !teclaMenuAnterior) {
                if (cima && opcaoVitoria > 1) opcaoVitoria--;
                else if (baixo && opcaoVitoria < 2) opcaoVitoria++;
                else if (enter) {
                    if (opcaoVitoria == 1) {
                        vitoria = false;
                        menu.reiniciar(1);
                    }
                    else {
                        pGG->fechar();
                    }
                }
            }

            configurarBotao(0, "Menu Principal", 290.f);
            configurarBotao(1, "Sair", 365.f);
            desenharTelaOpcoes(
                "VITORIA!",
                sf::Color(50, 220, 100),
                "Pontuacao Final: " + std::to_string(pontuacaoFinal),
                2,
                opcaoVitoria
            );
        }

        // Menu de Pausa
        else if (pausado && faseAtual != nullptr) {
            faseAtual->desenhar();

            if (algumaTecla && !teclaMenuAnterior) {
                if (esc) {
                    pausado = false;
                }
                else if (cima && opcaoPausa > 1) opcaoPausa--;
                else if (baixo && opcaoPausa < 3) opcaoPausa++;
                else if (enter) {
                    if (opcaoPausa == 1) {
                        pausado = false;
                    }
                    else if (opcaoPausa == 2) {
                        delete faseAtual;
                        faseAtual = nullptr;
                        pausado = false;
                        menu.reiniciar(1);
                    }
                    else {
                        pGG->fechar();
                    }
                }
            }

            configurarBotao(0, "Continuar", 260.f);
            configurarBotao(1, "Menu Principal", 330.f);
            configurarBotao(2, "Sair", 400.f);
            desenharTelaOpcoes("JOGO PAUSADO", sf::Color::Yellow, "", 3, opcaoPausa);
        }

        // Menu Inicial
        else if (menu.estaAtivo()) {
            menu.executar();

            if (menu.querSair()) {
                pGG->fechar();
            }
            else if (!menu.estaAtivo()) {
                if (menu.getOpcaoSelecionada() == 1) {
                    faseAtual = new FaseHawkins();
                    segundaFase = false;
                }
                else {
                    faseAtual = new FaseMundoInvertido();
                    segundaFase = true;
                }

                int p1 = menu.getPersonagemSelecionado();
                faseAtual->setPersonagem(p1);
                if (menu.isDoisJogadores()) {
                    faseAtual->ativarSegundoJogador(1 - p1);
                }
            }
        }

        // Fase em andamento
        else if (faseAtual != nullptr) {
            if (esc && !teclaMenuAnterior) {
                pausado = true;
                opcaoPausa = 1;
            }
            else {
                faseAtual->executar();

                if (faseAtual->jogadorMorreu()) {
                    pontuacaoFinal = faseAtual->getPontosJogador();
                    Menu::salvarPontuacao(
                        menu.getPersonagemSelecionado(),
                        pontuacaoFinal,
                        menu.isDoisJogadores()
                    );

                    delete faseAtual;
                    faseAtual = nullptr;

                    gameOver = true;
                    opcaoGameOver = 1;
                }
                else if (faseAtual->terminou() && !segundaFase) {
                    int pontosAcumulados = faseAtual->getPontosJogador();
                    delete faseAtual;
                    faseAtual = new FaseMundoInvertido();

                    int p1 = menu.getPersonagemSelecionado();
                    faseAtual->setPersonagem(p1);
                    if (menu.isDoisJogadores()) {
                        faseAtual->ativarSegundoJogador(1 - p1);
                    }
                    faseAtual->setPontosJogador(pontosAcumulados);
                    segundaFase = true;
                }
                else if (faseAtual->terminou() && segundaFase) {
                    pontuacaoFinal = faseAtual->getPontosJogador();
                    Menu::salvarPontuacao(
                        menu.getPersonagemSelecionado(),
                        pontuacaoFinal,
                        menu.isDoisJogadores()
                    );

                    delete faseAtual;
                    faseAtual = nullptr;

                    vitoria = true;
                    opcaoVitoria = 1;
                }
            }
        }

        teclaMenuAnterior = algumaTecla;
        pGG->mostrar();
    }
}
