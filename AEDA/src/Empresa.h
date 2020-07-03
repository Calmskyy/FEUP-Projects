#pragma once

#include "ServicoTransporte.h"
#include "camiao.h"
#include "Person.h"
#include "Utils.h"
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <unordered_set>
#include <algorithm>
#include "BST.h"
#include "Oficina.h"
#include <cmath>
using namespace std;

/**
 * Struct usada para a hash table dos clientes inativos
 */

struct inactiveClientHash {
    int operator() (const Cliente& c1) const {
        int table_size = 97;
        return (c1.getNif()*(int)pow(2,8)) % table_size;
    }

    bool operator() (const Cliente& c1, const Cliente& c2) const {
        return c1.getNif() == c2.getNif();
    }
};

typedef unordered_set<Cliente, inactiveClientHash, inactiveClientHash> HashTabInactiveClient;

/**
 *  Representacao da empresa, funciona como uma base de dados para guardar todos os outros elementos relevantes
 */
class Empresa {
    string nome;
    string filename;
    vector<Cliente> clientes;
    HashTabInactiveClient inactiveClients;
    BST<Motorista> motoristas;
    vector<Camiao *> camioes;
    string clientes_ficheiro;
    string motoristas_ficheiro;
    string camioes_ficheiro;
    string distancias_ficheiro;
    string servicos_ficheiro;
    string oficinas_ficheiro;
    vector<ServicoTransporte> servicos;
    int numCamioes;
    map<pair<string, string>, double> distancias; // Distancias entre as cidades onde opera a empresa
    std::set<string> localizacoes; // Localizacoes onde a empresa opera
    priority_queue <Oficina> oficinas;
public:
    /**
    * @brief Construtor da base de dados da empresa
    *
    * @param filename Ficheiro de ponto de partida para ler a informacao da empresa
    * @return Empresa Base de dados criada
    */
    Empresa(string filename);

    /**
    * @brief Retorna as localizacoes onde a empresa opera
    *
    * @return set<string> Localizacoes onde a empresa opera
    */
    std::set<string> getLocalizacoes() const;

    /**
    * @brief Retorna o nome da empresa
    *
    * @return string Nome da empresa
    */
    string getName() const;

    /**
    * @brief Retorna os camioes registados na empresa
    *
    * @return vector<Camiao*> Camioes da empresa
    */
    vector<Camiao *> getCamioes() const;

    /**
    * @brief Retorna os clientes registados na empresa
    *
    * @return vector<Cliente> Clientes da empresa
    */
    vector<Cliente> getClientes() const;

    /**
    * @brief Retorna os motoristas registados na empresa
    *
    * @return BST<Motorista> Motoristas da empresa
    */

    HashTabInactiveClient getInactive() const;

    void arrangeClients(vector<Cliente> cli);

    BST<Motorista> getMotoristas() const;

    /**
    * @brief Retorna as rotas registadas na empresa, cada rota contendo os dois locais e a distancia entre estes
    *
    * @return map <pair<string,string>,double> Rotas entre locais da empresa
    */
    map<pair<string, string>, double> getDistancias() const;

    /**
    * @brief retorna a fila de prioridade com as oficinas utilizadas pela empresa
    * @return priority queue com as oficinas
    */
    priority_queue<Oficina> getOficinas() const;

    /**
    * @brief Retorna os servicos registados na empresa
    *
    * @return vector<ServicoTransporte> Servicos da empresa
    */
    vector<ServicoTransporte> getServicos() const;

    /**
    * @brief Muda o registo de clientes na empresa
    *
    * @param clientes Novo valor a ser usado
    */
    void setClientes(vector<Cliente> clientes);

    /**
    * @brief Muda o registo de motoristas na empresa
    *
    * @param motoristas Novo valor a ser usado
    */
    void setMotoristas(BST<Motorista> motoristas);

    /**
    * @brief Muda o registo de camioes na empresa
    *
    * @param camioes Novo valor a ser usado
    */
    void setCamioes(vector<Camiao *> camioes);

    /**
    * @brief Muda o registo de servicos na empresa
    *
    * @param st Novo valor a ser usado
    */
    void setServicos(vector<ServicoTransporte> st);

    /**
    * @brief Retorna os camioes de uma determinada categoria apenas
    *
    * @param camioes Camioes a processar
    * @param categoria Categoria especifica de camioes a retornar
    * @return vector<Camiao*> Camioes de categoria especifica
    */
    vector<Camiao *> getCamioesTipo(vector<Camiao *> camioes, string categoria);

    /**
    * @brief Le informacao de clientes no respetivo ficheiro e guarda a informacao na base de dados
    *
    */
    void readClientes();

    /**
    * @brief Le informacao de motoristas no respetivo ficheiro e guarda a informacao na base de dados
    *
    */
    void readMotoristas();

    /**
    * @brief Le informacao de camioes no respetivo ficheiro e guarda a informacao na base de dados
    *
    */
    void readCamioes();

    /**
    * @brief Le informacao de rotas no respetivo ficheiro e guarda a informacao na base de dados
    *
    */
    void readDistancias();

    /**
    * @brief Le informacao de servicos no respetivo ficheiro e guarda a informacao na base de dados
    *
    */
    void readServicos();

    /**
    * @brief Escreve no respetivo ficheiro a informacao atualizada sobre os clientes
    *
    */
    void updateClientes();

    /**
    * @brief Escreve no respetivo ficheiro a informacao atualizada sobre os camioes
    *
    */
    void updateCamioes();

    /**
    * @brief Escreve no respetivo ficheiro a informacao atualizada sobre os motoristas
    *
    */
    void updateMotoristas();

    /**
    * @brief Escreve no respetivo ficheiro a informacao atualizada sobre os servicos
    *
    */
    void updateServicos();

    /**
    * @brief Escreve no respetivo ficheiro a informacao atualizada sobre os servicos apos remocao de um camiao
    *
    */
    void atualizarServicosCamiao();

    /**
    * @brief Escreve no respetivo ficheiro a informacao atualizada sobre os servicos apos remocao de um motorista
    *
    */
    void atualizarServicosMotorista();

    /**
    * @brief Ordena os camiaos pelos km totais percorridos, em ordem ascendente
    *
    */
    vector <Camiao *> sortCamioes();

    /**
    * @brief Adiciona um novo cliente a base de dados
    *
    * @param novoCliente Cliente a adicionar
    */
    void adicionarCliente(Cliente novoCliente);

    /**
    * @brief Remove um cliente existente na base de dados
    *
    * @param cli Cliente a remover
    */
    void eliminarCliente(Cliente cli);

    /**
    * @brief Adiciona um novo camiao a base de dados
    *
    * @param novoCamiao Camiao a adicionar
    */
    void adicionarCamiao(Camiao *novoCamiao);

    /**
    * @brief Remove um camiao existente na base de dados
    *
    * @param c Camiao a remover
    */
    void eliminarCamiao(Camiao *c);

    /**
    * @brief Adiciona um novo motorista a base de dados
    *
    * @param mot Motorista a adicionar
    */
    void adicionarMotorista(Motorista mot);

    /**
    * @brief Remove um motorista existente na base de dados
    *
    * @param mot Motorista a remover
    */
    void eliminarMotorista(Motorista mot);

    /**
    * @brief Adiciona um novo servico a base de dados
    *
    * @param st Servico a adicionar
    */
    void adicionarServico(ServicoTransporte st);

    /**
    * @brief Remove um servico existente na base de dados
    *
    * @param st Servico a remover
    */
    void eliminarServico(ServicoTransporte st);

    /**
    * @brief Calcula o lucro da empresa, com a soma do preco dos servicos adquiridos subtraidos ao salario dos motoristas
    *
    * @return double Lucro da empresa
    */
    double calcularLucroMensal();

	/**
    * @brief Retorna os servicos que se encontram disponiveis
    *
    * @return vector<ServicoTransporte> Servicos disponiveis da empresa
    */
    vector <ServicoTransporte> servicosDisponiveis();

	/**
    * @brief Verifica se o camiao indicado esta disponivel para realizar o servico pretendido
    *
	* @param ca Camiao a verificar
	* @param st Servico que se pretende realizar
    * @return bool True se o camiao esta disponivel, false caso contrario
    */
    bool isAvailable(Camiao* ca, ServicoTransporte st);

	/**
    * @brief Verifica se o servico pretendido deve-se tornar disponivel, e se sim, torna o servico disponivel
    *
    * @param st Servico a verificar
    */
    void setDisponivel(ServicoTransporte st);

    /**
    * @brief Atualiza os clientes cujo ultimo serviço adquirido ocorreu ha mais de 1 ano
    */
    //void atualizaClientesInativos();

    /**
    * Le informacao relativa as oficinas utilizadas pela empresa
    */
    void readOficinas();

    /**
    * @brief atualiza no ficheiro das oficinas a informaçao acerca das mesmas
    */
    void updateOficinas();


    void subscreveServicoOficina(string tipoServico, Oficina& o1);

    /**
     * @brief Permite alterar a fila de prioridade com as oficinas da empresa
     * @param oficinas Nova priority_queue das oficinas
     */

    void setOficinas(priority_queue <Oficina> oficinas);

    /**
     * @brief Método que permite subscrever a uma oficina um serviço específico a um camião da marca passada no parâmetro
     * @param marca Marca do camião ao qual se destina o serviço
     * @return true se o serviço for agendado com sucesso, false caso contrário
     */

    bool adicionaServicoEspecifico(string marca);
};
