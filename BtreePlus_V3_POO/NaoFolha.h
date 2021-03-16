#ifndef NAOFOLHA_H_INCLUDED
#define NAOFOLHA_H_INCLUDED
#include "Pagina.h"
#include "Folha.h"
//#include "TIndices.h"
#include <vector>

struct TIndices{ // celula que vai dentro do meu no
        Pagina *dir;
        int indice;
};

class NaoFolha : public Pagina{
    public:
    NaoFolha(); // construtor
    //NaoFolha(int n):Pagina(n){ }
    Pagina *primeiro;

    vector<TIndices> i;
    //vector<TIndices>::iterator as;

    ///metodos
    //void splitNaoFolha(Pagina *&no, Pagina *&A, int valorPraJogarProPai);
    void splitNaoFolha(Pagina *&no, Folha *&A,int valorPraJogarProPai,Pagina *&raizA);
    void setIndice(int val);
    void setPrimeiro(Pagina *&primeiro);
    Pagina *buscoNaoFolha(NaoFolha *no, int val);
    Pagina *getPrimeiro();
    void arrumarPonteiros(NaoFolha *&aux1,Folha *&A, int valorPraJogarProPai);
    Pagina *buscaFolha(NaoFolha *no);
    int retornaTamPai(NaoFolha *n);
    void arrumarPonteiros2(NaoFolha *nfAux, Pagina *&no, NaoFolha *&B, Pagina *&A);
    static bool ordenar(const TIndices &f1, const TIndices &f2);
    void setPai(Pagina *&p);
    void buscaPorIgualdadeNaoFolha(NaoFolha *no, int val);
    Pagina *buscaPorIntervaloNaoFolha(NaoFolha *no, int val);
    //void setDireita(Pagina *p);
    //Pagina *getDireita();
    //void mostrarRaiz(NaoFolha *no);
};

#endif // NAOFOLHA_H_INCLUDED
