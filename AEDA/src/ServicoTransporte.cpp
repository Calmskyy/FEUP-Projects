#include "ServicoTransporte.h"
using namespace std;

double ServicoTransporte::NormalMultiplicador = 1;

double ServicoTransporte::CongelacaoMultiplicador = 2.5;

double ServicoTransporte::AnimaisMultiplicador = 3;

double ServicoTransporte::PerigososMultiplicador = 5;

string ServicoTransporte::getDestino() const {return destino;}

string ServicoTransporte::getOrigem() const {return origem;}

int ServicoTransporte::getId() const {return id;}

void ServicoTransporte::setHorario(string horario) {this->horario = horario;}

int ServicoTransporte::globalID = 0;

ServicoTransporte::ServicoTransporte(string origem, string destino, string tipo_camioes, vector<Camiao *> camioes, string horario, Date data, unsigned disponivel, unsigned n_horas) {
    this->id = ++globalID;
    this->origem = origem;
    this->destino = destino;
    this->camioes = camioes;
    this->horario = horario;
    this->tipo_camioes = tipo_camioes;
    this->data = data;
    this->servicoDisponivel = disponivel;
    this->n_horas = n_horas;
}

Date ServicoTransporte::getDate() const {return data;}

void ServicoTransporte::setDate(const Date &d) {this->data = d;}

void ServicoTransporte::setDestino(string destino) {
    this->destino = destino;
}

void ServicoTransporte::setOrigem(string origem) {
    this->origem = origem;
}

bool ServicoTransporte::operator==(ServicoTransporte st2) {
    return (this->id == st2.getId() && this->origem == st2.getOrigem() && this->destino == st2.getDestino());
}

string ServicoTransporte::getTipo() const {return tipo_camioes;}

vector <Camiao *> ServicoTransporte::getCamioes() const {return camioes;}

string ServicoTransporte::getHorario() const {return horario;}

ostream& operator<<(ostream &out, const ServicoTransporte &st) {
    out << "Identificador: " << st.getId() << endl;
    out << "Origem: " << st.getOrigem() << " ; Destino: " << st.getDestino() << endl;
    out << "Horario: " << st.getHorario() << endl;
    out << "Numero de horas estimadas: " << st.getHoras() << endl;
    return out;
}

void ServicoTransporte::setCamioes(vector<Camiao *> camioes) {this->camioes = camioes;}

double ServicoTransporte::getDistancia(map<pair<string, string>, double> distancias) const{
    for (auto it = distancias.begin(); it != distancias.end(); it++){
        if (((*it).first.first == origem && (*it).first.second == destino) || ((*it).first.first == destino && (*it).first.second == origem))
            return (*it).second;
    }
    return 0;
}

double ServicoTransporte::getPreco(map<pair<string,string>,double > distancias) const {
    double result = this->getDistancia(distancias)*this->getCamioes().size();
    if (this->getTipo() == "perigosos") result *= this->PerigososMultiplicador;
    else if (this->getTipo() == "congelacao") result *= this->CongelacaoMultiplicador;
    else if (this->getTipo() == "normal") result*= this->NormalMultiplicador;
    else if (this->getTipo() == "animais") result *= this->AnimaisMultiplicador;
    return result;
}

void ServicoTransporte::setId(int id) {this->id = id;}

bool Date::operator==(const Date &d1) {
    return (d1.ano == this->ano && d1.mes == this->mes && d1.dia == this->dia);
}

void ServicoTransporte::setDisponibilidade(unsigned b) {
    this->servicoDisponivel = b;
}

//verifica se o servico se encontra disponivel
unsigned ServicoTransporte::getDisponibilidade() const {
    return servicoDisponivel;
}

bool Date::operator<(const Date &d1) {
    int aux1 = this->ano*365 + this->mes*30 +this->dia;
    int aux2 = d1.ano*365 + d1.mes*30 + d1.dia;
    return aux1<aux2;
}

LocalizacaoIndisponivel::LocalizacaoIndisponivel(string nome) {this->nome = nome;}

string LocalizacaoIndisponivel::getNome() const {return nome;}

CamioesIndisponiveis::CamioesIndisponiveis() {}

ServicoInexistente::ServicoInexistente(string origem, string destino) {
    this->origem = origem;
    this->destino = destino;
}

string ServicoInexistente::getDestino() const {return destino;}

string ServicoInexistente::getOrigem() const {return origem;}

MotoristasIndisponiveis::MotoristasIndisponiveis(string origem, string destino) {
    this->origem = origem;
    this->destino = destino;
}

Date Date::operator+(const Date &d1) {
    Date result;
    result.ano = this->ano + d1.ano;
    result.mes = this->mes + d1.mes;
    if (result.mes > 12){
        result.ano += (result.mes / 12);
        result.mes %= 12;
    }
    result.dia = this->dia + d1.dia;
    if (result.dia > 31){
        result.dia %= 31;
        result.mes++;
    }
    return result;
}

Date Date::addDays(unsigned &d) {
    Date result;
    result.dia = this->dia+d;
    result.ano = this->ano;
    result.mes = this->mes;
    if (result.dia > 30){
        result.mes ++;//= (result.dia / 30);
        result.dia %= 30;
    }
    if (result.mes > 12){
        result.ano ++;//= (result.mes / 12);
        result.mes %= 12;
    }
    return result;
}

unsigned ServicoTransporte::getHoras() const {return this->n_horas;}

void ServicoTransporte::setHoras(unsigned h) {this->n_horas = h;}

bool ServicoTransporte::eliminaCamiaoServico(Camiao *ca) {
    for (auto it = camioes.begin(); it != camioes.end();it++){
        if (**it == *ca) {
            camioes.erase(it);
            return true;
        }
    }
    return false;
}

