#ifndef LISTA_H
#define LISTA_H

template <class TL>
class Lista { // Declara a classe template de lista simplesmente encadeada
public:
    template <class TE>
    class Elemento { // Declara a classe interna que representa cada nó da lista
    private:
        Elemento<TE>* pProx; // Ponteiro para o próximo elemento
        TE* pInfo;           // Ponteiro para a informação armazenada

    public:
        Elemento() : pProx(nullptr), pInfo(nullptr) {} // Construtor padrão
        ~Elemento() {
            pProx = nullptr;
            pInfo = nullptr;
        }

        void setProx(Elemento<TE>* p) { pProx = p; }
        Elemento<TE>* getProx() const { return pProx; }

        void setInfo(TE* p) { pInfo = p; }
        TE* getInfo() const { return pInfo; }
    };

private:
    Elemento<TL>* pPrimeiro; // Ponteiro para o primeiro nó da lista
    Elemento<TL>* pUltimo;   // Ponteiro para o último nó da lista
    int tamanho;             // Quantidade de elementos na lista

public:
    Lista() : pPrimeiro(nullptr), pUltimo(nullptr), tamanho(0) {} // Construtor padrão

    ~Lista() { // Destrutor que limpa os nós da lista
        limpar();
    }

    void incluir(TL* pInfo) { // Insere um novo elemento no final da lista
        if (!pInfo) return;

        Elemento<TL>* novo = new Elemento<TL>();
        novo->setInfo(pInfo);

        if (pPrimeiro == nullptr) {
            pPrimeiro = novo;
            pUltimo = novo;
        } else {
            pUltimo->setProx(novo);
            pUltimo = novo;
        }
        tamanho++;
    }

    void remover(TL* pInfo) { // Remove um elemento específico da lista
        if (!pInfo || !pPrimeiro) return;

        Elemento<TL>* atual = pPrimeiro;
        Elemento<TL>* anterior = nullptr;

        while (atual != nullptr && atual->getInfo() != pInfo) {
            anterior = atual;
            atual = atual->getProx();
        }

        if (atual == nullptr) return;

        if (atual == pPrimeiro) {
            pPrimeiro = atual->getProx();
            if (pPrimeiro == nullptr) pUltimo = nullptr;
        } else {
            anterior->setProx(atual->getProx());
            if (atual == pUltimo) pUltimo = anterior;
        }

        delete atual;
        tamanho--;
    }

    void limpar() { // Desaloca todos os nós (Elementos) da lista
        Elemento<TL>* atual = pPrimeiro;
        while (atual != nullptr) {
            Elemento<TL>* aux = atual;
            atual = atual->getProx();
            delete aux;
        }
        pPrimeiro = nullptr;
        pUltimo = nullptr;
        tamanho = 0;
    }

    Elemento<TL>* getPrimeiro() const { return pPrimeiro; }
    int getTamanho() const { return tamanho; }
};

#endif
