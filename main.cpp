#include <iostream>

using namespace std;

class Jogador{
    string nome;
    int ataque, passe, defesa;
protected:
    Jogador(string nome, int ataque, int passe, int defesa):
    nome(nome), ataque(ataque), passe(passe), defesa(defesa){}
public:
    int getAtaque(){ return ataque; }
    int getPasse(){ return passe; }
    int getDefesa(){ return defesa; }
    virtual int pegarHabilidadeIndividual(){}
};

class Levantador:public Jogador{
    int melhorjogador;
public:
    Levantador(string nome, int ataque, int passe, int defesa, int melhorjogador):
    Jogador(nome, ataque, passe, defesa), melhorjogador(melhorjogador){}
    int pegarHabilidadeIndividual(){
        return getAtaque() + 6*getPasse() + 3*getDefesa() + 10*melhorjogador;
    }
};

class Oposto:public Jogador{
    int maisMarcouPontos;
public:
    Oposto(string nome, int ataque, int passe, int defesa, int maisMarcouPontos):
    Jogador(nome, ataque, passe, defesa), maisMarcouPontos(maisMarcouPontos){}
    int pegarHabilidadeIndividual(){
        return 6*getAtaque() + getPasse() + 3*getDefesa() + 20*maisMarcouPontos;
    }
};

class Libero:public Jogador{
    int melhorQualPasse;
public:
    Libero(string nome, int ataque, int passe, int defesa, int melhorQualPasse):
    Jogador(nome, ataque, passe, defesa), melhorQualPasse(melhorQualPasse){}
    int pegarHabilidadeIndividual(){
        int pontos = 5*getPasse() + 5*getDefesa();
        int partidas = melhorQualPasse;
        while(partidas >= 10){
            pontos *= 2;
            partidas -= 10;
        }
        return pontos;
    }
};

class Meia:public Jogador{
    int naoBloqueio;
public:
    Meia(string nome, int ataque, int passe, int defesa, int naoBloqueio):
    Jogador(nome, ataque, passe, defesa), naoBloqueio(naoBloqueio){}
    int pegarHabilidadeIndividual(){
        return 4*getAtaque() + getPasse() + 3*getDefesa() - naoBloqueio;
    }
};

class Ponta:public Jogador{
public:
    Ponta(string nome, int ataque, int passe, int defesa):
    Jogador(nome, ataque, passe, defesa){}
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
public:
    bool realizar(Time &t1, Time &t2){
        if(t1.getnJogadores()==7 && t2.getnJogadores()==7){
            if(t1.pegarHabilidadeTotal()>t2.pegarHabilidadeTotal()){
                cout << t1.getNome();
            }
            else if(t1.pegarHabilidadeTotal()<t2.pegarHabilidadeTotal()){
                cout << t2.getNome();
            }
            else{
                cout << "empate" << endl;
            }
            return true;
        }
        return false;
    }
};

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

    //Partida
    cout << "Partida: " << time1.getNome() << " versus " << time2.getNome() << endl;
    cout << "O vencedor é: ";
    Partida p;
    p.realizar(time1, time2);
    cout << endl;

    return 0;
}