#ifndef VOLEI_H
#define VOLEI_H
#include <string>

// Classe abstrata
class Jogador{
    std::string nome;
    int ataque, passe, defesa, modificador;
protected:
    Jogador(std::string nome, int ataque, int passe, int defesa, int modificador):
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
    Levantador(std::string nome, int ataque, int passe, int defesa, int modificador):
    Jogador(nome, ataque, passe, defesa, modificador){}
    int pegarHabilidadeIndividual();
};

class Oposto:public Jogador{
public:
    Oposto(std::string nome, int ataque, int passe, int defesa, int modificador):
    Jogador(nome, ataque, passe, defesa, modificador){}
    int pegarHabilidadeIndividual();
};

class Libero:public Jogador{
public:
    Libero(std::string nome, int ataque, int passe, int defesa, int modificador):
    Jogador(nome, ataque, passe, defesa, modificador){}
    int pegarHabilidadeIndividual();
};

class Meia:public Jogador{
public:
    Meia(std::string nome, int ataque, int passe, int defesa, int modificador):
    Jogador(nome, ataque, passe, defesa, modificador){}
    int pegarHabilidadeIndividual();
};

class Ponta:public Jogador{
public:
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
};

class Partida{
  	bool ponto(Time &t1, Time &t2, bool saque);  // saque: false -> time t1 saca; true -> time t2 saca
  	bool realizarSet(Time &t1, Time &t2, int set1, int set2);
public:
    bool realizar(Time &t1, Time &t2);
};

#endif