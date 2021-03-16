#include <iostream>
#include <vector>
#include <cmath>
///biblioteca usada para se gerar numeros aleatorios
/*
#include <cstdlib>
#include <ctime>
*/
int pG = 2;
int tamBuckets = 4;

using namespace std;

struct bucket{
    int profundidadeLocal;
    vector<int> x;
};

struct celulaDiretorio{
    int numBin;
    bucket *b;
};

struct Diretorio{
    int profundidadeGlobal;
    vector<celulaDiretorio> v;
};

void criarNovoDiretorio(Diretorio *&d, bucket *&bu){
    d = new Diretorio();
    d->profundidadeGlobal = pG;

    //é criado um novo diretorio onde cada celula desse diretorio, irá apontar para um novo bucket
    for(int i = 0; i < 4; i++){
        bu = new bucket();
        bu->profundidadeLocal = pG;
        celulaDiretorio c;
        c.numBin = i;
        c.b = bu;
        d->v.push_back(c);
    }
}

//calcula o hash(num) e retorna seu resto
int calculoHash(int num, Diretorio *&d){
    int x = d->profundidadeGlobal;
    int y = pow(x,2);
    return num%y;
}

void duplicarDiretorio(int &profundidadeGlobalAtual, Diretorio *&d){
    int profundidadeGlobalAnterior = profundidadeGlobalAtual - 1;
    //dar push_back no vetor atual inserindo novos numeros, ex se já existir,
    //0, 1, 2, 3 inserir 4, 5, 6, 7 e fazer esses novos apontar para suas posições
    for(int i = pow(2, profundidadeGlobalAnterior); i < pow(2, profundidadeGlobalAtual); i++){
        celulaDiretorio c;
        c.numBin = i;
        d->v.push_back(c)
    }
}

void duplicarBucket(Diretorio *&d){
    int pGlobalAtual = d->profundidadeGlobal;
    d->v[pow(2,pGlobalAtual)/2+1] = new bucket();
}

void inserirNumBucket(int num, Diretorio *&d){
    //verificar se o bucket ainda cabe alguma coisa

    int resto = calculoHash(num, d);
    //insiro o numero no respectivo bucket cujo resto foi calculado
    d->v[resto].b->x.push_back(num);

    if(d->v[resto].b->x.size()==tamBuckets){
        cout << "Bucket esta cheio" << endl;
        duplicarDiretorio(d->profundidadeGlobal, d);
        duplicarBucket(d);
    }
}

void mostrar(Diretorio *d){
    vector<celulaDiretorio>::iterator i;
    vector<int>::iterator j;

    for(i = d->v.begin(); i!= d->v.end(); i++){
        //crio um iterador j para percorrer os buckets um a um, mostrando todos elementos
        //i->b aponta para o endereço do bucket desejado, i->b->x.begin() aponta para o elemento que tem no bucket
        for(j = i->b->x.begin(); j!= i->b->x.end(); j++){
            cout << "[" << *j << "]";
        }
        cout << endl;
    }
}

int main()
{
    Diretorio *d;
    bucket *bu;
    criarNovoDiretorio(d, bu);
    inserirNumBucket(15, d);
    inserirNumBucket(7, d);
    inserirNumBucket(19, d);
    inserirNumBucket(10, d);
    inserirNumBucket(1, d);
    inserirNumBucket(5, d);
    inserirNumBucket(4, d);
    inserirNumBucket(21, d);
    inserirNumBucket(13, d);
    inserirNumBucket(12, d);
    inserirNumBucket(32, d);
    inserirNumBucket(16, d);
    ///gerar numeros aleatórios
//    srand((unsigned)time(NULL));
//    for(int i = 0; i < 100; i++){
//        inserirNumBucket(rand()%100, d);
//    }
    mostrar(d);
    return 0;
}

