#include "Oficina.h"
#include <iostream>
using namespace std;

Oficina::Oficina(string nome, list<string> marcas, unsigned disponibilidade) {
    Date atual = getCurrentTime();
    this->nome = nome;
    this->marcas = marcas;
    this-> disponibilidade = disponibilidade;
    this->next_available_date = atual.addDays(disponibilidade);
}

unsigned int Oficina::getDisponibilidade() const {return disponibilidade;}

void Oficina::setDisponibilidade(const unsigned d) {
    this->disponibilidade = disponibilidade;
}

string Oficina::getNome() const {return nome;}

list <string> Oficina::getMarcas() const {return marcas;}

void Oficina::setMarcas(list<string> marcas) {this->marcas = marcas;}

void Oficina::setNome(const string nome) {this->nome = nome;}

bool Oficina::operator==(const Oficina &o1) {return this->getNome() == o1.nome && this->disponibilidade == o1.disponibilidade;}

bool Oficina::operator<(const Oficina &o1) const {return this->disponibilidade > o1.disponibilidade;}

ostream& operator<<(ostream &out, const Oficina &o) {
    out << "Nome - " << o.nome << endl;
    out << "Especializada nas marcas: \n";
    for (string m: o.marcas)
        out << m << endl;
    out << "Disponivel em " << o.disponibilidade << " dias\n";
    out << "------------------------------------\n";
    return  out;
}

Date Oficina::getDateAvailable() const {return this->next_available_date;}

void Oficina::setDateAvailable(Date &d1) {this->next_available_date = d1;}

bool Oficina::addServico(string marca, string tipoServico) {
    auto it = find(marcas.begin(), marcas.end(), marca);
    if (tipoServico != "normal" && it == marcas.end()) //servico especifico e a marca nao e abrangida pela oficina
        return false;
    unsigned  disp;
    if (tipoServico == "normal") {
        disponibilidade += 1;
        disp = 1;
    }
    else {
        disponibilidade += 3;
        disp = 3;
    }
    next_available_date = next_available_date.addDays(disp);
    return true;
}
