#include <iostream>
#include "volei.h"

using namespace std;

int main(){
    //Time 1
    Time time1("X-Men");
    Levantador le1("Carlos", 3, 2, 1, 5);
    Oposto op1("Jorge", 2, 2, 4, 3);
    Libero li1("João", 2, 2, 1, 21);
    Meia me1("Pedro", 7, 2, 4, 2), me2("Manuel", 6, 3, 3, 1);
    Ponta po1("Matheus", 8, 5, 2), po2("José", 9, 4, 3);

    cout << "Jogadores do Time 1:" << endl;
    cout << "Levantador: " << le1.pegarHabilidadeIndividual() << endl;
    cout << "Oposto: " << op1.pegarHabilidadeIndividual() << endl;
    cout << "Libero: " << li1.pegarHabilidadeIndividual() << endl;
    cout << "Meia 1: " << me1.pegarHabilidadeIndividual() << endl;
    cout << "Meia 2: " << me2.pegarHabilidadeIndividual() << endl;
    cout << "Ponta 1: " << po1.pegarHabilidadeIndividual() << endl;
    cout << "Ponta 2: " << po2.pegarHabilidadeIndividual() << endl;

    time1.inserirJogador(le1);
    time1.inserirJogador(op1);
    time1.inserirJogador(li1);
    time1.inserirJogador(me1);
    time1.inserirJogador(me2);
    time1.inserirJogador(po1);
    time1.inserirJogador(po2);
    
    cout << "Pontuação total do Time 1: " << time1.pegarHabilidadeTotal() << endl << endl;

    //Time 2
    Time time2("Vingadores");
    Levantador le3("Josué", 4, 1, 1, 4);
    Oposto op3("Maurício", 2, 3, 4, 2);
    Libero li3("Péricles", 3, 2, 1, 18);
    Meia me3("Eduardo", 6, 2, 4, 1), me4("Edmundo", 6, 3, 3, 1);
    Ponta po3("Roberto", 7, 5, 3), po4("Marcelo", 8, 4, 4);

    cout << "Jogadores do Time 2:" << endl;
    cout << "Levantador: " << le1.pegarHabilidadeIndividual() << endl;
    cout << "Oposto: " << op1.pegarHabilidadeIndividual() << endl;
    cout << "Libero: " << li1.pegarHabilidadeIndividual() << endl;
    cout << "Meia 1: " << me1.pegarHabilidadeIndividual() << endl;
    cout << "Meia 2: " << me2.pegarHabilidadeIndividual() << endl;
    cout << "Ponta 1: " << po1.pegarHabilidadeIndividual() << endl;
    cout << "Ponta 2: " << po2.pegarHabilidadeIndividual() << endl;

    time2.inserirJogador(le3);
    time2.inserirJogador(op3);
    time2.inserirJogador(li3);
    time2.inserirJogador(me3);
    time2.inserirJogador(me4);
    time2.inserirJogador(po3);
    time2.inserirJogador(po4);

    cout << "Pontuação total do Time 2: " << time2.pegarHabilidadeTotal() << endl << endl;

    Jogador *j = &le3;
    cout << j->getPosicao() << endl;
    
    //Partida
    Partida p;
    p.realizar(time1, time2);

    return 0;
}