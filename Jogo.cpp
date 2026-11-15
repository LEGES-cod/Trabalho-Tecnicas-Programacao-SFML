#include "Jogo.h"

Jogo::Jogo()
    : pGG(GerenciadorGrafico::getInstancia()), faseAtual(nullptr), segundaFase(false) {
    Ente::setGG(pGG);
}

Jogo::~Jogo() {
    delete faseAtual;
}

void Jogo::executar() { // Ciclo principal do jogo, executado enquanto a janela estiver aberta
    while (pGG->janelaAberta()) {
        sf::Event evento; // Declara uma estrutura para armazenar eventos de sistema
        while (pGG->getJanela().pollEvent(evento)) { // Recolhe todos os eventos pendentes na fila da janela
            if (evento.type == sf::Event::Closed) pGG->fechar(); // Se o utilizador clicar no "X" da janela, o comando de fechar é acionado
        }

        pGG->atualizarDeltaTime(); // Reinicia o relógio e guarda o tempo decorrido no frame atual
        pGG->limpar();             // Limpa o conteúdo visual do frame anterior

        if (menu.estaAtivo()) {
            menu.executar();
            if (!menu.estaAtivo()) {
                if (menu.getOpcaoSelecionada() == 1) {
                    faseAtual = new FaseHawkins();
                    segundaFase = false;
                } else {
                    faseAtual = new FaseMundoInvertido();
                    segundaFase = true;
                }
            }
        } else if (faseAtual != nullptr) {
            faseAtual->executar(); // Executa a lógica, colisões e renderização da fase ativa atual

            if (faseAtual->terminou() && !segundaFase) { // Gestão de transição de fases
                delete faseAtual;
                faseAtual = new FaseMundoInvertido();
                segundaFase = true;
            } else if (faseAtual->terminou() && segundaFase) {
                pGG->fechar();
            }
        }

        pGG->mostrar(); // Apresenta no ecrã o resultado renderizado do frame atual (display)
    }
}
