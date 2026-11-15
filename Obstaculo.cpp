#include "Obstaculo.h"

Obstaculo::Obstaculo(const sf::Vector2f& posicao, const sf::Vector2f& tamanho, // Implementa o construtor, delegando os parâmetros de construção diretamente para a classe base Entidade.
                     const sf::Color& cor, bool ehDanoso)
    : Entidade(posicao, tamanho, cor), danoso(ehDanoso) {}

void Obstaculo::executar() {} // Implementa o método executar de forma vazia, uma vez que os obstáculos são estáticos nesta versão.
