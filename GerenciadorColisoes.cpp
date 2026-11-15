#include "GerenciadorColisoes.h"

GerenciadorColisoes::GerenciadorColisoes() : pJog1(nullptr) {}

GerenciadorColisoes::~GerenciadorColisoes() {
    limpar();
}

void GerenciadorColisoes::setJogador(Jogador* pJ) { // Associa o jogador ao gerenciador
    pJog1 = pJ;
}

void GerenciadorColisoes::incluirInimigo(Inimigo* pi) { // Adiciona inimigo ao std::vector
    if (pi) LIs.push_back(pi);
}

void GerenciadorColisoes::incluirObstaculo(Obstaculo* po) { // Adiciona obstáculo à std::list
    if (po) LOs.push_back(po);
}

void GerenciadorColisoes::incluirProjetil(Projetil* pj) { // Adiciona projétil ao std::set
    if (pj) LPs.insert(pj);
}

void GerenciadorColisoes::limpar() { // Limpa as referências armazenadas (a desalocação ocorre na ListaEntidades)
    LIs.clear();
    LOs.clear();
    LPs.clear();
    pJog1 = nullptr;
}

const bool GerenciadorColisoes::verificarColisao(Entidade* pe1, Entidade* pe2) const { // Verifica se os retângulos estão se sobrepondo
    if (!pe1 || !pe2) return false;
    return pe1->getLimites().intersects(pe2->getLimites());
}

void GerenciadorColisoes::tratarColisoesJogsObstacs() { // Colisão entre jogador e obstáculos (Tronco, Plataforma, Espinhos)
    if (!pJog1) return;

    for (auto* obstaculo : LOs) {
        if (verificarColisao(pJog1, obstaculo)) {
            obstaculo->obstacular(pJog1);
        }
    }
}

void GerenciadorColisoes::tratarColisoesJogsInimgs() { // Verifica colisões entre o jogador e cada inimigo
    if (!pJog1) return;

    for (auto* inimigo : LIs) {
        if (verificarColisao(pJog1, inimigo)) {
            pJog1->receberDano(inimigo->getDano());
        }
    }
}

void GerenciadorColisoes::tratarColisoesJogsProjeteis() { // Verifica colisões entre o jogador e projéteis
    if (!pJog1) return;

    for (auto* projetil : LPs) {
        if (projetil->getAtivo() && verificarColisao(pJog1, projetil)) {
            pJog1->receberDano(projetil->getDano());
            projetil->desativar();
        }
    }
}

void GerenciadorColisoes::tratarColisoesInimgsObstacs() { // Verifica colisões entre inimigos e obstáculos
    for (auto* inimigo : LIs) {
        for (auto* obstaculo : LOs) {
            if (verificarColisao(inimigo, obstaculo)) {
                sf::FloatRect limitesIni = inimigo->getLimites();
                sf::FloatRect limitesObs = obstaculo->getLimites();

                if (limitesIni.left < limitesObs.left) {
                    inimigo->setPosicao(sf::Vector2f(limitesObs.left - limitesIni.width, limitesIni.top));
                } else {
                    inimigo->setPosicao(sf::Vector2f(limitesObs.left + limitesObs.width, limitesIni.top));
                }
                inimigo->inverterDirecao();
            }
        }
    }
}

void GerenciadorColisoes::executar() { // Executa todas as rotinas de colisão do frame
    tratarColisoesJogsObstacs();
    tratarColisoesJogsInimgs();
    tratarColisoesJogsProjeteis();
    tratarColisoesInimgsObstacs();
}
