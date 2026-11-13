#include <SFML/Graphics.hpp>
#include "GerenciadorGrafico.h"
#include "FaseHawkins.h"
#include "FaseMundoInvertido.h"

int main() {
    GerenciadorGrafico& grafico = GerenciadorGrafico::getInstancia(); //Obtém a referência para a instância única do gestor gráfico
    sf::Clock relogio; //Cria um relógio da SFML para medir o tempo decorrido entre os frames.
    FaseHawkins hawkins; //Instancia os dois níveis/fases do jogo.
    FaseMundoInvertido mundoInvertido;
    Fase* faseAtual = &hawkins; //Define um ponteiro para apontar inicialmente para a fase de Hawkins
    bool segundaFase = false; //Variável de controle para verificar se o jogo já avançou para a segunda fase.

    while (grafico.janelaAberta()) { //Ciclo principal do jogo, executado enquanto a janela estiver aberta.
        sf::Event evento; //Declara uma estrutura para armazenar eventos de sistema.
        while (grafico.getJanela().pollEvent(evento)) { //Recolhe todos os eventos pendentes na fila da janela
            if (evento.type == sf::Event::Closed) grafico.fechar(); //Se o utilizador clicar no "X" da janela, o comando de fechar é acionado.
        }

        float deltaTime = relogio.restart().asSeconds(); //Reinicia o relógio e guarda o tempo decorrido no frame atual convertido em segundos
        grafico.limpar(); //Limpa o conteúdo visual do frame anterior.
        faseAtual->executar(deltaTime, grafico.getJanela()); //Executa a lógica, colisões e renderização da fase ativa atual

        if (faseAtual->terminou() && !segundaFase) { //Gestão de transição de fases: se a fase atual terminou e ainda não está na segunda fase, muda o ponteiro faseAtual para o mundoInvertido e ativa a flag; se a segunda fase também terminar, fecha o jogo.
            faseAtual = &mundoInvertido;
            segundaFase = true;
        } else if (faseAtual->terminou() && segundaFase) {
            grafico.fechar();
        }
        grafico.mostrar(); //Apresenta no ecrã o resultado renderizado do frame atual (display).
    }
    return 0; //Termina o programa
}
