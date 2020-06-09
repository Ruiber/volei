#include <iostream>
#include <cstdlib>
#include <ctime>
#include "volei.h"

using namespace std;

int Levantador::pegarHabilidadeIndividual(){
    return getAtaque() + 6*getPasse() + 3*getDefesa() + 10*getModificador();
}

int Oposto::pegarHabilidadeIndividual(){
    return 6*getAtaque() + getPasse() + 3*getDefesa() + 20*getModificador();
}

int Libero::pegarHabilidadeIndividual(){
    int pontos = 5*getPasse() + 5*getDefesa();
    int partidas = getModificador();
    while(partidas >= 10){
        pontos *= 2;
        partidas -= 10;
    }
    return pontos;
}

int Meia::pegarHabilidadeIndividual(){
    return 4*getAtaque() + getPasse() + 3*getDefesa() - getModificador();
}

int Ponta::pegarHabilidadeIndividual(){
    return 4*getAtaque() + 3*getPasse() + 3*getDefesa();
}

Time::Time(const Time &t){
    nome = t.nome;
    nJogadores = t.nJogadores;
    jogadores = new Jogador*[7];
    for(int i=0; i<nJogadores; i++){
        jogadores[i] = t.jogadores[i];
    }
}

bool Time::inserirJogador(Jogador &j){
    if(nJogadores < 7){
        jogadores[nJogadores++] = &j;
        return true;
    }
    return false;
}

bool Time::alterarJogador(int n, Jogador &j){
    if(n <= nJogadores){
        jogadores[n] = &j;
        return true;
    }
    return false;
}

int Time::pegarHabilidadeTotal(){
    int total=0;
    if(nJogadores == 7){
        for(int i=0; i<7; i++){
            total += jogadores[i]->pegarHabilidadeIndividual();
        }
        return total;
    }
    return -1;
}

bool Partida::ponto(Time &t1, Time &t2, bool saque){
    float hab1 = t1.pegarHabilidadeTotal(), hab2 = t2.pegarHabilidadeTotal(), aleatorio;
    if (saque) hab2 *= 1.25;
    else hab1 *= 1.25; 
    aleatorio = (rand()%((int) hab1*100 + (int) hab2*100) + 1) / 100;
    if (aleatorio <= hab1) return false; 
    return true;
}

bool Partida::realizarSet(Time &t1, Time &t2, int set1, int set2){
    int ponto1 = 0, ponto2 = 0, total = 25;
    bool saque;
    if ((set1 + set2)%2) saque = false;
    else saque = true;
    if (set1 == 2 && set2 == 2) total = 15;
    while ((ponto1 < total && ponto2 < total) || (ponto1 - ponto2 < 2 && ponto1 - ponto2 > -2)){
        saque = ponto(t1, t2, saque);
        ponto1 += (int) !saque;
        ponto2 += (int) saque;
        cout << ponto1 << " X " << ponto2 << endl;
    }
    cout << endl;
    if (ponto1 > ponto2) return false;
    else return true;
}

bool Partida::realizar(Time &t1, Time &t2){
    srand(time(NULL));
    int set1 = 0, set2 = 0;
    cout << t1.getNome() << " X " << t2.getNome() << endl;
    if(t1.getnJogadores()==7 && t2.getnJogadores()==7){
        while(set1 != 3 && set2 != 3){
            cout << endl << set1 + set2 + 1 << "º Set:" << endl;
            if(realizarSet(t1, t2, set1, set2)) set2++;
            else set1++;
            cout << "Placar: " << set1 << " X " << set2 << endl;
        }
        cout << endl << "Vencedor: ";
        if(set1 == 3) cout << t1.getNome() << endl;
        else cout << t2.getNome() << endl;
        return true;
    }
    return false;
}