#include "GerenciadorColisoes.h"

bool GerenciadorColisoes::verificar(const Entidade& a, const Entidade& b) { //Implementa o método de verificação de colisãp. Obtem os limites espaciais das entidades e utiliza a função natida da SFML para ver se os retângulos estão se sobrepondo, retornando true ou false
    return a.getLimites().intersects(b.getLimites());
}
