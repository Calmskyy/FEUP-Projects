#include "camiao.h"
using namespace std;

int Camiao::globalID = 0;

Camiao::Camiao(int c, string marca, double km_percorridos) {
    id = ++globalID;
    this->capacidade = c;
    this->marca = marca;
    this->km_percorridos = km_percorridos;
}


int Camiao::getId() const {return id;}

int Camiao::getCapacidade() const {return capacidade;}

string Camiao::getMarca() const {return marca;}

void Camiao::setCapacidade(int capacidade) {this->capacidade = capacidade;}

void Camiao::setId(int id) {this->id = id;}

Perigosos::Perigosos(int c, string marca,double km_percorridos, string nivel): Camiao(c,marca,km_percorridos) {
    this->nivel = nivel;
}

Congelacao::Congelacao(int c, string marca, double km_percorridos, int tempMin): Camiao(c,marca,km_percorridos) {
    this->tempMin = tempMin;
}

Normal::Normal(int c, string marca, double km_percorridos) : Camiao(c, marca, km_percorridos){}

Animais::Animais(int c, string marca, double km_percorridos, int numAnimais) : Camiao(c,marca, km_percorridos){
    this->numAnimais = numAnimais;
}

int Animais::getNumAnimais() const {return numAnimais;}

string Perigosos::getNivel() const {return nivel;}

int Congelacao::getTempMin() const {return tempMin;}

CamiaoRepetido::CamiaoRepetido(string marca, int id) {
    this->marca = marca;
    this->id = id;
}

int CamiaoRepetido::getId() const {return id;}

string CamiaoRepetido::getMarca() const {return marca;}

CamiaoInexistente::CamiaoInexistente(int id, string marca) {
    this->id = id;
    this->marca = marca;
}

int CamiaoInexistente::getId() const { return id;}

string CamiaoInexistente::getMarca() const {return marca;}

bool Camiao::operator==(const Camiao c2) {
    return (this->id == c2.getId() && this->marca == c2.getMarca());
}

double Camiao::getKmPercorridos() const {return km_percorridos;}

ostream& operator<<(ostream &out, const Camiao &c2) {
    out << "Identificador:" << c2.getId() << endl;
    out << "Marca:" << c2.getMarca() << endl;
    return out;
}

void Camiao::setMarca(string marca) {this->marca = marca;}

void Camiao::setkmPercorridos(double km) {this->km_percorridos = km;}

void Perigosos::setNivel(string nivel) {this->nivel = nivel;}

void Congelacao::setTempMin(int tempmin) {this->tempMin = tempmin;}

void Animais::setNumAnimais(int numAnimais) {this->numAnimais = numAnimais;}

CamiaoOcupado::CamiaoOcupado(Camiao *ca) {
    this->ca = ca;
}

int CamiaoOcupado::getId() const {return this->ca->getId();}


