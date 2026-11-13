#include "Fase.h"

Fase::Fase(const std::string& caminhoFundo) : concluida(false), jogador(std::make_unique<Jogador>()) { //Construtor da classe Fase. Inicializa concluida como falso e instancia o jogador usando std::make_unique.
    if (texturaFundo.loadFromFile(caminhoFundo)) {
        spriteFundo.setTexture(texturaFundo); //Construtor agora carrega a imagem passada por parâmetro
    }
    chao.setSize(sf::Vector2f(800.f, 100.f)); // config do chão e as dimensoes
    chao.setPosition(0.f, 530.f);
    chao.setFillColor(sf::Color(35, 35, 35)); // cor cinza do chao
}

void Fase::adicionarInimigo(std::unique_ptr<Inimigo> inimigo) { //Adiciona um inimigo, guarda o ponteiro no vetor Inimigos e transfere a posse do ponteiro inteligente para o vetor geral
    inimigos.push_back(inimigo.get());
    objetos.push_back(std::move(inimigo));
}

void Fase::adicionarObstaculo(std::unique_ptr<Obstaculo> obstaculo) { //Faz o mesmo procedimento para os obstáculos, registando-os no vetor de obstáculos e transferindo a posse para o vetor objetos
    obstaculos.push_back(obstaculo.get());
    objetos.push_back(std::move(obstaculo));
}

void Fase::executar(float deltaTime, sf::RenderWindow& janela) { //Inicia o métode de execução do loop da fase

    if (texturaFundo.getSize().x > 0 && texturaFundo.getSize().y > 0) {
        float escalaX = static_cast<float>(janela.getSize().x) / texturaFundo.getSize().x; // Ajusta o tamanho da imagem de fundo para preencher toda a janela[cite: 32]
        float escalaY = static_cast<float>(janela.getSize().y) / texturaFundo.getSize().y;
        spriteFundo.setScale(escalaX, escalaY);
    }

    janela.draw(spriteFundo); //Desenha o fundo PRIMEIRO para que tudo fique por cima dele
    janela.draw(chao);

    jogador->executar(deltaTime); //Atualiza a lógica do jogador com base no tempo decorrido
    for (auto& objeto : objetos) objeto->executar(deltaTime); //Percorre todos os objetos da fase, chamando a atualização lógica que os ppertence

    // Colisão inteligente com Obstáculos (Tronco)
    for (auto* obstaculo : obstaculos) {
        if (GerenciadorColisoes::verificar(*jogador, *obstaculo)) {
            sf::FloatRect rectJogador = jogador->getLimites();   // Caixa delimitadora do jogador
            sf::FloatRect rectObstaculo = obstaculo->getLimites(); // Caixa delimitadora do tronco

            // 1. Aterragem no topo do tronco (se o jogador estiver caindo e vindo de cima)
            if (jogador->getVelocidadeY() > 0.f &&
                (rectJogador.top + rectJogador.height - jogador->getVelocidadeY() * deltaTime) <= rectObstaculo.top + 10.f) {
                jogador->aterrar(rectObstaculo.top - rectJogador.height);
            }
            // 2. Bloqueio lateral esquerdo (indo para a direita contra o tronco)
            else if (rectJogador.left < rectObstaculo.left) {
                jogador->setPosicao(sf::Vector2f(rectObstaculo.left - rectJogador.width, rectJogador.top));
            }
            // 3. Bloqueio lateral direito (indo para a esquerda contra o tronco)
            else if (rectJogador.left > rectObstaculo.left) {
                jogador->setPosicao(sf::Vector2f(rectObstaculo.left + rectObstaculo.width, rectJogador.top));
            }
        }
    }

    for (auto* inimigo : inimigos) { //Verifica colisões entre o jogador e cada inimigo
       inimigo->executar(deltaTime, jogador->getPosicao());
       if(GerenciadorColisoes::verificar(*jogador, *inimigo))
       {
           jogador->receberDano(inimigo->getDano());
       }
       for(auto* obstaculo : obstaculos)
       {
           if (GerenciadorColisoes::verificar(*inimigo, *obstaculo))
           {
               sf::FloatRect limitesIni = inimigo->getLimites();
               sf::FloatRect limitesObs = obstaculo->getLimites();
               if(limitesIni.left < limitesObs.left)
               {
                   inimigo->setPosicao(sf::Vector2f(limitesObs.left - limitesIni.width, limitesIni.top));
               }
               else{
                inimigo->setPosicao(sf::Vector2f(limitesObs.left + limitesObs.width, limitesIni.top));
               }
               inimigo->inverterDirecao();
           }
       }
       if (GerenciadorColisoes::verificar(*jogador, *inimigo)) {
        // Tratar o toque no inimigo
    }
    }

    if (jogador->getPosicao().x > 750.f) concluida = true; //Se o jogador passar a coordenada X de 750 pixels, a fase é dada como concluída

    for (auto& objeto : objetos) objeto->desenhar(janela);  //Desenha todos os objetos na janela do jogo
    jogador->desenhar(janela); //Desenha o jogador por cima dos outros elementos
}

bool Fase::terminou() const { return concluida; } //Retorna o valor da variável concluída
