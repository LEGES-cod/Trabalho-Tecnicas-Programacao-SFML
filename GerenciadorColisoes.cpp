#include "GerenciadorColisoes.h"
#include "Demogorgon.h"
#include "PlataformaEstatica.h"
#include <cmath>

GerenciadorColisoes::GerenciadorColisoes()
    : pJog1(nullptr) {}

GerenciadorColisoes::~GerenciadorColisoes() {
    limpar();
}

void GerenciadorColisoes::setJogador(Jogador* pJ) {
    pJog1 = pJ;
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
}

const bool GerenciadorColisoes::verificarColisao(
    Entidade* pe1, Entidade* pe2) const {

    if (!pe1 || !pe2) return false;

    return pe1->getLimites().intersects(pe2->getLimites());
}

void GerenciadorColisoes::tratarColisoesJogsObstacs() {
    if (!pJog1) return;

    for (auto* obstaculo : LOs) {

        // A plataforma estatica precisa ser verificada
        // mesmo quando o jogador apenas encosta nela.
        if (dynamic_cast<PlataformaEstatica*>(obstaculo)) {
            obstaculo->obstacular(pJog1);
        }
        else if (verificarColisao(pJog1, obstaculo)) {
            obstaculo->obstacular(pJog1);
        }
    }
}

void GerenciadorColisoes::tratarColisoesJogsChao() {
    if (!pJog1) return;

    for (auto* chao : LCs) {
        if (verificarColisao(pJog1, chao)) {
            chao->colidir(pJog1);
        }
    }
}

void GerenciadorColisoes::tratarColisoesJogsInimgs() {
    if (!pJog1) return;

    for (auto* inimigo : LIs) {
        if (inimigo->estaVivo() &&
            verificarColisao(pJog1, inimigo)) {

            if (dynamic_cast<Demogorgon*>(inimigo)) {
                pJog1->iniciarDanoContinuo();
            }
            else {
                pJog1->receberDano(inimigo->getDano());
            }
        }
    }
}

void GerenciadorColisoes::tratarColisoesJogsProjeteis() {
    if (!pJog1) return;

    for (auto* projetil : LPs) {
        if (projetil->getAtivo() &&
            verificarColisao(pJog1, projetil)) {

            pJog1->receberDano(projetil->getDano());
            projetil->desativar();
        }
    }
}


void GerenciadorColisoes::tratarColisoesProjeteisObstacs() {

    for (auto* projetil : projeteisJogador) {
        if (!projetil->getAtivo()) continue;

        for (auto* obstaculo : LOs) {

            if (verificarColisao(projetil, obstaculo)) {
                projetil->desativar();
                break;
            }
        }
    }

    // Mantém a colisão dos projéteis inimigos
    // com as plataformas estáticas.
    for (auto* projetil : LPs) {
        if (!projetil->getAtivo()) continue;

        for (auto* obstaculo : LOs) {

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

                if (limitesIni.left < limitesObs.left) {
                    inimigo->setPosicao(
                        sf::Vector2f(
                            limitesObs.left - limitesIni.width,
                            limitesIni.top
                        )
                    );
                }
                else {
                    inimigo->setPosicao(
                        sf::Vector2f(
                            limitesObs.left + limitesObs.width,
                            limitesIni.top
                        )
                    );
                }

                inimigo->inverterDirecao();
            }
        }
    }
}

void GerenciadorColisoes::executar() {
    tratarColisoesJogsObstacs();
    tratarColisoesJogsChao();
    tratarColisoesJogsInimgs();

    // Impede que os projéteis inimigos atravessem plataformas.
    tratarColisoesProjeteisObstacs();

    tratarColisoesJogsProjeteis();
    tratarColisoesProjeteisInimgs();
    tratarColisoesInimgsObstacs();
}
