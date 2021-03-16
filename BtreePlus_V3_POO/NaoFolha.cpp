#include "NaoFolha.h" // header
#include <iostream>
#include <vector> // vetor dinamico
#include <typeinfo> // casts e testes de tipos de classes
#include <algorithm> // metodo de ordenacao
//#include "TIndices.h"
using namespace std;
NaoFolha::NaoFolha()
{

}

void NaoFolha::setPai(Pagina *&p){
    this->pai = p;
}

void NaoFolha::arrumarPonteiros2(NaoFolha *nfAux, Pagina *&no, NaoFolha *&B, Pagina *&A) // arrumando ponteiros para split
{
    int cont = 0;
    int metade = res/2;
    B->primeiro = nfAux->i.at(metade).dir;
    vector<TIndices>::iterator it;
    it = nfAux->i.begin();
    it = it + (metade + 1);
    while(it!=nfAux->i.end() && metade < res - 1){
        B->i.at(cont).dir = nfAux->i.at(metade+1).dir;
        metade++;
        it++;
        cont ++;
    }

    int SIZE = B->i.size();

    //cout << "Tamanho de B: " << SIZE << endl;

    B->i.at(SIZE-1).dir = A;

}

void NaoFolha::setIndice(int val)
{
    TIndices a;
    a.indice = val;
    this->i.push_back(a);
}

void NaoFolha::setPrimeiro(Pagina *&primeiro)
{
    this->primeiro = primeiro;
}

Pagina *NaoFolha::getPrimeiro(){
    return this->primeiro;
}

bool NaoFolha::ordenar(const TIndices &f1, const TIndices &f2) { // metodo de comparacao utilizado na ordenacao
    return f1.indice<f2.indice;
}

void NaoFolha::splitNaoFolha(Pagina *&no, Folha *&A, int valorPraJogarProPai, Pagina *&raizA) // split para nos do tipo nao folha
{
    int qtdSplit = 0 ;
    int acharVariavelPraJogarProPai, metadeMaisUm;
    if(no->getPai() == NULL) { // se meu no for a raiz
        NaoFolha *r = new NaoFolha;
        r->setIndice(valorPraJogarProPai);
        no->setPai(r);
        A->setPai(r);
        r->setPrimeiro(no);

        vector<int>::iterator it;

        it = A->getInicioVetor();

        vector<TIndices>::iterator it2;
        it2 = r->i.begin();

        vector<TIndices>::iterator a;

        r->i.at(0).dir = A;

        no =  r;

    } else{ // se nao dor a raiz
        NaoFolha *nfAux = dynamic_cast<NaoFolha*>(no->getPai());

        NaoFolha *B = new NaoFolha;

        no->setPai(B);
        A->setPai(B);

        vector<int> aux;

        for(int cont = 0; cont < res - 1; cont++){
            aux.push_back(nfAux->i.at(cont).indice);
        }

        aux.push_back(valorPraJogarProPai);

        sort(aux.begin(), aux.end()); // ordenando meu vetor auxiliar

        acharVariavelPraJogarProPai = res/2;

        valorPraJogarProPai = aux.at(acharVariavelPraJogarProPai);

        metadeMaisUm = acharVariavelPraJogarProPai + 1;

        int cont = 0;
        while(metadeMaisUm<=res-1) {
            TIndices t;
            t.indice = aux.at(metadeMaisUm);
            B->i.push_back(t);
            metadeMaisUm++;
            cont ++;
        }


        sort(B->i.begin(), B->i.end(), ordenar); // ordenando meu no

        ///tem que fazer dinamic em A
//
        Pagina *p = dynamic_cast<Pagina*>(A);
//
        arrumarPonteiros2(nfAux, no, B, p);
//
        int metadeVetorOriginal = ordem;
        while(metadeVetorOriginal>0) {
            nfAux->i.pop_back();
            metadeVetorOriginal--;
        }

        NaoFolha *nf1 = new NaoFolha;

        raizA = nf1;

        //cout << "End apontado raizA: " << raizA << endl;

        TIndices auxIndices;
        auxIndices.indice = valorPraJogarProPai;
        auxIndices.dir = B;

        nf1->i.push_back(auxIndices);

        nfAux->pai = nf1;
        B->pai = nf1;

        nf1->primeiro = nfAux;

        //return nf1;
    }
}

Pagina *NaoFolha::buscoNaoFolha(NaoFolha *no, int val) {
    int cont = 0;
    bool x;
    vector<TIndices>::iterator it;
    it =  no->i.begin();

    it = it+1;

    x = typeid(*no->i.at(cont).dir) == typeid(Folha);
    //inicio:
    if(val>no->i.at(cont).indice) {
        if(x==false) {
            NaoFolha *n1 = dynamic_cast<NaoFolha*>(no->i.at(cont).dir);
            buscoNaoFolha(n1, val);
        } else {
            if(x==true) {
                while(it<=no->i.end()) {
                    if(val > no->i.at(cont).indice && it!=no->i.end()) {
                        cont++;
                        it++;
                    } else {
                        if(val < no->i.at(cont).indice) {
                            int conta = 0;
                            return no->i.at(cont - 1).dir;
                            break;
                        } else {
                            return no->i.at(cont).dir;
                            break;
                        }
                    }
                }
            }
        }
    }else if(val < no->i.at(0).indice) {
        if(x==false) {
            NaoFolha *n1 = dynamic_cast<NaoFolha*>(no->getPrimeiro());
            buscoNaoFolha(n1, val);
        } else {
            if(x==true) {
                return no->getPrimeiro();
            }
        }
    }
}

void NaoFolha::arrumarPonteiros(NaoFolha *&aux1, Folha *&A, int valorPraJogarProPai){
    vector<TIndices>::iterator it;
    int cont = 0;

    it = aux1->i.begin();

    while(it<=aux1->i.end()){
        if(valorPraJogarProPai == it.base()->indice){
            aux1->i.at(cont).dir = A;
            break;
        } else {
            cont++;
            it++;
        }
    }
}

///funcao destinada a mostrar os elementos da folha
Pagina *NaoFolha::buscaFolha(NaoFolha *no) {
    bool teste = typeid(*(no->getPrimeiro())) == typeid(Folha);
    Pagina *noAux;
    NaoFolha *nfAux;
    //cout << "Passei aqui: " << endl;
    if(teste) {
        Pagina *x;
        x = no->getPrimeiro();
        //cout << "END apontado por x:" << x << endl;
        return x;
    } else {
        noAux = no->getPrimeiro();
        nfAux = dynamic_cast<NaoFolha*>(noAux);
        buscaFolha(nfAux);
    }
    //return 0;
}

int NaoFolha::retornaTamPai(NaoFolha *n){
    return n->i.size();
}

void NaoFolha::buscaPorIgualdadeNaoFolha(NaoFolha *no, int val){
    int cont = 0;
    bool x;
    bool achou = false;
    vector<TIndices>::iterator it;
    it =  no->i.begin();
    it = it+1;
    x = typeid(*no->i.at(cont).dir) == typeid(Folha);

    if(val >= no->i.at(cont).indice){
        if(x == false && it == no->i.end()){
            NaoFolha *nf1 = dynamic_cast<NaoFolha*>(no->i.at(cont).dir);
            buscaPorIgualdadeNaoFolha(nf1, val);
        } else {
            while(it<=no->i.end()){
                if(x==true && it != no->i.end()){
                    if(val >= no->i.at(cont).indice){
                        cont ++;
                        it++;
                    }
                } else {
                   if(val >= no->i.at(cont).indice && it == no->i.end()){
                        Folha f1;
                        achou =  f1.buscaPorIgualdadeFolha(no->i.at(cont).dir, val);
                        if(achou == true){
                            cout << "O elemento procurado faz parte da arvore!!! " << endl;
                            break;
                        } else {
                            cout << "O elemento procurado nao faz parte da arvore!!! " << endl;
                            break;
                        }
                    } else {
                        if(val < no->i.at(cont).indice && it == no->i.end()){
                            Folha f1;
                            achou =  f1.buscaPorIgualdadeFolha(no->i.at(cont-1).dir, val);
                            if(achou == true){
                                cout << "O elemento procurado faz parte da arvore!!! " << endl;
                                break;
                            } else {
                                cout << "Entrei aqui" << endl;
                                cout << "O elemento procurado nao faz parte da arvore!!! " << endl;
                                break;
                            }
                        }
                    }
                }
            }
        }
    } else {
        if(val < no->i.at(0).indice && x==false){
            NaoFolha *nf2 = dynamic_cast<NaoFolha*>(no->getPrimeiro());
            buscaPorIgualdadeNaoFolha(nf2,val);
        } else {
            if(val < no->i.at(0).indice && x==true){
                Folha f2;
                achou = f2.buscaPorIgualdadeFolha(no->getPrimeiro(),val);
                if(achou == true){
                    cout << "O valor procurado faz parte da arvore!!! "<< endl;
                } else {
                    cout << "O valor procurado nao faz parte da arvore!!! "<< endl;
                }
            }
        }
    }
}


Pagina *NaoFolha::buscaPorIntervaloNaoFolha(NaoFolha *no, int val){
    int cont = 0;
    bool x;
    bool achou = false;
    vector<TIndices>::iterator it;
    it =  no->i.begin();
    it = it+1;
    x = typeid(*no->i.at(cont).dir) == typeid(Folha);

    if(val >= no->i.at(cont).indice){
        if(x == false && it == no->i.end()){
            NaoFolha *nf1 = dynamic_cast<NaoFolha*>(no->i.at(cont).dir);
            buscaPorIntervaloNaoFolha(nf1, val);
        } else {
            while(it<=no->i.end()){
                if(x==true && it != no->i.end()){
                    if(val >= no->i.at(cont).indice){
                        cont ++;
                        it++;
                    }
                } else {
                   if(val >= no->i.at(cont).indice && it == no->i.end()){
                        return no->i.at(cont).dir;
                        break;
                    } else {
                        if(val < no->i.at(cont).indice && it == no->i.end()){
                            return no->i.at(cont-1).dir;
                            break;
                        }
                    }
                }
            }
        }
    } else {
        if(val < no->i.at(0).indice && x==false){
            NaoFolha *nf2 = dynamic_cast<NaoFolha*>(no->getPrimeiro());
            buscaPorIntervaloNaoFolha(nf2,val);
        } else {
            if(val < no->i.at(0).indice && x==true){
                return no->getPrimeiro();
            }
        }
    }
}

//void NaoFolha::mostrarRaiz(NaoFolha *no)
//{
//    vector<TIndices>::iterator it;
//    //cout "Tam raiz: " << no->i.size() << endl;
//    for(it = no->i.begin(); it != no->i.end(); it++) cout << "Val raiz: "<< it.base()->indice << endl;
//}
