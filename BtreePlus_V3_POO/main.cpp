#include <iostream>
#include "Pagina.h"
#include "Folha.h"
#include "NaoFolha.h"
#include <typeinfo>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

Pagina *raiz = NULL;

 int main(int argc, char** arqv) {
    int ordemMain, val, procurar, a, b;
    string st = arqv[2];

    stringstream s(st);
    s >> ordemMain;

    fstream arquivo;
    arquivo.open(arqv[1]);

    ordemMain = 4;

    Folha f;

    cout << "Para insercoes altere os valores do arquivo texto !!!" << endl; // os numeros a serem iseridos estao em um arquivo txt, para novas insercoes altere o arquivo.
    do {
        arquivo >> val;
        f.inserir(raiz, val);
        cout << "Inserindo  " << val << endl;
    } while (!arquivo.eof()&&arquivo.good());
    cout << "Elementos inseridos com sucesso na arvore!!!" << endl;
    cout << "Numeros presentes nos nos folha: " << endl;
    f.mostrarFolha(raiz);

    int op;

    /// Menu interativo

    cout << "        " << "Escolha uma Opcao:  " << endl;
    cout << " |" << "-------------------------------------------" << "| " << endl;
    cout << " |" <<  "Digite 1 para Realizar Busca por Igualdade " << "| " << endl ;
    cout << " |" << "-------------------------------------------" << "| " << endl;
    cout << " |" << "Digite 2 para Realizar Busca por intervalo " << "| " << endl;
    cout << " |" << "-------------------------------------------" << "| " << endl;
    cout << " |" << "Digite 3 para SAIR                         " << "| " << endl;
    cout << " |" << "-------------------------------------------" << "| " << endl;
    cin >> op;

    NaoFolha n;
    NaoFolha *nf1= dynamic_cast<NaoFolha*>(raiz);
    Folha fAux;

    switch (op){
    case 1:
        cout << "Digite um valor pra fazer busca por igualdade: ";
        cin >> procurar;
        cout << "Processando..." << endl;

        n.buscaPorIgualdadeNaoFolha(nf1, procurar);
        break;

    case 2:
        cout << "Digite o primeiro valor pra fazer busca por intervalo: ";
        cin >> a;
        cout << "Digite o segundo valor pra fazer busca por intervalo: ";
        cin >> b;
        cout << "Processando..." << endl;

        fAux.buscaIntervalo(raiz, a, b);
        break;
    default:
        break;
    }
}
