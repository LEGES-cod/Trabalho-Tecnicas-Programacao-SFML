#include "Obstaculo.h"

Obstaculo::Obstaculo(const sf::Vector2f& posicao, const sf::Vector2f& tamanho, // Implementa o construtor, delegando os par�metros de constru��o diretamente para a classe base Entidade.
                     const sf::Color& cor, bool ehDanoso)
    : Entidade(posicao, tamanho, cor), danoso(ehDanoso) {}

void Obstaculo::executar() {} // Implementa o m�todo executar de forma vazia, uma vez que os obst�culos s�o est�ticos nesta vers�o.
