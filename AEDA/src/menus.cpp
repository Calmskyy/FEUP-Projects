#include <iostream>
#include "menus.h"
#include <iomanip>
using namespace std;

void adicionarClientes(Empresa& e1){
    string nome;
    cout << "Nome:";
    getline(cin, nome);
    nome = removeSpaces(nome);
    int idade = menuValidInput("Idade:" ,18,120);
    int nif = inputNIF("Nif:");

    Cliente n(nome, idade, nif, 0);
    try{
        e1.adicionarCliente(n);
        cout << endl << "Cliente adicionado => " << n.getName() << endl;
    }
    catch(ClienteRepetido c){
        cerr << "Cliente repetido => " << c.getName() << endl;
    }
}

void editarClientes(Empresa& e1){
    int option;
    int idx;
    vector<Cliente> copia = e1.getClientes();
    copia.insert(copia.end(), e1.getInactive().begin(), e1.getInactive().end());
    cout << "[0] Sair\n";
    cout << "--------------------------------------------------" << endl;
    for (size_t i = 1; i <= copia.size(); i++){
        cout << "[" << i << "] " << copia.at(i-1);
        cout << "--------------------------------------------------" << endl;
    }
    idx = menuValidInput("Selecione o cliente que pretende editar:",0, copia.size());
    if (idx == 0) return;
    cout << "[0] Sair\n" << "[1] Nome\n" << "[2] Idade\n" << "[3] Nif\n" << "[4] Eliminar servicos adquiridos\n" << "[5] adicionar servicos adquiridos" << endl << endl;
    option = menuValidInput("Selecione o que pretende editar:", 0, 5);
    cout << "--------------------------------------------------" << endl;
    switch (option) {
        case 0:
            return;
        case 1: {
            string novo_nome;
            cout << "Novo nome:";
            getline(cin, novo_nome);
            novo_nome = removeSpaces(novo_nome);
            copia.at(idx - 1).setName(novo_nome);
            break;
        }
        case 2: {
            int idadeN;
            idadeN = menuValidInput("Nova idade:", 18, 120);
            copia.at(idx - 1).setAge(idadeN);
            break;
        }
        case 3: {
            int Nnif;
            Nnif = inputNIF("Novo nif:");
            copia.at(idx - 1).setNif(Nnif);
            break;
        }
        case 4: {
            cout << "[0] Voltar\n";
            for (size_t i = 1; i <= e1.getClientes().at(idx - 1).getServicos().size(); i++) {
                cout << "--------------------------------------------------" << endl;
                cout << "[" << i << "]" << e1.getClientes().at(idx - 1).getServicos().at(i - 1);
            }
            cout << "--------------------------------------------------" << endl;
            int option2 = menuValidInput("Selecione o servico que pretende eliminar:", 0, GetMaxId(e1.getServicos()));
            if (option2 == 0) return;
            vector<ServicoTransporte> st1 = copia.at(idx - 1).getServicos();
            ServicoTransporte s = st1.at(option2 - 1);
            e1.setDisponivel(s);
            st1.erase(st1.begin() + option2 - 1);
            copia.at(idx - 1).setServicos(st1);
            copia.at(idx - 1).setActive(activeCheck(copia.at(idx - 1)));
            break;
        }
        case 5: {
            cout << "[0] Sair\n";
            for (size_t i = 1; i <= e1.servicosDisponiveis().size(); i++) {
                cout << "--------------------------------------------------" << endl;
                cout << "[" << i << "]" << e1.servicosDisponiveis().at(i - 1);
            }
            cout << "--------------------------------------------------" << endl;
            int option = menuValidInput("Selecione o servico que pretende adquirir para este cliente:", 0, e1.servicosDisponiveis().size());
            if (option == 0) return;
            vector<ServicoTransporte> st1 = copia.at(idx - 1).getServicos();
            st1.push_back(e1.servicosDisponiveis().at(option - 1));
            e1.eliminarServico(e1.servicosDisponiveis().at(option - 1));
            copia.at(idx - 1).setServicos(st1);
            copia.at(idx - 1).setActive(activeCheck(copia.at(idx - 1)));
            break;
        }
        default:
            break;
    }
    e1.arrangeClients(copia);
    return;
}


void eliminarClientes(Empresa& e1) {
    cout << "[0] Sair\n";
    cout << "--------------------------------------------------" << endl;
    vector<Cliente> copia = e1.getClientes();
    copia.insert(copia.end(), e1.getInactive().begin(), e1.getInactive().end());
    for (size_t i = 1; i <= copia.size(); i++) {
        cout << "[" << i << "] " << copia.at(i - 1);
        cout << "--------------------------------------------------" << endl;
    }
    int option = menuValidInput("Selecione o cliente:", 0, copia.size());
    if (option == 0) return;
    cout << copia.at(option-1);
    e1.setClientes(copia);
    e1.eliminarCliente(e1.getClientes().at(option-1));
    e1.arrangeClients(copia);
}

void gerirClientes(Empresa& e1) {
    cout << "= = = = = = = = = GERIR CLIENTES= = = = = = = = ==" << endl;
    int option;
    cout << "[0] => Sair\n";
    cout << "[1] => Adicionar um novo cliente\n";
    cout << "[2] => Editar um cliente existente\n";
    cout << "[3] => Eliminar um cliente\n";
    option = menuValidInput("Opcao:" ,0,4);
    cout << "= = = = = = = = = = = = = = = = = = = = = = = = ==" << endl;
    switch(option){
        case 0: return;
        case 1:
            adicionarClientes(e1);
            e1.updateClientes();
            break;
        case 2:
            editarClientes(e1);
            e1.updateClientes();
            e1.updateServicos();
            break;
        case 3:
            eliminarClientes(e1);
            e1.updateClientes();
            break;
        default: gerirClientes(e1);
    }
}


void adicionarCamioes(Empresa& e1){
    vector<Camiao *> copia;
    cout << "Selecione o tipo de camioes: \n";
    cout << "[0] Sair\n" << "[1] Perigosos\n" << "[2] Congelacao\n" << "[3] Normal\n" << "[4] Animais\n";
    int option = menuValidInput("Opcao:" , 0, 4);
    cout << "--------------------------------------------------" << endl;
    switch(option) {
        case 0:
            return;
        case 1: {
            int cap = menuValidInput("Capacidade:", 0, 200000);
            string marca, nivel;
            cout << "Marca:";
            getline(cin, marca);
            marca = removeSpaces(marca);
            nivel = nivelVerifier();
            nivel = removeSpaces(nivel);
            Perigosos *p = new Perigosos(cap, marca, 0, nivel);
            cout << "Camiao adicionardo:\n" << *p;
            Camiao *ca = p;
            try {
                e1.adicionarCamiao(ca);
            }
            catch (CamiaoRepetido c) {
                cerr << "Este camiao ja existe\n";
            }
            break;
        }
        case 2: {
            int cap = menuValidInput("Capacidade:", 0, 200000);
            string marca;
            cout << "Marca:";
            getline(cin, marca);
            marca = removeSpaces(marca);
            int tempmin = menuValidInput("Temperatura minima:", -1000, 1000);
            Congelacao *c = new Congelacao(cap, marca, 0, tempmin);
            cout << "Camiao adicionardo:\n" << *c;
            Camiao *ca = c;
            try {
                e1.adicionarCamiao(ca);
            }
            catch (CamiaoRepetido c) {
                cerr << "Este camiao ja existe\n";
            }
            break;
        }

        case 3: {
            int cap = menuValidInput("Capacidade:", 0, 200000);
            string marca;
            cout << "Marca:";
            getline(cin, marca);
            marca = removeSpaces(marca);
            Normal *n = new Normal(cap, marca, 0);
            cout << "Camiao adicionardo:\n" << *n;
            Camiao *ca = n;
            try {
                e1.adicionarCamiao(ca);
            }
            catch (CamiaoRepetido c) {
                cerr << "Este camiao ja existe\n";
            }
            break;
        }

        case 4:{
            int cap = menuValidInput("Capacidade:", 0, 200000);
            string marca, nivel;
            cout << "Marca:";
            getline(cin, marca);
            marca = removeSpaces(marca);
            int numAnimais = menuValidInput("Numero de animais:", 0, 10000);
            Animais *na = new Animais(cap, marca, 0, numAnimais);
            cout << "Camiao adicionardo:\n" << *na;
            Camiao *ca = na;
            try {
                e1.adicionarCamiao(ca);
            }
            catch (CamiaoRepetido c) {
                cerr << "Este camiao ja existe\n";
            }
            break;
        }
        default: break;
    }
}


void eliminarCamioes(Empresa& e1) {
    cout << "[0] Sair\n";
    for (size_t i = 1; i <= e1.getCamioes().size(); i++){
        cout << "[" << i << "]\n" << *e1.getCamioes().at(i-1) << endl;
    }
    int option = menuValidInput("Option:", 0, e1.getCamioes().size());
    if (option == 0) return;
    e1.eliminarCamiao(e1.getCamioes().at(option-1));
}

void editarCamioes(Empresa& e1) {
    cout << "[0] Sair\n" << endl;
    for (size_t i = 1; i <= e1.getCamioes().size(); i++) {
        cout << "[" << i << "]\n" << *e1.getCamioes().at(i - 1) << endl;
    }
    int option = menuValidInput("Selecione o camiao a editar:", 0, e1.getCamioes().size());
    if (option == 0) return;
    Camiao* c = e1.getCamioes().at(option - 1);
    Perigosos* np = dynamic_cast<Perigosos*>(c);
    Normal* nn = dynamic_cast<Normal*>(c);
    Congelacao* nc = dynamic_cast<Congelacao*>(c);
    Animais* na = dynamic_cast<Animais*>(c);

    cout << "[0] Voltar\n" << "[1] Capacidade\n" << "[2] Marca\n";

    int limitOption = 3;
    if (np != nullptr) {
        cout << "[3] Nivel\n";
        limitOption = 4;
    }
    else if (nc != nullptr) {
        cout << "[3] Temperatura minima\n";
        limitOption = 4;
    }
    else if (na != nullptr) {
        cout << "[3] Numero de animais\n";
        limitOption = 4;
    }
    else if (nn != nullptr)
        limitOption = 3;

    int option2 = menuValidInput("Opcao:", 0, limitOption);
    switch (option2) {
        case 0:
            editarCamioes(e1);
            break;
        case 1: {
            int capacidade = menuValidInput("Capacidade:", 0, 9999999);
            if (np != nullptr)
                np->setCapacidade(capacidade);
            else if (nn != nullptr)
                nn->setCapacidade(capacidade);
            else if (nc != nullptr)
                nc->setCapacidade(capacidade);
            else if (na != nullptr)
                na->setCapacidade(capacidade);
            break;
        }
        case 2: {
            string marca;
            cout << "Marca:";
            getline(cin, marca);
            if (np != nullptr)
                np->setMarca(marca);
            else if (nn != nullptr)
                nn->setMarca(marca);
            else if (nc != nullptr)
                nc->setMarca(marca);
            else if (na != nullptr)
                na->setMarca(marca);
            break;
        }
        case 3: {
            if (np != nullptr) {
                string nivel = nivelVerifier();
                np->setNivel(nivel);
            }
            else if (nc != nullptr) {
                int tempMin = menuValidInput("Temperatura minima:", -1000, 1000);
                nc->setTempMin(tempMin);
            }
            else if (na != nullptr) {
                int numAnimais = menuValidInput("Numero de animais:", 0, 1000);
                na->setNumAnimais(numAnimais);
            }
            break;
        }
    }
}

void gerirCamioes(Empresa& e1) {
    int option;
    cout << "[0] => Sair\n";
    cout << "[1] => Adicionar um novo camiao\n";
    cout << "[2] => Editar um camiao existente\n";
    cout << "[3] => Eliminar um camiao\n";
    option = menuValidInput("Option:", 0,3);
    cout << "= = = = = = = = = = = = = = = = = = = = = = = = ==" << endl;
    switch(option){
        case 1:
            adicionarCamioes(e1);
            e1.updateCamioes();
            break;
        case 2:
            editarCamioes(e1);
            e1.updateCamioes();
            break;
        case 3:
            eliminarCamioes(e1);
            e1.updateCamioes();
            e1.updateServicos();
            break;
        case 0:
            break;
        default: gerirCamioes(e1);
    }
}

void adicionarServicos(Empresa& e1){
    string camioes_str, origem, destino, horario, data;
    int n_horas;
    vector <Camiao*> aux;
    string tipo_camioes = camioesTipoVerifier(e1.getCamioes(), aux);
    if (aux.size() == 0){
        cout << "Nao existem camioes deste tipo disponiveis\n";
        return;
    }
    if (aux.size() == 0) vector<Camiao*> vect = {}; //vetor de camioes vazio
    else {
        cout << "Camioes para entrega: " << endl;
        cout << "[0] Sair\n[1] Escolha automatica\n[2] Escolha manual" << endl;
        int option = menuValidInput("Opcao:", 0, 2);
        switch(option) {
            case 0: return;
            case 1: {
                int op = menuValidInput("Numero de camioes para a entrega:", 1, aux.size());
                for (size_t i = 0; i < op; i++) {
                    if (i == op - 1) camioes_str += to_string(aux.at(i)->getId());
                    else {
                        camioes_str += to_string(aux.at(i)->getId());
                        camioes_str += " ; ";
                    }
                }
                break;
            }
            case 2: {
                cout << "--------------------------------------------------" << endl;
                for (Camiao *ca: aux) {
                    cout << *ca;
                    cout << "--------------------------------------------------" << endl;
                }
                cout << "Escolha os camioes para efetuar o servico de transporte (identificadores separados por ';'):";
                getline(cin, camioes_str);
                camioes_str = removeSpaces(camioes_str);
                break;
            }
            default: break;
        }
    }
    vector <Camiao*> vect = camioesBuilder(camioes_str, aux, tipo_camioes);
    cout << "Origem:";getline(cin, origem);
    cout << "Destino:";getline(cin, destino);
    horario = inputHorario("Horario:");
    data = menuDateInput("Data(DD/MM/AAAA):");
    n_horas = menuValidInput("Numero de horas estimadas:", 0, 100);
    ServicoTransporte st(origem,destino,tipo_camioes,vect,horario, dateSplitter(data),1, (unsigned) n_horas);
    try{
        e1.adicionarServico(st);
    }
    catch (CamioesIndisponiveis c) {
        cerr << "Um ou mais camioes selecionados encontram-se indisponiveis para este servico de transporte\n";
        return;
    }
    catch (LocalizacaoIndisponivel li){
        cerr << "Localizacao indisponivel: " << li.getNome() << endl;
        return;
    }
    catch (MotoristasIndisponiveis mi){
        cerr << "Motoristas indisponiveis." << endl;
        return;
    }
    catch (CamiaoOcupado co){
        cerr << "O camiao com identificador " << co.getId() << "encontra-se ocupado\n";
    }
    return;
}

void eliminarServicos(Empresa& e1){
    cout << "[0] Sair\n";
    for (size_t i = 1; i <= e1.servicosDisponiveis().size(); i++){
        cout << "[" << i << "] " << e1.servicosDisponiveis().at(i-1) << endl;
    }
    int option = menuValidInput("Selecione o servico que pretende eliminar:", 0, e1.servicosDisponiveis().size());
    if (option == 0)return;
    e1.eliminarServico(e1.servicosDisponiveis().at(option-1));
}

void editarServicos(Empresa& e1){
    vector<Camiao *> aux;
    cout << "[0] Sair\n";
    cout << "--------------------------------------------------" << endl;
    for (size_t i=1; i <= e1.getServicos().size(); i++){
        cout << "[" << i << "] " << e1.getServicos().at(i-1);
        cout << "--------------------------------------------------" << endl;
    }
    int option = menuValidInput("Selecione o servico que pretende editar:", 0, e1.getServicos().size());
    if (option == 0) return;
    ServicoTransporte s = e1.getServicos().at(option-1); //copia do servico selecionado
    cout << "Selecione o atributo que pretende editar\n" << "[0] Voltar\n" ;
    cout <<"[1] Origem\n" << "[2] Destino\n" << "[3] Horario\n";
    int option2 = menuValidInput("Opcao:",0,3);
    vector <string> v;
    for (string s: e1.getLocalizacoes()) v.push_back(s);
    cout << "--------------------------------------------------" << endl;
    switch(option2){
        case 0: return;

        case 1:{
            vector <ServicoTransporte> copia = e1.getServicos();
            bool found = false;
            string origem;
            while (!found) {
                cout << "Origem:";
                getline(cin, origem);
                auto it = find(v.begin(), v.end(), origem);
                if (it == v.end())
                    cout << "Localizacao indisponivel\n";
                else found=true;
            }

            s.setOrigem(origem);
            copia.erase(copia.begin() + option - 1);
            copia.push_back(s);
            e1.setServicos(copia);
            break;
        }

        case 2: {
            vector <ServicoTransporte> copia = e1.getServicos();
            ServicoTransporte s = e1.getServicos().at(option-1); //copia do servico selecionado
            bool found = false;
            string destino;
            while (!found) {
                cout << "Destino:";
                getline(cin, destino);//cin.ignore(1000, '\n');
                auto it = find(v.begin(), v.end(), destino);
                if (it == v.end()) cout << "Localizacao indisponivel\n";
                else found = true;
            }
            ServicoTransporte::globalID--;
            s.setDestino(destino);
            copia.erase(copia.begin() + option - 1);
            copia.push_back(s);
            e1.setServicos(copia);
            return;
        }
        case 3:{
            vector <ServicoTransporte> copia = e1.getServicos();
            string horario;
            horario = inputHorario("Horario (HH:MM):");
            s.setHorario(horario);
            copia.erase(copia.begin() + option - 1);
            copia.push_back(s);
            e1.setServicos(copia);
            break;
        }
        default:break;

    }
    return;
}


void gerirServicos(Empresa& e1){
    cout << "= = = = = = = = = =GERIR SERVICOS= = = = = = = = =" << endl;
    cout << "[0] Sair\n";
    cout << "[1] Adicionar um servico\n";
    cout << "[2] Editar um servico\n";
    cout << "[3] Eliminar um servico\n";// << "Opcao: ";
    int option = menuValidInput("Opcao:",0,3);
    cout << "= = = = = = = = = = = = = = = = = = = = = = = = ==" << endl;
    switch(option){
        case 0:
            return;
        case 1:
            adicionarServicos(e1);
            e1.updateServicos();
            break;
        case 2:
            editarServicos(e1);
            e1.updateServicos();
            break;
        case 3:
            eliminarServicos(e1);
            e1.updateServicos();
            break;
        default: gerirServicos(e1);
    }
}

void adicionarMotoristas(Empresa& e1) {
    string nome, idade_str, salario_str, horario_str, horario2_str, categorias_str;
    cout << "Nome:";;
    getline(cin, nome);
    nome = removeSpaces(nome);
    int idade = menuValidInput("Idade:", 24, 65);
    int salario = menuValidInput("Salario:", 0, 1000000000);
    horario_str = inputHorario("Horario Inicial (HH:MM):");
    horario2_str = inputHorario("Horario Final (HH:MM):");
    horario_str = horario_str + " -> " + horario2_str;
    //cin.ignore(10000, '\n');
    cout << "Categorias (separadadas por ' ; '):";  getline(cin, categorias_str);
    Motorista mot(nome, idade, salario, toPair(horario_str), categoryVector(categorias_str),0);
    try {
        e1.adicionarMotorista(mot);
        cout << endl << "Motorista adicionado => " << mot.getName() << endl;
    }
    catch (MotoristaRepetido c) {
        cerr << "Motorista repetido =>" << mot.getName() << endl;
    }
}

void editarMotoristas(Empresa& e1) {
    cout << "[0] Sair\n";
    cout << "--------------------------------------------------" << endl;
    BST <Motorista> copia = e1.getMotoristas();
    BSTItrIn <Motorista> it(copia);
    while (!it.isAtEnd()) {
        cout << it.retrieve();
        cout << "--------------------------------------------------" << endl;
        it.advance();
    }
    int idx = menuValidInput("Selecione o motorista que pretende editar:", 0, (int) Motorista::getLastId()+1);
    if (idx == 0) return;
    cout << "Selecione o que pretende editar\n";
    cout << "[0] Voltar\n" << "[1] Nome\n" << "[2] Idade\n" << "[3] Salario\n" << "[4] Horario\n" << "[5] Categorias para as quais o motorista e qualificado\n";
    int option = menuValidInput("Opcao:", 0, 5);
    cout << "--------------------------------------------------" << endl;
    switch (option) {
        case 0:
            editarMotoristas(e1);
            break;
        case 1: {
            string name;
            cout << "Nome:";
            getline(cin, name);
            name = removeSpaces(name);
            Motorista *s = findMotoristaIndex(copia,idx);
            copia.remove(*s);
            s->setName(name);
            copia.insert(*s);
            e1.setMotoristas(copia);
            break;
        }
        case 2: {
            int age;
            age = menuValidInput("Idade:", 24, 65);
            Motorista* m = findMotoristaIndex(copia,idx);
            copia.remove(*m);
            m->setAge(age);
            copia.insert(*m);
            e1.setMotoristas(copia);
            break;
        }
        case 3: {
            int salary;
            salary = menuValidInput("Novo salario:", 0, 1000000000);
            Motorista* m = findMotoristaIndex(copia,idx);
            copia.remove(*m);
            m->setSalario(salary);
            copia.insert(*m);
            e1.setMotoristas(copia);
            break;
        }
        case 4: {
            cout << "[1] Mudar horario de entrada\n" << "[2] Mudar horario de saida\n" << "[3] Mudar horario total\n";
            int op = menuValidInput("Opcao:", 1, 3);
            switch (op) {
                case 1: {
                    string inicio;
                    inicio = inputHorario("Horario Inicial (HH:MM):");
                    //BST<Motorista> copia = e1.getMotoristas();
                    Motorista* m = findMotoristaIndex(copia,idx);
                    copia.remove(*m);
                    m->setHorario(inicio, m->getHorario().second);
                    copia.insert(*m);
                    e1.setMotoristas(copia);
                    break;
                }
                case 2: {
                    string fim;
                    fim = inputHorario("Horario Final (HH:MM):");
                    //BST<Motorista> copia = e1.getMotoristas();
                    Motorista* m = findMotoristaIndex(copia,idx);
                    copia.remove(*m);
                    m->setHorario(m->getHorario().first, fim);
                    copia.insert(*m);
                    e1.setMotoristas(copia);
                    break;
                }
                case 3: {
                    string time, time1;
                    time = inputHorario("Horario Inicial (HH:MM):");
                    time1 = inputHorario("Horario Final (HH:MM):");
                    time = removeSpaces(time);
                    time1 = removeSpaces(time1);
                    time += " -> ";
                    time += time1;
                    //BST<Motorista> copia = e1.getMotoristas();
                    Motorista* m = findMotoristaIndex(copia,idx);
                    copia.remove(*m);
                    m->setHorario(toPair(time));
                    copia.insert(*m);
                    e1.setMotoristas(copia);
                    break;
                }
            }
            break;
        }
        case 5: {
            string category;
            cout << "Categorias (separadadas por ' ; ') "; getline(cin, category);
            //BST<Motorista> copia = e1.getMotoristas();
            Motorista* m = findMotoristaIndex(copia,idx);
            copia.remove(*m);
            m->setCategorias(categoryVector(category));
            copia.insert(*m);
            e1.setMotoristas(copia);
            break;
        }
        default: break;
    }
}

void eliminarMotoristas(Empresa& e1) {
    BST<Motorista> copia = e1.getMotoristas();
    BSTItrIn <Motorista> it(copia);
    cout << "[0] Sair\n";
    cout << "--------------------------------------------------" << endl;
    while (!it.isAtEnd()) {
        cout << "[" << it.retrieve().getId() << "] -> ";
        cout << findMotoristaIndex(copia, it.retrieve().getId());
        cout << "--------------------------------------------------" << endl;
    }
    int option = menuValidInput("Selecione o motorista:", 0, Motorista::getLastId()+1);
    if (option == 0) return;
    e1.eliminarMotorista(*findMotoristaIndex(copia, option));
}


void gerirMotoristas(Empresa& e1) {
    cout << "= = = = = = = = =GERIR MOTORISTAS= = = = = = = = =" << endl;
    int option;
    cout << "[0] => Sair\n";
    cout << "[1] => Adicionar um novo motorista\n";
    cout << "[2] => Editar um motorista existente\n";
    cout << "[3] => Eliminar um motorista\n";
    option = menuValidInput("Opcao:", 0, 3);
    cout << "= = = = = = = = = = = = = = = = = = = = = = = = ==" << endl;
    switch (option) {
        case 0: return;
        case 1:
            adicionarMotoristas(e1);
            e1.updateMotoristas();
            break;
        case 2:
            editarMotoristas(e1);
            e1.updateMotoristas();
            break;
        case 3:
            eliminarMotoristas(e1);
            e1.updateMotoristas();
            e1.updateServicos();
            break;
        default: gerirMotoristas(e1);
    }
}

void mostrarCamioesTipo(Empresa& e1) {
    vector <Camiao *> aux;
    string tipo = camioesTipoVerifier(e1.getCamioes(), aux);
    unsigned i = 0;
    for (Camiao* ca: aux){
        Perigosos *np = dynamic_cast<Perigosos *>(ca);
        Normal *nn = dynamic_cast<Normal *>(ca);
        Animais *na = dynamic_cast<Animais *>(ca);
        Congelacao *nc = dynamic_cast<Congelacao *>(ca);
        if (np != nullptr) {
            cout << *np;
            cout << "Capacidade: " << np->getCapacidade() << endl;
            cout << "Kilometros percorridos: " << np->getKmPercorridos() << endl;
            cout << "Nivel de perigo: " << np->getNivel() << endl;
        } else if (nn != nullptr) {
            cout << *nn;
            cout << "Capacidade: " << nn->getCapacidade() << endl;
            cout << "Kilometros percorridos: " << nn->getKmPercorridos() << endl;
        } else if (na != nullptr) {
            cout << *na;
            cout << "Capacidade: " << na->getCapacidade() << endl;
            cout << "Kilometros percorridos: " << na->getKmPercorridos() << endl;
            cout << "Numero de animais transportados: " << na->getNumAnimais() << endl;
        } else if (nc != nullptr) {
            cout << *nc;
            cout << "Capacidade: " << nc->getCapacidade() << endl;
            cout << "Kilometros percorridos: " << nc->getKmPercorridos() << endl;
            cout << "Temperatura minima de congelacao: " << nc->getTempMin() << endl;
        }
        if (i < aux.size() - 1) cout << "--------------------------------------------------" << endl;
        i++;
    }
}

void mostrarInformacaoCamioes(Empresa& e1){
    cout << "= = = = = = = =ESTATISTICAS CAMIOES= = = = = = = =" << endl;
    cout << "[0] Sair\n" << "[1] Escolha entre todos os camioes\n" << "[2] Pesquisar camioes por tipo\n";
    int option = menuValidInput("Opcao:",0,2);
    cout << "= = = = = = = = = = = = = = = = = = = = = = = = ==" << endl;
    switch (option) {
        case 0: return;
        case 1:{
            for (size_t i = 1; i < e1.getCamioes().size() + 1; i++) {
                cout << "[" << i << "] -> ";
                cout << *e1.getCamioes().at(i - 1);
                cout << "--------------------------------------------------" << endl;
            }
            int option = menuValidInput("Selecione o camiao para ver em detalhe:", 1, e1.getCamioes().size());
            Camiao *ca = e1.getCamioes().at(option - 1);
            Perigosos *np = dynamic_cast<Perigosos *>(ca);
            Normal *nn = dynamic_cast<Normal *>(ca);
            Animais *na = dynamic_cast<Animais *>(ca);
            Congelacao *nc = dynamic_cast<Congelacao *>(ca);
            cout << endl;
            if (np != nullptr) {
                cout << "Camiao de transporte de mercadorias perigosas\n";
                cout << *np;
                cout << "Capacidade: " << np->getCapacidade() << endl;
                cout << "Kilometros percorridos: " << np->getKmPercorridos() << endl;
                cout << "Nivel de perigo: " << np->getNivel() << endl;
            } else if (nn != nullptr) {
                cout << "Camiao de transporte de mercadorias normais\n";
                cout << *nn;
                cout << "Capacidade: " << nn->getCapacidade() << endl;
                cout << "Kilometros percorridos: " << nn->getKmPercorridos() << endl;
            } else if (na != nullptr) {
                cout << "Camiao de transporte de animais\n";
                cout << *na;
                cout << "Capacidade: " << na->getCapacidade() << endl;
                cout << "Kilometros percorridos: " << na->getKmPercorridos() << endl;
                cout << "Numero de animais transportados: " << na->getNumAnimais() << endl;
            } else if (nc != nullptr) {
                cout << "Camiao de transporte de mercadorias congeladas\n";
                cout << *nc;
                cout << "Capacidade: " << nc->getCapacidade() << endl;
                cout << "Kilometros percorridos: " << nc->getKmPercorridos() << endl;
                cout << "Temperatura minima de congelacao: " << nc->getTempMin() << endl;
            }
            break;
        }
        case 2:{
            mostrarCamioesTipo(e1);
            break;
        }
        default: break;
    }
}

void mostrarInformacaoClientes(Empresa& e1) {
    cout << "= = = = = = = ESTATISTICAS  CLIENTES = = = = = = =" << endl;
    cout << "[0] Sair\n";
    cout << "--------------------------------------------------" << endl;
    vector<Cliente> copia = e1.getClientes();
    copia.insert(copia.end(), e1.getInactive().begin(), e1.getInactive().end());
    for (size_t i = 1; i <= copia.size(); i++){
        cout << "[" << i << "]\n" << copia.at(i-1);
        cout << "--------------------------------------------------" << endl;
    }
    int option = menuValidInput("Selecione o cliente para ver informacao detalhada:", 0, copia.size());
    cout << endl;
    if (option == 0) return;
    Cliente esc = copia.at(option - 1);
    cout << esc;
    cout << "Servicos de transporte adquiridos:";
    if (esc.getServicos().size() == 0) cout << " Ainda nao realizou nenhuma encomenda." << endl;
    else {
        cout << endl;
        unsigned aux = 1;
        for (ServicoTransporte st: esc.getServicos()) {
            cout << "[" << aux << "] " << st;
            aux++;
        }
    }
    e1.arrangeClients(copia);
}

void mostrarInformacaoServicos(Empresa& e1){
    cout << "= = = = = = = ESTATISTICAS  SERVICOS = = = = = = =" << endl;
    cout << "[0] Sair\n";
    cout << "--------------------------------------------------" << endl;
    for (size_t i = 1; i <= e1.getServicos().size(); i++){
        cout << e1.getServicos().at(i-1);
        cout << "--------------------------------------------------" << endl;
    }
    int option = menuValidInput("Selecione o servico para ver em detalhe:", 0, e1.getServicos().size());
    cout << endl;
    if (option == 0) return;
    ServicoTransporte st = e1.getServicos().at(option-1);
    cout << st;
    cout << "Preco: " << st.getPreco(e1.getDistancias()) << endl;
}

void mostrarInformacaoMotoristas(Empresa& e1) {
    cout << "= = = = = = =ESTATISTICAS MOTORISTAS= = = = = = =" << endl;
    cout << "[0] Sair\n";
    cout << "[1] Mostrar motoristas em ordem\n" << "[2] Mostrar motoristas por nivel\n";
    cout << "[3] Mostrar motoristas em pre-ordem\n" << "[4] Mostrar motoristas em pos-ordem\n";
    cout << "--------------------------------------------------" << endl;
    int option = menuValidInput("Selecione a opcao desejada:",0,4);
    BST<Motorista> copia = e1.getMotoristas();
    if (option == 0) return;
    else if (option == 1) {
        BSTItrIn<Motorista> it(copia);
        while (!it.isAtEnd()){
            cout << "[" << it.retrieve().getId() << "] Nome:" << findMotoristaIndex(copia, it.retrieve().getId())->getName() << endl << "    Idade:" << findMotoristaIndex(copia, it.retrieve().getId())->getAge() << endl;
            cout << "--------------------------------------------------" << endl;
            it.advance();
        }
    }
    else if (option == 2) {
        BSTItrLevel<Motorista> it(copia);
        while (!it.isAtEnd()){
            cout << "[" << it.retrieve().getId() << "] Nome:" << findMotoristaIndex(copia, it.retrieve().getId())->getName() << endl << "    Idade:" << findMotoristaIndex(copia, it.retrieve().getId())->getAge() << endl;
            cout << "--------------------------------------------------" << endl;
            it.advance();
        }
    }
    else if (option == 3) {
        BSTItrPre<Motorista> it(copia);
        while (!it.isAtEnd()){
            cout << "[" << it.retrieve().getId() << "] Nome:" << findMotoristaIndex(copia, it.retrieve().getId())->getName() << endl << "    Idade:" << findMotoristaIndex(copia, it.retrieve().getId())->getAge() << endl;
            cout << "--------------------------------------------------" << endl;
            it.advance();
        }
    }
    else if (option == 4) {
        BSTItrPost<Motorista> it(copia);
        while (!it.isAtEnd()){
            cout << "[" << it.retrieve().getId() << "] Nome:" << findMotoristaIndex(copia, it.retrieve().getId())->getName() << endl << "    Idade:" << findMotoristaIndex(copia, it.retrieve().getId())->getAge() << endl;
            cout << "--------------------------------------------------" << endl;
            it.advance();
        }
    }
    int option2 = menuValidInput("Selecione o motorista para ver em detalhe:", 0, e1.getServicos().size());
    cout << "= = = = = = = = = = = = = = = = = = = = = = = = ==" << endl;
    if (option2 == 0) return;
    Motorista *mot = findMotoristaIndex(e1.getMotoristas(), option2);
    cout << *mot;
}

void mostrarInformacaoEmpresa(Empresa& e1){
    cout << "Numero de motoristas: " << Motorista::getLastId() << endl;
    cout << "Numero de clientes ativos: " << e1.getClientes().size() << endl;
    cout << "Numero de servicos de transporte disponiveis: " << e1.getServicos().size() << endl;
    cout << "Lucro mensal estimado: " << e1.calcularLucroMensal() << endl;
}

void mostrarInformacaoOficinas(Empresa& e1){
    priority_queue<Oficina> aux = e1.getOficinas();
    while (!aux.empty()){
        Oficina atual = aux.top();
        cout << atual;
        aux.pop();
    }
}

void Estatisticas(Empresa& e1){
    cout << "= = = = = = = = = =ESTATISTICAS= = = = = = = = = =" << endl;
    cout << "[0] Sair\n" << "[1] Mostrar informacao dos clientes\n" << "[2] Mostrar informacao dos camioes\n" << "[3] Mostrar informacao dos servicos disponiveis\n";
    cout << "[4] Mostrar informacao dos motoristas\n" << "[5] Mostrar informacao relativa as oficinas\n" << "[6] Mostrar informacao mensal da empresa\n";
    int option = menuValidInput("Opcao:", 0, 6);
    cout << "= = = = = = = = = = = = = = = = = = = = = = = = ==" << endl;
    switch(option){
        case 0: return;
        case 1:
            mostrarInformacaoClientes(e1);
            break;
        case 2:
            mostrarInformacaoCamioes(e1);
            break;
        case 3:
            mostrarInformacaoServicos(e1);
            break;
        case 4:
            mostrarInformacaoMotoristas(e1);
            break;
        case 5:
            mostrarInformacaoOficinas(e1);
            break;
        case 6:
            mostrarInformacaoEmpresa(e1);
            break;
    }
    //return;
}

void gerirServicosOficinas(Empresa& e1){
    cout << "= = = = = = = = = = = = = = = = = = = = = = = = ==" << endl;
    cout << "[0] Sair\n";
    cout << "--------------------------------------------------" << endl;
    for (Camiao* c: e1.getCamioes()){
        cout << *c;
        cout << "--------------------------------------------------" << endl;
    }
    int id_sel = menuValidInput("Selecione o camiao que pretende para o servico (0 para sair):",0, e1.getCamioes().size());
    if (id_sel == 0) return;
    Camiao* ca = findCamioesID(e1.getCamioes(), id_sel);
    cout << "[0] Sair\n" ;
    cout << "[1] Servico normal\n";
    cout << "[2] Serviço especifico\n";
    int option = menuValidInput("Escolah o tipo de servico que pretende:", 0, 2);
    switch(option){
        case 0: return;
        case 1: {
            priority_queue <Oficina> aux = e1.getOficinas();
            Oficina selecionada = aux.top();
            aux.pop();
            cout << "[0] Sair\n" << "[1] Mudanca de oleo\n" << "[2] Revisao\n"<< "[3] Limpeza\n" << "[4] Manutencao geral\n";
            int servico = menuValidInput("Selecione o servico pretendido: ", 0, 4);
            if (servico == 0) return;
            else{
                selecionada.addServico(ca->getMarca(), "normal");
                aux.push(selecionada);
                e1.setOficinas(aux);
                e1.updateOficinas();
                vector <ServicoTransporte> copia_servicos = e1.getServicos();
                for (auto it = copia_servicos.begin(); it != copia_servicos.end(); it++){
                    vector <Camiao*> camioes = (*it).getCamioes();
                    auto itfind = find(camioes.begin(), camioes.end(), ca);
                    if (itfind != camioes.end() && selecionada.getDateAvailable() == it->getDate()) it->eliminaCamiaoServico(ca);
                }
                e1.setServicos(copia_servicos);
                e1.updateServicos();
            }
            }
            break;

        case 2: {
            cout << "[0] Sair\n" << "[1] Substituicao de componentes\n" << "[2] Troca de pneus\n" << "[3] Manutencao do motor\n" << "[4] Manutencao do sistema eletrico\n";
            int option2 = menuValidInput("Selecione o servico que pretendde:", 0,4);
            if (option2 == 0) return;
            else{
                if (e1.adicionaServicoEspecifico(ca->getMarca())) cout << "Servico agendado com sucesso\n";
                else cout << "Nenhuma oficina encontrada para o camiao selecionado\n";
                e1.updateOficinas();
                /*vector <ServicoTransporte> copia_servicos = e1.getServicos();
                for (auto it = copia_servicos.begin(); it != copia_servicos.end(); it++){
                    vector <Camiao*> camioes = (*it).getCamioes();
                    auto itfind = find(camioes.begin(), camioes.end(), *ca);
                    if (itfind != camioes.end() && selec) it->eliminaCamiaoServico(ca);
                }
                e1.setServicos(copia_servicos);*/
            }
            break;
        }
    }
}


unsigned mainMenu(Empresa& e1) {
    e1.updateOficinas();
    cout << endl;
    cout << "====== BEM-VINDO A EMPRESA " << e1.getName() << "! ======" << endl;
    cout << "|| ================== MAIN MENU ==================" << endl;
    cout << "|| (0) Sair" << endl;
    cout << "|| (1) Gerir clientes" << endl;
    cout << "|| (2) Gerir camioes" << endl;
    cout << "|| (3) Gerir servicos de transporte" << endl;
    cout << "|| (4) Gerir motoristas" << endl;
    cout << "|| (5) Gerir oficinas" << endl;
    cout << "|| (6) Mostrar estatisticas da empresa" << endl;
    int option = menuValidInput("Opcao:", 0,6);
    switch(option){
        case 0:
            return 1; // acabar programa
        case 1:
            gerirClientes(e1);
            cout << "= = = = = = = = = = = = = = = = = = = = = = = = ==" << endl;
            mainMenu(e1);
            break;
        case 2:
            gerirCamioes(e1);
            cout << "= = = = = = = = = = = = = = = = = = = = = = = = ==" << endl;
            mainMenu(e1);
            break;
        case 3:
            gerirServicos(e1);
            cout << "= = = = = = = = = = = = = = = = = = = = = = = = ==" << endl;
            mainMenu(e1);
            break;
        case 4:
            gerirMotoristas(e1);
            cout << "= = = = = = = = = = = = = = = = = = = = = = = = ==" << endl;
            mainMenu(e1);
            break;
        case 5:
            gerirServicosOficinas(e1);
            mainMenu(e1);
            break;
        case 6:
            Estatisticas(e1);
            cout << "= = = = = = = = = = = = = = = = = = = = = = = = = =" << endl;
            mainMenu(e1);
            break;
        default: return 0;
    }
    return 0;
}
