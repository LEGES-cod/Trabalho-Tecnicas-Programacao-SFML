#include "Fase.h"
#include "BolaDeFogo.h"
#include "PlataformaEstatica.h"
#include "Demogorgon.h"
#include "Demodog.h"
#include "Vecna.h"
#include <cmath>

Fase::Fase(const std::string& caminhoFundo, const sf::Color& corChao)
    : Ente(), pJog1(nullptr), pJog2(nullptr), doisJogadores(false),
      concluida(false), exigirDerrotaInimigos(false),
      corChao(corChao), fonteHUDCarregada(false) {

    if (texturaFundo.loadFromFile(caminhoFundo)) {
        spriteFundo.setTexture(texturaFundo);
    }

    fonteHUDCarregada = fonteHUD.loadFromFile("arial.ttf");
    if (fonteHUDCarregada) {
        textoHUD.setFont(fonteHUD);
        textoHUD.setCharacterSize(20);
        textoHUD.setFillColor(sf::Color::White);
        textoHUD.setOutlineColor(sf::Color::Black);
        textoHUD.setOutlineThickness(2.f);
        textoHUD.setPosition(15.f, 12.f);

        textoHUD2.setFont(fonteHUD);
        textoHUD2.setCharacterSize(20);
        textoHUD2.setFillColor(sf::Color(120, 210, 255));
        textoHUD2.setOutlineColor(sf::Color::Black);
        textoHUD2.setOutlineThickness(2.f);
        textoHUD2.setPosition(615.f, 12.f);
    }
}

Fase::~Fase() {
    gColisoes.limpar();
    LEnts.limpar();
}

void Fase::inicializar() {
    pJog1 = new Jogador(1);

    LEnts.incluir(pJog1);
    gColisoes.setJogador(pJog1);

    adicionarChao(new Chao(
        sf::Vector2f(0.f, 535.f),
        sf::Vector2f(800.f, 65.f),
        corChao
    ));
}

void Fase::setPersonagem(int indice) {
    if (pJog1) {
        pJog1->setPersonagem(indice);
    }
}

void Fase::ativarSegundoJogador(int indicePersonagem) {
    if (pJog2) return;

    doisJogadores = true;
    pJog2 = new Jogador(2);
    pJog2->setPersonagem(indicePersonagem);

    LEnts.incluir(pJog2);
    gColisoes.setJogador2(pJog2);
}

Jogador* Fase::getJogadorMaisProximo(sf::Vector2f origem) const {
    bool j1Vivo = pJog1 && pJog1->estaVivo();
    bool j2Vivo = pJog2 && pJog2->estaVivo();

    if (j1Vivo && !j2Vivo) return pJog1;
    if (j2Vivo && !j1Vivo) return pJog2;
    if (!j1Vivo && !j2Vivo) return nullptr;

    float d1 = std::hypot(
        pJog1->getPosicao().x - origem.x,
        pJog1->getPosicao().y - origem.y
    );
    float d2 = std::hypot(
        pJog2->getPosicao().x - origem.x,
        pJog2->getPosicao().y - origem.y
    );

    return (d1 <= d2) ? pJog1 : pJog2;
}

void Fase::adicionarInimigo(Inimigo* inimigo) {
    if (inimigo) {
        inimigo->setJogador(pJog1);

        inimigos.push_back(inimigo);
        inimigoPontuado.push_back(false);
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

    for (Inimigo* inimigo : inimigos) {
        if (!inimigo || !inimigo->estaVivo()) continue;

        Jogador* alvo = getJogadorMaisProximo(inimigo->getPosicao());
        inimigo->setJogador(alvo);

        if (!alvo) continue;

        Demogorgon* demogorgon = dynamic_cast<Demogorgon*>(inimigo);

       if (demogorgon && demogorgon->consumirDisparo()) {
            sf::Vector2f origem = demogorgon->getPosicao();
            sf::Vector2f destino = alvo->getPosicao();

            origem.x += 17.f;
            origem.y += 24.f;
            destino.x += 20.f;
            destino.y += 18.f;

            float dx = destino.x - origem.x;
            float dy = destino.y - origem.y;
            float distancia = std::sqrt(dx * dx + dy * dy);

            if (distancia > 0.f) {
                const float velocidadeProjetil = 280.f;
                float vx = (dx / distancia) * velocidadeProjetil;
                float vy = (dy / distancia) * velocidadeProjetil;

                BolaDeFogo* projetilInimigo = new BolaDeFogo(
                    origem, vx, 3, sf::Color(180, 0, 180), vy
                );

                LEnts.incluir(projetilInimigo);
                gColisoes.incluirProjetil(projetilInimigo);
            }
        }

        Vecna* vecna = dynamic_cast<Vecna*>(inimigo);

       if (vecna && vecna->consumirAtaque()) {
            sf::Vector2f origem = vecna->getPosicao();
            float dir = (alvo->getPosicao().x >= origem.x) ? 1.f : -1.f;

            BolaDeFogo* projVecna = new BolaDeFogo(
                sf::Vector2f(origem.x + 18.f, origem.y + 26.f),
                320.f * dir,
                8,
                sf::Color::Red,
                0.f
            );

            LEnts.incluir(projVecna);
            gColisoes.incluirProjetil(projVecna);
        }
    }

    // Disparo do Jogador 1
    if (pJog1 && pJog1->estaVivo() && pJog1->consumirDisparo()) {
        sf::Vector2f posicao = pJog1->getPosicao();
        float direcao = pJog1->getDirecao();

        BolaDeFogo* bolaFogo = new BolaDeFogo(
            sf::Vector2f(
                direcao > 0 ? posicao.x + 40.f : posicao.x - 16.f,
                posicao.y + 12.f
            ),
            500.f * direcao,
            1,
            sf::Color(255, 100, 0)
        );

        LEnts.incluir(bolaFogo);
        gColisoes.incluirProjetilJogador(bolaFogo);
    }

    // Disparo do Jogador 2
    if (pJog2 && pJog2->estaVivo() && pJog2->consumirDisparo()) {
        sf::Vector2f posicao = pJog2->getPosicao();
        float direcao = pJog2->getDirecao();

        BolaDeFogo* bolaFogo2 = new BolaDeFogo(
            sf::Vector2f(
                direcao > 0 ? posicao.x + 40.f : posicao.x - 16.f,
                posicao.y + 12.f
            ),
            500.f * direcao,
            1,
            sf::Color(0, 180, 255)
        );

        LEnts.incluir(bolaFogo2);
        gColisoes.incluirProjetilJogador(bolaFogo2);
    }

    gColisoes.executar();

    if (pJog1) {
        for (size_t i = 0; i < inimigos.size(); i++) {
            if (inimigos[i] && !inimigos[i]->estaVivo() && !inimigoPontuado[i]) {
                inimigoPontuado[i] = true;

                if (dynamic_cast<Vecna*>(inimigos[i])) {
                    pJog1->adicionarPontos(300);
                }
                else if (dynamic_cast<Demogorgon*>(inimigos[i])) {
                    pJog1->adicionarPontos(200);
                }
                else {
                    pJog1->adicionarPontos(100);
                }
            }
        }
    }

    desenharHUD();

    bool j1Chegou = pJog1 && pJog1->estaVivo() && pJog1->getPosicao().x > 735.f;
    bool j2Chegou = pJog2 && pJog2->estaVivo() && pJog2->getPosicao().x > 735.f;

    if (j1Chegou || j2Chegou) {
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

    if (texturaFundo.getSize().x > 0 &&
        texturaFundo.getSize().y > 0) {

        float escalaX =
            static_cast<float>(pGG->getJanela().getSize().x) /
            texturaFundo.getSize().x;

        float escalaY =
            static_cast<float>(pGG->getJanela().getSize().y) /
            texturaFundo.getSize().y;

        spriteFundo.setScale(escalaX, escalaY);
    }

    pGG->desenharElemento(spriteFundo);
}

void Fase::desenharHUD() {
    if (!pGG || !fonteHUDCarregada || !pJog1) return;

    std::string prefixoJ1 = doisJogadores ? "J1 Vidas: " : "Vidas: ";
    textoHUD.setString(
        prefixoJ1 + std::to_string(pJog1->getVidas()) +
        "   |   Pontos: " + std::to_string(pJog1->getPontos())
    );
    pGG->desenharElemento(textoHUD);

    if (doisJogadores && pJog2) {
        textoHUD2.setString("J2 Vidas: " + std::to_string(pJog2->getVidas()));
        pGG->desenharElemento(textoHUD2);
    }
}

bool Fase::terminou() const {
    return concluida;
}

bool Fase::jogadorMorreu() const {
    bool j1Morto = !pJog1 || !pJog1->estaVivo();
    if (!doisJogadores) {
        return j1Morto;
    }

    bool j2Morto = !pJog2 || !pJog2->estaVivo();
    return j1Morto && j2Morto;
}

int Fase::getPontosJogador() const {
    return pJog1 ? pJog1->getPontos() : 0;
}

void Fase::setPontosJogador(int pontos) {
    if (pJog1 && pontos > 0) {
        pJog1->adicionarPontos(pontos);
    }
}
