
#include "Fase.h"
#include "BolaDeFogo.h"
#include "PlataformaEstatica.h"

Fase::Fase(const std::string& caminhoFundo, const sf::Color& corChao)
    : Ente(), pJog1(nullptr), concluida(false),
      exigirDerrotaInimigos(false), corChao(corChao) {
    if (texturaFundo.loadFromFile(caminhoFundo)) {
        spriteFundo.setTexture(texturaFundo);
    }
}

Fase::~Fase() {
    gColisoes.limpar();
    LEnts.limpar();
}

void Fase::inicializar() {
    pJog1 = new Jogador();
    LEnts.incluir(pJog1);
    gColisoes.setJogador(pJog1);

    adicionarChao(new Chao(sf::Vector2f(0.f, 535.f),
                           sf::Vector2f(800.f, 65.f), corChao));
    // Plataforma elevada compartilhada pelas fases; o jogador pode pular e aterrissar nela.
    adicionarObstaculo(new PlataformaEstatica(sf::Vector2f(300.f, 450.f),
                                               sf::Vector2f(180.f, 20.f)));
}

void Fase::adicionarInimigo(Inimigo* inimigo) {
    if (inimigo) {
        inimigo->setJogador(pJog1);
        inimigos.push_back(inimigo);
        LEnts.incluir(inimigo);
        gColisoes.incluirInimigo(inimigo);
    }
}

void Fase::adicionarChao(Chao* chao) {
    if (chao) {
        LEnts.incluir(chao);
        gColisoes.incluirChao(chao);
    }
}

void Fase::adicionarObstaculo(Obstaculo* obstaculo) {
    if (obstaculo) {
        LEnts.incluir(obstaculo);
        gColisoes.incluirObstaculo(obstaculo);
    }
}

void Fase::executar() {
    desenhar();

    LEnts.percorrer();

    // Cria uma bola de fogo quando o jogador solicita um disparo.
    if (pJog1 && pJog1->consumirDisparo()) {
        sf::Vector2f posicao = pJog1->getPosicao();
        float direcao = pJog1->getDirecao();

        BolaDeFogo* bolaFogo = new BolaDeFogo(
            sf::Vector2f(
                direcao > 0 ? posicao.x + 35.f : posicao.x - 16.f,
                posicao.y + 10.f
            ),
            500.f * direcao,
            1,
            sf::Color(255, 100, 0)
        );

        LEnts.incluir(bolaFogo);
        gColisoes.incluirProjetilJogador(bolaFogo);
    }

    gColisoes.executar();

    if (pJog1 && pJog1->getPosicao().x > 750.f) {
        bool todosInimigosDerrotados = true;

        if (exigirDerrotaInimigos) {
            for (Inimigo* inimigo : inimigos) {
                if (inimigo && inimigo->estaVivo()) {
                    todosInimigosDerrotados = false;
                    break;
                }
            }
        }

        if (todosInimigosDerrotados) {
            concluida = true;
        }
    }
}

void Fase::desenhar() {
    if (!pGG) return;

    if (texturaFundo.getSize().x > 0 && texturaFundo.getSize().y > 0) {
        float escalaX = static_cast<float>(pGG->getJanela().getSize().x) / texturaFundo.getSize().x;
        float escalaY = static_cast<float>(pGG->getJanela().getSize().y) / texturaFundo.getSize().y;
        spriteFundo.setScale(escalaX, escalaY);
    }

    pGG->desenharElemento(spriteFundo);
}

bool Fase::terminou() const {
    return concluida;
}

bool Fase::jogadorMorreu() const {
    return pJog1 && pJog1->getVidas() <= 0;
}
