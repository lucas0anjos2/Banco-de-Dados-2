#include "Folha.h" //header
#include "NaoFolha.h"
#include <iostream>
#include <vector> // vetor dinamico
#include <algorithm> // metodo de ordenacao
#include <typeinfo> // casts e testes de tipos de classes
using namespace std;

Folha::Folha() {

}

///metodos folha

void Folha::setPai(Pagina *p)
{
    this->pai = p;
}

Pagina *Folha::getPai()
{
    return pai;
}

int Folha::tamVector() {
    return x.size();
}

void Folha::removePosicao() {
    this->x.pop_back();
}

void Folha::setIndice(int val) {
    this->x.push_back(val);
}

int Folha::getX(int a) {
    i = x.begin();/// i aponta para o inicio do vector, a medida que o parametro a é incrementado
    /// o i vai apontando para o a proxima posição do vector
    i = i + a;
    return *i;
}

vector<int>::iterator Folha:: getInicioVetor() {
    return x.begin();
}


vector<int>::iterator Folha::getFimVetor() {
    return x.end();
}

void Folha::setAnterior(Pagina *anterior) {
    this->anterior = anterior;
}

Pagina *Folha::getAnterior() {
    return this->anterior;
}

void Folha::setProximo(Pagina *proximo) {
    this->proximo = proximo;
}

Pagina *Folha::getProximo() {
    return this->proximo;
}

void Folha::splitFolha(Pagina *&no, int val, Pagina *&raizA) { // metodo realiza split para nos do tipo folha
    vector<int> aux; // vetor auxiliar para realizacao dos splits
    vector<int>::iterator it;
    int cont, acharVariavelPraJogarProPai, valorPraJogarProPai;
    int metadeMaisUm; // divisor do vetor auxiliar
    int qtdSplit = 0;
    NaoFolha n;
    int qtdElementosPai;

    if(no->getPai()!=NULL){ // se o no a ser dividido for minha raiz

        NaoFolha *nfAux = dynamic_cast<NaoFolha*>(no->getPai());

        qtdElementosPai = n.retornaTamPai(nfAux);
    }


    if(no->getAnterior() == NULL && no->getProximo()==NULL && no->getPai() == NULL) {
        Folha *A = new Folha;
        no->setProximo(A);
        A->setProximo(NULL);
        A->setAnterior(no);
        A->setPai(NULL);

        it = aux.begin();
        for(cont = 0; cont < res - 1; cont++) {
            aux.push_back(no->getX(cont));
        }
        aux.push_back(val);
        sort(aux.begin(), aux.end(), ordenar);

        acharVariavelPraJogarProPai = res/2;
        valorPraJogarProPai = aux.at(acharVariavelPraJogarProPai);
        metadeMaisUm = acharVariavelPraJogarProPai + 1;
        int i = 0;
        ///passando metade do vetor aux pra nova folha
        while(metadeMaisUm<=res-1) {
            A->setIndice(aux.at(metadeMaisUm));
            metadeMaisUm++;
        }

        A->setIndice(valorPraJogarProPai);
        sort(A->getInicioVetor(), A->getFimVetor(), ordenar);

        ///removendo conteiner desnecessários da folha antiga
        int metadeVetorOriginal = ordem;
        while(metadeVetorOriginal>0) {
            no->removePosicao();
            metadeVetorOriginal--;
        }

        n.splitNaoFolha(no, A, valorPraJogarProPai, raizA);
    } else if(qtdElementosPai == res - 1){

        Folha *A = new Folha;
        no->setProximo(A);
        A->setProximo(NULL);
        A->setAnterior(no);

        it = aux.begin();
        for(cont = 0; cont < res - 1; cont++) {
            aux.push_back(no->getX(cont));
        }

        aux.push_back(val);
        sort(aux.begin(), aux.end(), ordenar);
        acharVariavelPraJogarProPai = res/2;
        valorPraJogarProPai = aux.at(acharVariavelPraJogarProPai);
        metadeMaisUm = acharVariavelPraJogarProPai + 1;

        while(metadeMaisUm<=res-1) {
            A->setIndice(aux.at(metadeMaisUm));
            metadeMaisUm++;
        }

        A->setIndice(valorPraJogarProPai);
        sort(A->getInicioVetor(), A->getFimVetor(), ordenar);

        int metadeVetorOriginal = ordem;
        while(metadeVetorOriginal>0) {
            no->removePosicao();
            metadeVetorOriginal--;
        }

        n.splitNaoFolha(no, A, valorPraJogarProPai, raizA);///tem que passar a raiz aqui

    } else {
        Folha *A = new Folha;
        no->setProximo(A);
        A->setProximo(NULL);
        A->setAnterior(no);
        A->setPai(A->getAnterior()->getPai());

        it = aux.begin();
        for(cont = 0; cont < res - 1; cont++) {
            aux.push_back(no->getX(cont));
        }

        aux.push_back(val);
        sort(aux.begin(), aux.end(), ordenar);
        acharVariavelPraJogarProPai = res/2;
        valorPraJogarProPai = aux.at(acharVariavelPraJogarProPai);
        metadeMaisUm = acharVariavelPraJogarProPai + 1;

        while(metadeMaisUm<=res-1) {
            A->setIndice(aux.at(metadeMaisUm));
            metadeMaisUm++;
        }

        A->setIndice(valorPraJogarProPai);
        sort(A->getInicioVetor(), A->getFimVetor(), ordenar);

        int metadeVetorOriginal = ordem;
        while(metadeVetorOriginal>0) {
            no->removePosicao();
            metadeVetorOriginal--;
        }

        A->getPai()->setIndice(valorPraJogarProPai);
        Pagina *aux1 = A->getPai();
        NaoFolha *noAux;
        noAux = dynamic_cast<NaoFolha*>(aux1);

        n.arrumarPonteiros(noAux, A, valorPraJogarProPai);
    }
}

bool Folha::ordenar(const int &f1, const int &f2) { // metodo de comparacao a ser utilizado na minha ordenacao
    return f1<f2;
}

void Folha::inserir(Pagina *&no, int val) { // insercao em nos folha
    bool d, t;
    if(no == NULL) { // se meu ponteiro nao tem valor
        Folha *aux = new Folha; // instancia-se um novo
        aux->setIndice(val);
        aux->setAnterior(NULL);
        aux->setProximo(NULL);
        aux->setPai(NULL);
        no = aux;
    } else {

        d = typeid(*no) == typeid(Folha); // d recebe a comparacao se meu no eh do tipo folha

        if(d == false) { //se d nao for folha
            NaoFolha nfAux;
            Pagina *aux;
            Pagina *aux2;
            NaoFolha *noAux;
            noAux = dynamic_cast<NaoFolha*>(no);
            aux = nfAux.buscoNaoFolha(noAux, val);

            if(aux->tamVector() == res - 1) {
                //cout << "Valor do no: " << no << endl;
                splitFolha(aux, val, no);
            } else {
                //cout << "Entrei aqui::" << endl;
                inserir(aux, val);
            }
        } else { // se for folha
            if(d == true && no->tamVector() < res - 1) {
                no->setIndice(val);
                sort(no->getInicioVetor(), no->getFimVetor(), ordenar);
            } else if (d == true && no->tamVector() == res-1) {
                splitFolha(no, val, no);
            }
        }
    }
}

void Folha::mostrarFolha(Pagina *no) {
    Pagina *aux;
    bool flag = typeid(*no) == typeid(Folha);

    if(flag == true){
        while(no != NULL){
            //cout << "Entrei aquiiii" << endl;
            vector<int>::iterator it;
            for(it = no->getInicioVetor(); it != no->getFimVetor(); it++){
                cout << *it << " - ";
            }

            no = no->getProximo();
        }
        cout << endl;
    } else {
        NaoFolha *nf;
        NaoFolha *noAux;
        noAux = dynamic_cast<NaoFolha*>(no);
        aux = nf->buscaFolha(noAux);
        mostrarFolha(aux);
    }
}

bool Folha::buscaPorIgualdadeFolha(Pagina *p, int val){
    Folha *f1 = dynamic_cast<Folha*>(p);
    vector<int>::iterator it;
    bool achou = false;

    for(it = f1->x.begin(); it!=f1->x.end(); it++){
        if(*it == val){
            achou = true;
        }
    }
    return achou;
}

void Folha::buscaIntervalo(Pagina *no,int a, int b) {

    Pagina *p1;
    NaoFolha n1, *n2;
    n2 = dynamic_cast<NaoFolha*>(no);
    p1 = n1.buscaPorIntervaloNaoFolha(n2,a);
    Folha *f1;
    f1 = dynamic_cast<Folha*>(p1);
    vector<int>::iterator it;
    bool achou = false;

    while(f1 != NULL && achou == false) {
        it = f1->x.begin();
        //cout << "Entrei aqui" << endl;
        while(it!=f1->x.end()) {
            if(*it != b) {
                if(*it>a) {
                    cout << *it << endl;
                }
                it++;
            }else{
                achou = true;
                break;
            }
        }
        Folha *proximo = dynamic_cast<Folha*>(f1->getProximo());
        f1 = proximo;
    }

}

