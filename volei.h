#ifndef VOLEI_H
#define VOLEI_H
#include <string>

// Classe abstrata
class Jogador{
    int posicao;
    std::string nome;
    int ataque, passe, defesa, modificador;
    friend class Partida;
protected:
    Jogador(std::string nome, int ataque, int passe, int defesa, int modificador):
    nome(nome), ataque(ataque), passe(passe), defesa(defesa), modificador(modificador){}
public:
    virtual int getPosicao(){ return posicao; }
    int getAtaque(){ return ataque; }
    int getPasse(){ return passe; }
    int getDefesa(){ return defesa; }
    int getModificador(){ return modificador; }
    virtual int pegarHabilidadeIndividual() = 0;  // vínculo dinâmico, pois queremos usar o método das subclasses
};

class Levantador:public Jogador{
    static int posicao;
public:
    int getPosicao(){ return posicao; }
    Levantador(std::string nome, int ataque, int passe, int defesa, int modificador):
    Jogador(nome, ataque, passe, defesa, modificador){}
    int pegarHabilidadeIndividual();
};

class Oposto:public Jogador{
    static int posicao;
public:
    int getPosicao(){ return posicao; }
    Oposto(std::string nome, int ataque, int passe, int defesa, int modificador):
    Jogador(nome, ataque, passe, defesa, modificador){}
    int pegarHabilidadeIndividual();
};

class Libero:public Jogador{
    static int posicao;
public:
    int getPosicao(){ return posicao; }
    Libero(std::string nome, int ataque, int passe, int defesa, int modificador):
    Jogador(nome, ataque, passe, defesa, modificador){}
    int pegarHabilidadeIndividual();
};

class Meia:public Jogador{
    static int posicao;
public:
    int getPosicao(){ return posicao; }
    Meia(std::string nome, int ataque, int passe, int defesa, int modificador):
    Jogador(nome, ataque, passe, defesa, modificador){}
    int pegarHabilidadeIndividual();
};

class Ponta:public Jogador{
    static int posicao;
public:
    int getPosicao(){ return posicao; }
    Ponta(std::string nome, int ataque, int passe, int defesa):
    Jogador(nome, ataque, passe, defesa, 0){}
    int pegarHabilidadeIndividual();
};

class Time{
    std::string nome;
    Jogador **jogadores;
    int nJogadores;
public:
    Time(std::string nome):nome(nome){
        jogadores = new Jogador*[7];
        nJogadores = 0;
    }
    ~Time(){
        delete []jogadores;
    }
    Time(const Time &t);
    int getnJogadores(){ return nJogadores; }
    std::string getNome(){ return nome; }
    bool inserirJogador(Jogador &j);
    bool alterarJogador(int n, Jogador &j); //Troca o n-ésimo jogador por outro
    int pegarHabilidadeTotal();
    Jogador *pegarJogador(int pos);
};

class Partida{
  	bool ponto(Time &t1, Time &t2, bool saque);  // saque: false -> time t1 saca; true -> time t2 saca
  	bool realizarSet(Time &t1, Time &t2, int set1, int set2);
public:
    bool realizar(Time &t1, Time &t2);
};

#endif