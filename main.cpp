#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Classe abstrata
class Jogador{
    string nome;
    int ataque, passe, defesa, modificador;
protected:
    Jogador(string nome, int ataque, int passe, int defesa, int modificador):
    nome(nome), ataque(ataque), passe(passe), defesa(defesa), modificador(modificador){}
public:
    int getAtaque(){ return ataque; }
    int getPasse(){ return passe; }
    int getDefesa(){ return defesa; }
    int getModificador(){ return modificador; }
    virtual int pegarHabilidadeIndividual(){}  // vínculo dinâmico, pois queremos usar o método das subclasses
};

class Levantador:public Jogador{
public:
    Levantador(string nome, int ataque, int passe, int defesa, int modificador):
    Jogador(nome, ataque, passe, defesa, modificador){}
    int pegarHabilidadeIndividual(){
        return getAtaque() + 6*getPasse() + 3*getDefesa() + 10*getModificador();
    }
};

class Oposto:public Jogador{
public:
    Oposto(string nome, int ataque, int passe, int defesa, int modificador):
    Jogador(nome, ataque, passe, defesa, modificador){}
    int pegarHabilidadeIndividual(){
        return 6*getAtaque() + getPasse() + 3*getDefesa() + 20*getModificador();
    }
};

class Libero:public Jogador{
public:
    Libero(string nome, int ataque, int passe, int defesa, int modificador):
    Jogador(nome, ataque, passe, defesa, modificador){}
    int pegarHabilidadeIndividual(){
        int pontos = 5*getPasse() + 5*getDefesa();
        int partidas = getModificador();
        while(partidas >= 10){
            pontos *= 2;
            partidas -= 10;
        }
        return pontos;
    }
};

class Meia:public Jogador{
public:
    Meia(string nome, int ataque, int passe, int defesa, int modificador):
    Jogador(nome, ataque, passe, defesa, modificador){}
    int pegarHabilidadeIndividual(){
        return 4*getAtaque() + getPasse() + 3*getDefesa() - getModificador();
    }
};

class Ponta:public Jogador{
public:
    Ponta(string nome, int ataque, int passe, int defesa):
    Jogador(nome, ataque, passe, defesa, 0){}
    int pegarHabilidadeIndividual(){
        return 4*getAtaque() + 3*getPasse() + 3*getDefesa();
    }
};

class Time{
    string nome;
    Jogador **jogadores;
    int nJogadores;
public:
    Time(string nome):nome(nome){
        jogadores = new Jogador*[7];
        nJogadores = 0;
    }
    ~Time(){
        delete []jogadores;
    }
    Time(const Time &t){
        nome = t.nome;
        nJogadores = t.nJogadores;
        jogadores = new Jogador*[7];
        for(int i=0; i<nJogadores; i++){
            jogadores[i] = t.jogadores[i];
        }
    }
    int getnJogadores(){ return nJogadores; }
    string getNome(){ return nome; }
    bool inserirJogador(Jogador &j){
        if(nJogadores < 7){
            jogadores[nJogadores++] = &j;
            return true;
        }
        return false;
    }
    bool alterarJogador(int n, Jogador &j){ //Troca o n-ésimo jogador por outro
        if(n <= nJogadores){
            jogadores[n] = &j;
            return true;
        }
        return false;
    }
    int pegarHabilidadeTotal(){
        int total=0;
        if(nJogadores == 7){
            for(int i=0; i<7; i++){
                total += jogadores[i]->pegarHabilidadeIndividual();
            }
            return total;
        }
        return -1;
    }
};

class Partida{
  	bool ponto(Time &t1, Time &t2, bool saque){  // saque: false -> time t1 saca; true -> time t2 saca
  		float hab1 = t1.pegarHabilidadeTotal(), hab2 = t2.pegarHabilidadeTotal(), aleatorio;
      	if (saque) hab2 *= 1.25;
      	else hab1 *= 1.25; 
    	aleatorio = (rand()%((int) hab1*100 + (int) hab2*100) + 1) / 100;
		if (aleatorio <= hab1) return false; 
		return true;
  	}
  	bool realizarSet(Time &t1, Time &t2, int set1, int set2){
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
public:
    bool realizar(Time &t1, Time &t2){
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
};

int main(){
    srand(time(NULL));
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

    //Partida
    Partida p;
    p.realizar(time1, time2);

    return 0;
}