#include "FaseHawkins.h"
#include "Demogorgon.h"
#include "Demodog.h"
#include "TroncoCaido.h"
#include "PlataformaEstatica.h"
#include <cstdlib>

FaseHawkins::FaseHawkins() : Fase("hawkins.png", sf::Color(40, 50, 35)) {
    exigirDerrotaInimigos = true;

    inicializar();

    // 1. Plataformas formando 4 andares exploráveis (6 a 8 instâncias aleatórias)
    int qtdPlataformas = 6 + (std::rand() % 3); // 6, 7 ou 8 plataformas
    sf::Vector2f posPlat[8] = {
        // Andar 1 (Y = 445) - Entrada e corredor direito
        sf::Vector2f(95.f,  445.f),
        sf::Vector2f(430.f, 445.f),
        // Andar 2 (Y = 355) - Esquerda, centro e direita
        sf::Vector2f(25.f,  355.f),
        sf::Vector2f(255.f, 355.f),
        sf::Vector2f(620.f, 355.f),
        // Andar 3 (Y = 265) - Pontes superiores
        sf::Vector2f(135.f, 265.f),
        sf::Vector2f(455.f, 265.f),
        // Andar 4 (Y = 165) - Topo central mais alto e afastado à esquerda para abrir o vão
        sf::Vector2f(275.f, 165.f)
    };
    sf::Vector2f tamPlat[8] = {
        sf::Vector2f(155.f, 16.f),
        sf::Vector2f(195.f, 16.f),
        sf::Vector2f(145.f, 16.f),
        sf::Vector2f(180.f, 16.f),
        sf::Vector2f(155.f, 16.f),
        sf::Vector2f(160.f, 16.f),
        sf::Vector2f(185.f, 16.f),
        sf::Vector2f(170.f, 16.f)
    };

    for (int i = 0; i < qtdPlataformas; i++) {
        adicionarObstaculo(new PlataformaEstatica(posPlat[i], tamPlat[i]));
    }

    // 2. Troncos no chão e em cima das plataformas (3 a 5 instâncias)
    criarTroncosCaidos();

    // 3. Demodogs patrulhando o chão e plataformas largas (3 a 4 instâncias)
    criarDemodog();

    // 4. Demogorgons guardando os andares superiores (3 a 4 instâncias)
    int qtdDemogorgons = 3 + (std::rand() % 2);
    sf::Vector2f posDemo[4] = {
        sf::Vector2f(55.f,  295.f), // Andar 2 (esquerda)
        sf::Vector2f(700.f, 295.f), // Andar 2 (direita)
        sf::Vector2f(575.f, 205.f), // Andar 3 (direita)
        sf::Vector2f(340.f, 105.f)  // Andar 4 (topo central)
    };
    for (int i = 0; i < qtdDemogorgons; i++) {
        adicionarInimigo(new Demogorgon(posDemo[i], pJog1));
    }
}

void FaseHawkins::criarDemodog() {
    int qtd = 3 + (std::rand() % 2);
    sf::Vector2f posDog[4] = {
        sf::Vector2f(340.f, 480.f), // Chão (centro)
        sf::Vector2f(620.f, 480.f), // Chão (direita)
        sf::Vector2f(470.f, 390.f), // Em cima da plataforma larga do Andar 1
        sf::Vector2f(310.f, 300.f)  // Em cima da plataforma central do Andar 2
    };
    for (int i = 0; i < qtd; i++) {
        adicionarInimigo(new Demodog(posDog[i], pJog1));
    }
}

void FaseHawkins::criarTroncosCaidos() {
    int qtd = 3 + (std::rand() % 3); // 3, 4 ou 5 troncos
    sf::Vector2f posTronco[5] = {
        sf::Vector2f(210.f, 517.f), // Chão (esquerda)
        sf::Vector2f(540.f, 517.f), // Chão (direita)
        sf::Vector2f(555.f, 427.f), // Em cima da plataforma do Andar 1 (445 - 18)
        sf::Vector2f(315.f, 337.f), // Mais à direita na plataforma central do Andar 2
        sf::Vector2f(505.f, 247.f)  // Mais à direita na plataforma do Andar 3, abrindo o vão
    };
    for (int i = 0; i < qtd; i++) {
        adicionarObstaculo(new TroncoCaido(posTronco[i]));
    }
}
