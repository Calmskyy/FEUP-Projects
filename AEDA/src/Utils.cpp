#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "ServicoTransporte.h"
#include "Utils.h"
#include <fstream>


using namespace std;
string removeSpaces(string fullstring){
    size_t pos = fullstring.find_first_not_of(' ');
    if (pos != 0)
        fullstring.erase(0, pos);
    fullstring.erase(fullstring.find_last_not_of(' ') + 1, string::npos);
    return fullstring;
}

//decompor a string obtida para os identificadores nos seus constituintes
vector<int> stringSplit(string fullstring, char delimiter){
    vector<int> result;
    size_t aux;
    fullstring.push_back(delimiter);
    while (fullstring.size() != 0) {
        aux = fullstring.find(delimiter);
        result.push_back(stoi(removeSpaces(fullstring.substr(0, aux))));
        fullstring = fullstring.substr(aux, fullstring.npos);
        fullstring.erase(0,1);
    }
    return result;
}
vector <ServicoTransporte> servicesBuilder(string packs_str, vector<ServicoTransporte> servicos){
    vector <ServicoTransporte> result;
    if (packs_str == "-")
        return result;
    for (int i: stringSplit(packs_str, ';')){
        for (ServicoTransporte serv: servicos){
            if (i == serv.getId())
                result.push_back(serv);
        }
    }
    return result;
}


map<int , bool> handle_horario(string horario){
    bool control = false;
    map<int , bool> res;
    for (int i = 0; i<25; i++){
        size_t idx = horario.find(to_string(i));
        if (idx != string::npos && idx != horario.at(horario.size()-1)){

        }
        cout << i << " - " << res[i] << endl;
    }
    return res;
}

string to_string_id(vector<ServicoTransporte> servicos) {
    string result = "";
    if (servicos.size() == 0) {
        result += "-";
        return result;
    }
    for (ServicoTransporte s: servicos){
        result += to_string(s.getId());
    result += " ; ";
    }
    return result.substr(0,result.size()-3);
}

pair<string,string> distanceSplitter(string info){
    pair <string, string> result;
    string fst, scnd;
    fst = info.substr(0, info.find("->"));
    result.first = removeSpaces(fst);
    info.erase(0, info.find("->")+2);
    scnd =  info.substr(0, info.find("-"));
    result.second = removeSpaces(scnd);
    return result;
}

pair<string, string> toPair(string horario) {
    pair <string, string> result;
    string fst, scnd;
    fst = horario.substr(0, horario.find("->"));
    result.first = removeSpaces(fst);
    horario.erase(0, horario.find("->")+2);
    result.second = removeSpaces(horario);
    return result;
}

vector<char> categoryVector(string categorias) {
    vector<char> result;
    categorias.push_back(';');
    vector<char> aux;
    aux.push_back('l');
    while (categorias.size() != 0) {
        char helper = removeSpaces(categorias.substr(0, categorias.find(';'))).at(0);
        if (find(aux.begin(), aux.end(), helper) != aux.end()) {
            categorias = categorias.substr(categorias.find(';'), categorias.npos);
            categorias.erase(0,1);
            continue;
        }
        aux.push_back(helper);
        result.push_back(helper);
        categorias = categorias.substr(categorias.find(';'), categorias.npos);
        categorias.erase(0,1);
    }
    return result;
}

bool compareTime(istringstream &time, istringstream &inicio, istringstream &fim) {
    string token;
    unsigned tempo = 0, tempo_inicio = 0, tempo_fim = 0, hora, minutos, hora_inicio, minutos_inicio, hora_fim, minutos_fim;
    unsigned aux = 0;
    while (getline(time, token, ':')) {
        if (!aux) {
            hora = stoi(token);
            aux++;
        }
        else minutos = stoi(token);
    }
    aux = 0;
    while (getline(inicio, token, ':')) {
        if (!aux) {
            hora_inicio = stoi(token);
            aux++;
        }
        else minutos_inicio = stoi(token);
    }
    aux = 0;
    while (getline(fim, token, ':')) {
        if (!aux) {
            hora_fim = stoi(token);
            aux++;
        }
        else minutos_fim = stoi(token);
    }
    tempo = hora*60*60 + minutos*60;
    tempo_inicio = hora_inicio*60*60 + minutos_inicio*60;
    tempo_fim = hora_fim*60*60 + minutos_fim*60;

    if (hora_inicio > hora_fim && tempo <= (23*60*60 + 59*60) && tempo >= tempo_inicio)
        return 1;
    else if (hora_inicio > hora_fim && tempo >= 0 && tempo <= tempo_fim)
        return 1;
    else return tempo_inicio <= tempo && tempo <= tempo_fim;
}


double distanceFinder(string origem, string destino, map<pair<string, string>,double>  distancias){
    for (auto it = distancias.begin(); it != distancias.end(); it++){
        if ((it->first.first == origem && it->first.second == destino) || (it->first.first == destino && it->first.second == origem))
            return it->second;
    }
}

string getTipoCamiao(Camiao* ca){
    string res;
    Perigosos* np = dynamic_cast<Perigosos*>(ca);
    Normal* nn = dynamic_cast<Normal*>(ca);
    Congelacao* nc = dynamic_cast<Congelacao*>(ca);
    Animais* na = dynamic_cast<Animais*>(ca);
    if (np != nullptr) res = "perigosos";
    else if (nn != nullptr) res = "normal";
    else if (na != nullptr) res = "animais";
    else if (nc != nullptr) res = "congelacao";
    return res;
}

vector<Camiao *> camioesBuilder(string ids, vector<Camiao *> camioes, string tipo){
    vector<Camiao*> res;
    if (ids == "-")
        return res;
    for (int i: stringSplit(ids,';')){
        for (Camiao *c: camioes){
            if (c->getId() == i && getTipoCamiao(c) == tipo)
                res.push_back(c);
        }
    }

    return res;
}

string to_string_camioes(vector<Camiao *> camioes) {
    string result = "";
    if (camioes.size() == 0) {
        result += "-";
        return result;
    }
    for (Camiao *c: camioes) {
        result += to_string(c->getId());
        result += " ; ";
    }
    return result.substr(0, result.size() - 3);
}

int menuValidInput(string message ,int min,int max) {
    bool valid = false;
    int input;
    cout << message;
    cin >> input;
    if(cin.fail() || (input < min  || input > max)){
        cin.clear();
        cin.ignore(1000, '\n');
    }
    else
        valid = true;
    while(!valid) {
        if (max - min == 0) cout << "Valor INVALIDO, escolha " << min << "." << endl;
        else cout << "Valor INVALIDO, escolha um entre [" << min << "," << max << "]." << endl;
        cout << message;
        cin >> input;
        if(cin.fail() || (input < min  || input > max)){
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else
            valid = true;
    }
    cin.ignore(1000, '\n');
    return input;
}

double menuValidInput(string message ,double min,double max) {
    bool valid = false;
    double input;
    cout << message;
    cin >> input;
    if(cin.fail() || (input < min  || input > max)){
        cin.clear();
        cin.ignore(1000, '\n');
    }
    else
        valid = true;
    while(!valid) {
        if (max - min == 0) cout << "Valor INVALIDO, escolha " << min << "." << endl;
        else cout << "Valor INVALIDO, escolha um entre [" << min << "," << max << "]." << endl;
        cout << message;
        cin >> input;
        if(cin.fail() || (input < min  || input > max)){
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else
            valid = true;
    }
    cin.ignore(1000, '\n');
    return input;
}

string nivelVerifier(){
    bool valid = false;
    vector <string> control = {"inflamavel", "toxico", "quimico"};
    string input;
    while (!valid){
        cout << "nivel:";
        getline(cin, input);
        auto it = find(control.begin(), control.end(), input);
        if (cin.fail() || it == control.end()){
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else
            valid = true;
    }
    return input;
}

string camioesTipoVerifier(vector<Camiao *> camioes, vector<Camiao *>& aux){ //vetor aux possui os camioes do primeiro vetor que pertencem ao tipo selecionado
    bool valid = false;
    aux.clear();
    vector <string> control = {"perigosos", "congelacao", "normal", "animais"};
    string input;
    while (!valid) {
        cout << "Tipo (TIPOS: perigosos, congelacao, normal ou animais):";
        getline(cin, input);
        input = removeSpaces(input);
        auto it = find(control.begin(), control.end(), input);
        if (cin.fail() || it == control.end()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Tipo invalido (TIPOS: perigosos, congelacao, normal ou animais).\n";
        }
        else  valid = true;
        if (input == "perigosos") {
            for (Camiao* ca: camioes) {
                Perigosos *np = dynamic_cast<Perigosos *>(ca);
                if (np != nullptr){
                    aux.push_back(ca);
                }
            }
        }

        else if (input == "congelacao"){
            for (Camiao* ca: camioes){
                Congelacao* np = dynamic_cast<Congelacao*>(ca);
                if (np != nullptr){
                    aux.push_back(ca);
                }
            }
        }

        else if (input == "normal"){
            for (Camiao* ca: camioes){
                Normal* np = dynamic_cast<Normal*>(ca);
                if (np != nullptr){
                    aux.push_back(ca);
                }
            }
        }

        else if (input == "animais"){
            for (Camiao* ca: camioes){
                Animais* np = dynamic_cast<Animais*>(ca);
                if (np != nullptr) {
                    aux.push_back(ca);
                }
            }
        }
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return input;
}

int GetMaxId(vector<ServicoTransporte> stvect){
    int result = stvect.at(0).getId();
    for (ServicoTransporte st: stvect){
        if (st.getId() > result)
            result = st.getId();
    }
    return result;
}

bool checkHorario(string horario) {
    unsigned aux = 0;
    if (horario.size() == 4) {
        int time = 0;
        int time1 = 0;
        for (char c: horario) {
            if (aux == 0) {
                if (!isdigit(c)) return true;
                time += c - '0';
            }
            if (aux == 1) {
                if (c != ':') return true;
            }
            if (aux == 2 || aux == 3) {
                if (!isdigit(c)) return true;
                time1 += c - '0';
            }
            aux++;
        }
        if (time < 0 || time >= 24) return true;
        if (time1 < 0 || time1 > 60) return true;
    }
    else if (horario.size() == 5) {
        int time = 0;
        int time1 = 0;
        for (char c: horario) {
            if (aux == 0 || aux == 1) {
                if (!isdigit(c)) return true;
                time += c - '0';
            }
            if (aux == 2) {
                if (c != ':') return true;
            }
            if (aux == 3 || aux == 4) {
                if (!isdigit(c)) return true;
                time1 += c - '0';
            }
            aux++;
        }
        if (time < 0 || time >= 24) return true;
        if (time1 < 0 || time1 > 60) return true;
    }
    else return true;
    return false;
}

string inputHorario(string mensagem) {
    bool valid = false;
    string input;
    cout << mensagem;
    cin >> input;
    if(cin.fail() || checkHorario(input)){
        cin.clear();
        cin.ignore(1000, '\n');
    }
    else
        valid = true;
    while(!valid) {
        cout << "Valor de horas INVALIDO, escreva as horas de forma (HH:MM)." << endl;
        cout << mensagem;
        cin >> input;
        if(cin.fail() || checkHorario(input)){
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else
            valid = true;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return input;
}

int inputNIF(string mensagem) {
    bool valid = false;
    int input;
    cout << mensagem;
    cin >> input;
    if(cin.fail() || to_string(input).length() != 9 || to_string(input).at(0) == '0'){
        cin.clear();
        cin.ignore(1000, '\n');
    }
    else
        valid = true;
    while(!valid) {
        cout << "Valor de nif INVALIDO, escreva um nif com 9 digitos." << endl;
        cout << mensagem;
        cin >> input;
        if(cin.fail() || to_string(input).length() != 9 || to_string(input).at(0) == '0'){
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else
            valid = true;
    }
    cin.ignore(1000, '\n');
    return input;
}

string toStringServicos(vector<ServicoTransporte> servicos) {
    string res;
    for (size_t i = 0; i < servicos.size(); i++) {
        if (i == servicos.size() - 1)
            res += servicos.at(i).getId();
        else {
            res += servicos.at(i).getId();
            res += " ; ";
        }
    }
    return res;
}

Date dateSplitter(string data){
    Date res;
    res.dia = stoi(data.substr(0, 2));
    res.mes = stoi(data.substr(3, 5));
    res.ano = stoi(data.substr(6));
    return res;
}

string toStringDate(const Date& d){
    stringstream res;
    string dia = to_string(d.dia),mes = to_string(d.mes);
    if (to_string(d.dia).size()<2){
        dia = "0" + to_string(d.dia);
    }
    if (to_string(d.mes).size()<2){
        mes = "0" + to_string(d.mes);
    }

    res << dia << "/" << mes << "/" << d.ano;
    return res.str();
}

Date getCurrentTime(){
    Date result;
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);
    result.ano = timePtr->tm_year+1900;
    result.mes = timePtr->tm_mon+1;
    result.dia = timePtr->tm_mday;
    return result;
}

bool DateVerifier(string date){
    unsigned aux = 0;
    if (date.length() == 10) {
        for (char c : date) {
            if (aux == 2 || aux == 5) {
                if (c != '/') return false;
            }
            else {
                if (!isdigit(c)) return false;
            }
            aux++;
        }
        return true;
    }
}

string menuDateInput(string mensagem){
    bool valid = false;
    string date_str;
    cout << "Data (DD/MM/AAAA):";
    cin >> date_str;
    if (cin.fail() || !DateVerifier(date_str) || dateSplitter(date_str).mes > 12 || dateSplitter(date_str).dia > 31){
        cin.clear();
        cin.ignore(1000, '\n');
    }
    else valid = true;
    while (!valid){
        cout << "Data invalida. Introduza no formato (DD/MM/AAAA)." << endl;
        cout << mensagem;
        cin >> date_str;
        if (cin.fail() || !DateVerifier(date_str) || dateSplitter(date_str).mes > 12 || dateSplitter(date_str).dia > 31){
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else valid = true;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return date_str;
}


int BinarySearch(const vector<char> &v, char x) {
    int left = 0;
    int right = v.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (v.at(mid) < x) left = mid + 1;
        else if (x < v.at(mid)) right = mid - 1;
        else return mid;
    }
    return -1;
}

Motorista* findMotoristaIndex(BST<Motorista> motoristas, int idx){
    Motorista* m;
    BSTItrIn <Motorista> it(motoristas);
    while(!it.isAtEnd()){
        if (it.retrieve().getId() == idx) m = new Motorista(it.retrieve());
        it.advance();
    }
    return m;

}

int activeCheck(Cliente c1) {
    for (auto s : c1.getServicos()) {
        int ano = s.getDate().ano;
        int mes = s.getDate().mes;
        int dia = s.getDate().dia;
        ano += 1;
        Date d1;
        d1.ano = ano; d1.mes = mes; d1.dia = dia;
        if (!(d1 < getCurrentTime()))
            return 1;
    }
    return 0;
}

/*bool verificaInatividade(const Cliente& c1, vector <ServicoTransporte> vst){
    vector <int> dates;
    int current = getCurrentTime().ano*365 + getCurrentTime().mes*30 + getCurrentTime().dia;
    for (ServicoTransporte st: vst){
        int elem = 365*st.getDate().ano;
        elem += 30*st.getDate().mes;
        elem += st.getDate().dia;
        dates.push_back(elem);
    }
    int last = *max_element(dates.begin(), dates.end());
    return current - last > 365; //ultimo servico ocorre ha mais de um ano ==> cliente inativo
}*/

list<string> listStringSplit(string fullstring, char delimiter){
    list<string> result;
    size_t aux;
    fullstring.push_back(delimiter);
    while (!fullstring.empty()) {
        aux = fullstring.find(delimiter);
        result.push_back(removeSpaces(fullstring.substr(0, aux)));
        fullstring = fullstring.substr(aux, fullstring.npos);
        fullstring.erase(0,1);
    }
    return result;
}

string toStringMarcas(list <string> marcas){
    stringstream ss;
    for (string str: marcas){
        ss << str << " ; ";
    }
    string result = ss.str();
    return result.substr(0, result.size()-2);
}

Camiao* findCamioesID(vector <Camiao*> camioes, int id){
    for (Camiao* c: camioes){
        if (c->getId() == id) return c;
    }
    return NULL;
}

int getNumDays(Date d){
    Date current_day = getCurrentTime();
    if (current_day.ano == d.ano){
        if (current_day.mes == d.mes) return d.dia - current_day.dia;
        else
            return (d.dia+30) - current_day.dia;
    }
    return ((d.ano-1)*365 + (d.mes-1)*365 + d.dia) - ((current_day.ano-1)*365 + (current_day.mes-1)*30 + current_day.dia);
}

bool emptyF(ifstream& file) {return file.peek() == iostream::traits_type::eof();}
