#include "Fase.h"

Fase::Fase(const std::string& caminhoFundo)
    : Ente(), pJog1(nullptr), concluida(false) { // Construtor da classe Fase. Inicializa concluida como falso
    if (texturaFundo.loadFromFile(caminhoFundo)) {
        spriteFundo.setTexture(texturaFundo); // Construtor carrega a imagem passada por parâmetro
    }
    chao.setSize(sf::Vector2f(800.f, 100.f)); // Config do chão e as dimensões
    chao.setPosition(0.f, 530.f);
    chao.setFillColor(sf::Color(35, 35, 35)); // Cor cinza do chão
}

Fase::~Fase() {
    gColisoes.limpar();
    LEnts.limpar();
}

void Fase::inicializar() { // Instancia o jogador e povoa a fase
    pJog1 = new Jogador();
    LEnts.incluir(pJog1);
    gColisoes.setJogador(pJog1);

    criarInimigos();
    criarObstaculos();
}

void Fase::adicionarInimigo(Inimigo* inimigo) { // Adiciona um inimigo na ListaEntidades e no GerenciadorColisoes
    if (inimigo) {
        inimigo->setJogador(pJog1);
        LEnts.incluir(inimigo);
        gColisoes.incluirInimigo(inimigo);
    }
}

void Fase::adicionarObstaculo(Obstaculo* obstaculo) { // Faz o mesmo procedimento para os obstáculos
    if (obstaculo) {
        LEnts.incluir(obstaculo);
        gColisoes.incluirObstaculo(obstaculo);
    }
}

void Fase::executar() { // Inicia o método de execução do loop da fase
    desenhar();
    LEnts.percorrer();
    gColisoes.executar();

    if (pJog1 && pJog1->getPosicao().x > 750.f) {
        concluida = true; // Se o jogador passar a coordenada X de 750 pixels, a fase é dada como concluída
    }
}

void Fase::desenhar() { // Desenha o fundo e o chão através do GerenciadorGrafico
    if (!pGG) return;

    if (texturaFundo.getSize().x > 0 && texturaFundo.getSize().y > 0) {
        float escalaX = static_cast<float>(pGG->getJanela().getSize().x) / texturaFundo.getSize().x; // Ajusta o tamanho da imagem de fundo para preencher toda a janela
        float escalaY = static_cast<float>(pGG->getJanela().getSize().y) / texturaFundo.getSize().y;
        spriteFundo.setScale(escalaX, escalaY);
    }

    pGG->desenharElemento(spriteFundo); // Desenha o fundo PRIMEIRO para que tudo fique por cima dele
    pGG->desenharElemento(chao);
}

bool Fase::terminou() const { return concluida; } // Retorna o valor da variável concluída
