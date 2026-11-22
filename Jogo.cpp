
#include "Jogo.h"

Jogo::Jogo()
    : pGG(GerenciadorGrafico::getInstancia()),
      faseAtual(nullptr),
      segundaFase(false),
      gameOver(false),
      opcaoGameOver(1) {

    Ente::setGG(pGG);

    // Fundo da tela de Game Over
    fundoGameOver.setSize(sf::Vector2f(800.f, 600.f));
    fundoGameOver.setFillColor(sf::Color(0, 0, 0, 230));

    // Carrega a mesma fonte utilizada pelo menu
    fonteGameOver.loadFromFile("arial.ttf");

    textoGameOver.setFont(fonteGameOver);
    textoGameOver.setString("GAME OVER");
    textoGameOver.setCharacterSize(48);
    textoGameOver.setFillColor(sf::Color::Red);

    textoTentarNovamente.setFont(fonteGameOver);
    textoTentarNovamente.setString("Tentar Novamente");
    textoTentarNovamente.setCharacterSize(24);
    textoTentarNovamente.setFillColor(sf::Color::White);

    textoSair.setFont(fonteGameOver);
    textoSair.setString("Sair");
    textoSair.setCharacterSize(24);
    textoSair.setFillColor(sf::Color::White);

    // Botao Tentar Novamente
    botaoTentarNovamente.setSize(sf::Vector2f(300.f, 55.f));
    botaoTentarNovamente.setPosition(250.f, 290.f);

    // Botao sair
    botaoSair.setSize(sf::Vector2f(300.f, 55.f));
    botaoSair.setPosition(250.f, 365.f);

    // Centraliza os textos
    sf::FloatRect limites = textoGameOver.getLocalBounds();
    textoGameOver.setPosition(
        400.f - (limites.width / 2.f + limites.left),
        190.f - (limites.height / 2.f + limites.top)
    );

    limites = textoTentarNovamente.getLocalBounds();
    textoTentarNovamente.setPosition(
        400.f - (limites.width / 2.f + limites.left),
        317.5f - (limites.height / 2.f + limites.top)
    );

    limites = textoSair.getLocalBounds();
    textoSair.setPosition(
        400.f - (limites.width / 2.f + limites.left),
        392.5f - (limites.height / 2.f + limites.top)
    );
}

Jogo::~Jogo() {
    delete faseAtual;
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

        // Tela de Game Over
        if (gameOver) {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                opcaoGameOver = 1;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                opcaoGameOver = 2;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

            if (opcaoGameOver == 1) {
                gameOver = false;
                menu.reiniciar(segundaFase ? 2 : 1);
            }
                else {
                    // Encerra o jogo
                    pGG->fechar();
                }
            }

            // Destaca a opcao selecionada
            botaoTentarNovamente.setFillColor(
                opcaoGameOver == 1 ? sf::Color::Red : sf::Color(80, 80, 80)
            );

            botaoSair.setFillColor(
                opcaoGameOver == 2 ? sf::Color::Red : sf::Color(80, 80, 80)
            );

            pGG->desenharElemento(fundoGameOver);
            pGG->desenharElemento(textoGameOver);
            pGG->desenharElemento(botaoTentarNovamente);
            pGG->desenharElemento(botaoSair);
            pGG->desenharElemento(textoTentarNovamente);
            pGG->desenharElemento(textoSair);
        }

        // Menu inicial
        else if (menu.estaAtivo()) {
            menu.executar();

            if (!menu.estaAtivo()) {
                if (menu.getOpcaoSelecionada() == 1) {
                    faseAtual = new FaseHawkins();
                    segundaFase = false;
                }
                else {
                    faseAtual = new FaseMundoInvertido();
                    segundaFase = true;
                }
            }
        }

        // Fase atual
        else if (faseAtual != nullptr) {
            faseAtual->executar();

            // Verifica se o jogador morreu
            if (faseAtual->jogadorMorreu()) {
                delete faseAtual;
                faseAtual = nullptr;

                gameOver = true;
                opcaoGameOver = 1;
            }

            // Transicao entre fases
            else if (faseAtual->terminou() && !segundaFase) {
                delete faseAtual;
                faseAtual = new FaseMundoInvertido();
                segundaFase = true;
            }
            else if (faseAtual->terminou() && segundaFase) {
                pGG->fechar();
            }
        }

        pGG->mostrar();
    }
}
