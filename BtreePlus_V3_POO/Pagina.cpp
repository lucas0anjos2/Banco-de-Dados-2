#include "Pagina.h"
//#include "Folha.h"
#include <iostream>
#include <vector>
//#include "TIndices.h"
using namespace std;

Pagina::Pagina() { // Metodo construtor da minha classe pagina
    ordem = 2;
    res = (ordem*2) + 1; /// isso é a capacidade maxima suportada por meu vetor aux criado pra fazer o split
}

Pagina *Pagina::buscoNaoFolha(Pagina *&no, int val){}

void Pagina::setAnterior(Pagina *anterior) {}

void Pagina::setIndice(int i) {}

void Pagina::removePosicao() {}

void Pagina::setProximo(Pagina *proximo) {}

vector<int>::iterator Pagina::getInicioVetor() {}

vector<int>::iterator Pagina::getFimVetor() {}

void Pagina::setPrimeiro(Pagina *primeiro) {}

int Pagina::tamVector() {
    return 0;
}

int Pagina::getX(int a) {
    return 0;
}

Pagina *Pagina::getAnterior() {
    return 0;
}

Pagina *Pagina::getProximo() {
    return 0;
}

Pagina *Pagina::getprimeiro() {
    return 0;
}

void Pagina::setPai(Pagina *p){}

Pagina *Pagina::getPai(){
    //return 0;
}
