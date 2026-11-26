#include "GerenciadorColisoes.h"
#include "Demogorgon.h"
#include "PlataformaEstatica.h"
#include <cmath>

GerenciadorColisoes::GerenciadorColisoes()
    : pJog1(nullptr), pJog2(nullptr) {}

GerenciadorColisoes::~GerenciadorColisoes() {
    limpar();
}

void GerenciadorColisoes::setJogador(Jogador* pJ) {
    pJog1 = pJ;
}

void GerenciadorColisoes::setJogador2(Jogador* pJ) {
    pJog2 = pJ;
}

void GerenciadorColisoes::incluirInimigo(Inimigo* pi) {
    if (pi) LIs.push_back(pi);
}

void GerenciadorColisoes::incluirObstaculo(Obstaculo* po) {
    if (po) LOs.push_back(po);
}

void GerenciadorColisoes::incluirChao(Chao* pc) {
    if (pc) LCs.push_back(pc);
}

void GerenciadorColisoes::incluirProjetil(BolaDeFogo* pj) {
    if (pj) LPs.insert(pj);
}

void GerenciadorColisoes::incluirProjetilJogador(BolaDeFogo* pj) {
    if (pj) projeteisJogador.insert(pj);
}

void GerenciadorColisoes::limpar() {
    LIs.clear();
    LOs.clear();
    LCs.clear();
    LPs.clear();
    projeteisJogador.clear();
    pJog1 = nullptr;
    pJog2 = nullptr;
}

const bool GerenciadorColisoes::verificarColisao(
    Entidade* pe1, Entidade* pe2) const {

    if (!pe1 || !pe2) return false;

    return pe1->getLimites().intersects(pe2->getLimites());
}

// Verifica obstaculos para os dois jogadores ativos
void GerenciadorColisoes::tratarColisoesJogsObstacs() {
    Jogador* jogadores[2] = { pJog1, pJog2 };

    for (Jogador* jog : jogadores) {
        if (!jog || !jog->estaVivo()) continue;

        for (auto* obstaculo : LOs) {
            if (dynamic_cast<PlataformaEstatica*>(obstaculo)) {
                obstaculo->obstacular(jog);
            }
            else if (verificarColisao(jog, obstaculo)) {
                obstaculo->obstacular(jog);
            }
        }
    }
}

void GerenciadorColisoes::tratarColisoesJogsChao() {
    Jogador* jogadores[2] = { pJog1, pJog2 };

    for (Jogador* jog : jogadores) {
        if (!jog || !jog->estaVivo()) continue;

        for (auto* chao : LCs) {
            if (verificarColisao(jog, chao)) {
                chao->colidir(jog);
            }
        }
    }
}

void GerenciadorColisoes::tratarColisoesJogsInimgs() {
    Jogador* jogadores[2] = { pJog1, pJog2 };

    for (Jogador* jog : jogadores) {
        if (!jog || !jog->estaVivo()) continue;

        for (auto* inimigo : LIs) {
            if (inimigo->estaVivo() &&
                verificarColisao(jog, inimigo)) {

                if (dynamic_cast<Demogorgon*>(inimigo)) {
                    jog->iniciarDanoContinuo();
                }
                else {
                    jog->receberDano(inimigo->getDano());
                }
            }
        }
    }
}

void GerenciadorColisoes::tratarColisoesJogsProjeteis() {
    Jogador* jogadores[2] = { pJog1, pJog2 };

    for (Jogador* jog : jogadores) {
        if (!jog || !jog->estaVivo()) continue;

        for (auto* projetil : LPs) {
            if (projetil->getAtivo() &&
                verificarColisao(jog, projetil)) {

                jog->receberDano(projetil->getDano());
                projetil->desativar();
            }
        }
    }
}

void GerenciadorColisoes::tratarColisoesProjeteisObstacs() {
    for (auto* projetil : projeteisJogador) {
        if (!projetil->getAtivo()) continue;

        for (auto* obstaculo : LOs) {
            if (!obstaculo || !obstaculo->podeColidir()) continue;

            if (verificarColisao(projetil, obstaculo)) {
                projetil->desativar();
                break;
            }
        }
    }

    for (auto* projetil : LPs) {
        if (!projetil->getAtivo()) continue;

        for (auto* obstaculo : LOs) {
            if (!obstaculo || !obstaculo->podeColidir()) continue;

            if (dynamic_cast<PlataformaEstatica*>(obstaculo)) {
                if (verificarColisao(projetil, obstaculo)) {
                    projetil->desativar();
                    break;
                }
            }
        }
    }
}

void GerenciadorColisoes::tratarColisoesProjeteisInimgs() {
    for (auto* projetil : projeteisJogador) {
        if (!projetil->getAtivo()) continue;

        for (auto* inimigo : LIs) {
            if (!inimigo->estaVivo()) continue;

            if (verificarColisao(projetil, inimigo)) {
                inimigo->receberDano(projetil->getDano());
                projetil->desativar();
                break;
            }
        }
    }
}

void GerenciadorColisoes::tratarColisoesInimgsObstacs() {
    for (auto* inimigo : LIs) {
        if (!inimigo->estaVivo()) continue;

        for (auto* obstaculo : LOs) {
            if (verificarColisao(inimigo, obstaculo)) {
                sf::FloatRect limitesIni = inimigo->getLimites();
                sf::FloatRect limitesObs = obstaculo->getLimites();

                if (dynamic_cast<PlataformaEstatica*>(obstaculo) &&
                    limitesIni.top + limitesIni.height <= limitesObs.top + 15.f) {

                    float posY = limitesObs.top - limitesIni.height;
                    float posX = limitesIni.left;

                    if (posX < limitesObs.left) {
                        posX = limitesObs.left;
                        inimigo->inverterDirecao();
                    } else if (posX + limitesIni.width > limitesObs.left + limitesObs.width) {
                        posX = limitesObs.left + limitesObs.width - limitesIni.width;
                        inimigo->inverterDirecao();
                    }

                    inimigo->setPosicao(sf::Vector2f(posX, posY));
                    inimigo->aterrar(posY);
                    continue;
                }

                if (limitesIni.left < limitesObs.left) {
                    inimigo->setPosicao(sf::Vector2f(
                        limitesObs.left - limitesIni.width,
                        limitesIni.top
                    ));
                } else {
                    inimigo->setPosicao(sf::Vector2f(
                        limitesObs.left + limitesObs.width,
                        limitesIni.top
                    ));
                }

                inimigo->inverterDirecao();
            }
        }
    }
}

void GerenciadorColisoes::tratarColisoesInimgsChao() {
    for (auto* inimigo : LIs) {
        if (!inimigo->estaVivo()) continue;

        for (auto* chao : LCs) {
            if (verificarColisao(inimigo, chao)) {
                sf::FloatRect rectIni = inimigo->getLimites();
                sf::FloatRect rectChao = chao->getLimites();
                inimigo->aterrar(rectChao.top - rectIni.height);
            }
        }
    }
}

void GerenciadorColisoes::executar() {
    tratarColisoesJogsObstacs();
    tratarColisoesJogsChao();
    tratarColisoesJogsInimgs();
    tratarColisoesProjeteisObstacs();
    tratarColisoesJogsProjeteis();
    tratarColisoesProjeteisInimgs();
    tratarColisoesInimgsObstacs();
    tratarColisoesInimgsChao();
}
