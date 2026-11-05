#include "Fase.h"

Fase::Fase() : concluida(false), jogador(std::make_unique<Jogador>()) {} //Construtor da classe Fase. Inicializa concluida como falso e instancia o jogador usando std::make_unique.
void Fase::adicionarInimigo(std::unique_ptr<Inimigo> inimigo) { //Adiciona um inimigo, guarda o ponteiro no vetor Inimigos e transfere a posse do ponteiro inteligente para o vetor geral
    inimigos.push_back(inimigo.get());
    objetos.push_back(std::move(inimigo));
}
void Fase::adicionarObstaculo(std::unique_ptr<Obstaculo> obstaculo) { //Faz o mesmo procedimento para os obstáculos, registando-os no vetor de obstáculos e transferindo a posse para o vetor objetos
    obstaculos.push_back(obstaculo.get());
    objetos.push_back(std::move(obstaculo));
}
void Fase::executar(float deltaTime, sf::RenderWindow& janela) { //Inicia o métode de execução do loop da fase
    jogador->executar(deltaTime); //Atualiza a lógica do jogador com base no tempo decorrido
    for (auto& objeto : objetos) objeto->executar(deltaTime); //Percorre todos os objetos da fase, chamando a atualização lógica que os ppertence

    for (auto* obstaculo : obstaculos) { //Verifica colisões entre o jogador e cada obstáculo
        if (GerenciadorColisoes::verificar(*jogador, *obstaculo)) {
            sf::Vector2f p = jogador->getPosicao();
            p.y = 500.f;
            jogador->setPosicao(p);
        }
    }
    for (auto* inimigo : inimigos) { //Verifica colisões entre o jogador e cada inimigo. Se colidirem, o jogador perde uma vida e é colocado em uma posição inicial. Se as vidas chegarem a zero, a fase é marcada como concluída/derrota
        if (GerenciadorColisoes::verificar(*jogador, *inimigo)) {
            jogador->perderVida();
            jogador->setPosicao(sf::Vector2f(80.f, 500.f));
            if (jogador->getVidas() == 0) concluida = true;
        }
    }
    if (jogador->getPosicao().x > 750.f) concluida = true; //Se o jogador passar a coorddenada X de 750 pixels, a fase é dada como concluída

    for (auto& objeto : objetos) objeto->desenhar(janela);  //Desenha todos os objetos na janela do jogo
    jogador->desenhar(janela); //Desenha o jogador por cima dos outros elementos
}
bool Fase::terminou() const { return concluida; } //Retorna o valor da variável concluída
