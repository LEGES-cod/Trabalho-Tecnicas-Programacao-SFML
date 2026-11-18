#include "GerenciadorColisoes.h"

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

void GerenciadorColisoes::incluirProjetil(Projetil* pj) {
    if (pj) LPs.insert(pj);
}

void GerenciadorColisoes::incluirProjetilJogador(Projetil* pj) {
    if (pj) projeteisJogador.insert(pj);
}

void GerenciadorColisoes::limpar() {
    LIs.clear();
    LOs.clear();
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
        if (verificarColisao(pJog1, obstaculo)) {
            obstaculo->obstacular(pJog1);
        }
    }
}

void GerenciadorColisoes::tratarColisoesJogsInimgs() {
    if (!pJog1) return;

    for (auto* inimigo : LIs) {
        if (inimigo->estaVivo() &&
            verificarColisao(pJog1, inimigo)) {

            pJog1->receberDano(inimigo->getDano());
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

void GerenciadorColisoes::tratarColisoesProjeteisInimgs() {
    for (auto* projetil : projeteisJogador) {
        if (!projetil->getAtivo()) continue;

        for (auto* inimigo : LIs) {
            if (!inimigo->estaVivo()) continue;

            if (verificarColisao(projetil, inimigo)) {
                inimigo->receberDano(projetil->getDano());
                projetil->desativar();

                if(!inimigo->estaVivo() &&pJog1)
                {
                    pJog1->adicionarPontos(inimigo->getPontos());
                }
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
                } else {
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
    tratarColisoesJogsInimgs();
    tratarColisoesJogsProjeteis();
    tratarColisoesProjeteisInimgs();
    tratarColisoesInimgsObstacs();
}
