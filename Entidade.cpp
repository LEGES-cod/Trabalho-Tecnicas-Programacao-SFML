#include "Entidade.h"
#include <iostream>

using namespace std;

Entidade::Entidade() {
    x = 0.0f;
    y = 0.0f;
}

Entidade::~Entidade() {
}

void Entidade::salvar() {
    cout << "Salvando entidade..." << endl;
}
