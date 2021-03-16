#ifndef PAGINA_H_INCLUDED
#define PAGINA_H_INCLUDED
#include <vector>
//#include "Pagina.h"
#include <iostream>
//#include "NaoFolha.h"
using namespace std;

class Pagina {
public:
    Pagina(); // construtor
    int ordem;
    int res;
    Pagina *pai;

    ///meotodos virtuais para serem acessados por outras classes
    virtual void setAnterior(Pagina *anterior);
    virtual void setIndice(int i);
    virtual void removePosicao();
    virtual void setProximo(Pagina *proximo);
    virtual vector<int>::iterator getInicioVetor();
    virtual vector<int>::iterator getFimVetor();
    virtual void setPrimeiro(Pagina *primeiro);
    virtual int tamVector();
    virtual int getX(int a);
    virtual Pagina *getAnterior();
    virtual Pagina *getProximo();
    virtual Pagina *getprimeiro();
    virtual void setPai(Pagina *p);
    virtual Pagina *getPai();
    virtual Pagina *buscoNaoFolha(Pagina *&no, int val);
};

#endif // PAGINA_H_INCLUDED
