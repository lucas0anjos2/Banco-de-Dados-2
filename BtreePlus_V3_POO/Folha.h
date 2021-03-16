#ifndef FOLHA_H_INCLUDED
#define FOLHA_H_INCLUDED
#include "Pagina.h"
//#include "NaoFolha.h"
#include <vector>

class Folha : public Pagina {
    public:
        Folha(); // construtor
        //virtual ~Folha() = default;
        //Folha(int n):Pagina(n){ } // "n" é o numero de registros
        Pagina *anterior;
        Pagina *proximo;
        vector<int> x;
        vector<int>::iterator i;

        ///metodos folha

        int tamVector();
        void removePosicao();
        void setIndice(int val);
        int getX(int a);
        vector<int>::iterator getInicioVetor();
        vector<int>::iterator getFimVetor();
        void setAnterior(Pagina *anterior);
        Pagina *getAnterior();
        void setProximo(Pagina *proximo);
        Pagina *getProximo();
        void splitFolha(Pagina *&no, int val, Pagina *&raizA);
        static bool ordenar(const int &f1, const int &f2);
        void inserir(Pagina *&no, int val);
        void mostrar(Pagina *no);
        void setPai(Pagina *p);
        Pagina *getPai();
        void mostrarFolha(Pagina *no);
        bool buscaPorIgualdadeFolha(Pagina *p, int val);
        void buscaIntervalo(Pagina *no,int a, int b);
};

#endif // FOLHA_H_INCLUDED
