#include <iostream>
#include <cstdlib>
#include <ctime>
#include "volei.h"

using namespace std;

int Levantador::posicao = 0;
int Oposto::posicao = 1;
int Libero::posicao = 2;
int Meia::posicao = 3;
int Ponta::posicao = 4;

inline int Levantador::pegarHabilidadeIndividual(){
    return getAtaque() + 6*getPasse() + 3*getDefesa() + 10*getModificador();
}

inline int Oposto::pegarHabilidadeIndividual(){
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

inline int Meia::pegarHabilidadeIndividual(){
    return 4*getAtaque() + getPasse() + 3*getDefesa() - getModificador();
}

inline int Ponta::pegarHabilidadeIndividual(){
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

inline bool Time::alterarJogador(int n, Jogador &j){
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

inline Jogador *Time::pegarJogador(int pos){
    if(nJogadores >= pos) return jogadores[pos];
    return NULL;
}

inline bool Partida::ponto(Time &t1, Time &t2, bool saque){
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
        int checarPosicao[10] = {0};
        for(int i=0; i<7; i++){
            Jogador *j;
            j = t1.pegarJogador(i);
            checarPosicao[j->getPosicao()]++;
            j = t2.pegarJogador(i);
            checarPosicao[j->getPosicao() + 5]++;
        }
        for(int i=0; i<10; i++){
            if(i%5 == 3 || i%5 == 4){
                if(checarPosicao[i] != 2) return false;
            }
            else{
                if(checarPosicao[i] != 1) return false;
            }
        }
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