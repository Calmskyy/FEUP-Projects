#pragma once
#include <string>
#include <vector>
#include <list>
#include "ServicoTransporte.h"
#include "Utils.h"
using namespace std;

/**
 * Representacao de uma oficina usada pela empresa para manutencao dos camioes
 */
class Oficina {
private:
    string nome;
    list <string> marcas;
    unsigned disponibilidade;
    Date next_available_date;
public:
    /**
     * @brief Construtor da classe Oficina
     * @param nome Nome da oficina
     * @param marcas Marcas nas quais a oficina se especializa
     * @param disponibilidade Numero de dias ate a oficina estar disponivel novamente
     */
    Oficina(string nome, list<string> marcas, unsigned disponibilidade);

    /**
     * @brief Metodo para obter o nome da oficina
     * @return string com o nome da oficina
     */
    string getNome() const;

    /**
     * @brief Metodo para alterar o nome de uma oficina
     * @param nome string com o novo nome da oficina
     */
    void setNome(const string nome);

    /**
     * @brief Obtem uma lista com as marcas nas quais a oficina se especializa
     * @return Lista com as marcas nas quais a oficina se especializa
     */
    list <string> getMarcas() const ;

    /**
     * @brief Metodo que permite alterar a lista com as marcas nas quais a oficina se especializa
     * @param marcas Nova lista com as strings que representam as marcas nas quais a oficina se especializa
     */
    void setMarcas(list <string > marcas);

    /**
     * @brief Obtem a disponibilidade da empresa
     * @return Unsigned int com o numero de dias ate à empresa estar novamente disponivel
     */
    unsigned int getDisponibilidade() const;
    /**
     * @brief Altera o valor da disponibilidade da oficina
     * @param d Novo valor da disponibilidade da oficina
     */
    void setDisponibilidade(unsigned d);
    /**
     * @brief Obtem a data na qual a oficina se encontrará novamente disponivel
     * @return Objeto da struct Date com a informação acerca da data na qual a oficina se encontra disponivel
     */
    Date getDateAvailable() const;
    /**
     * @brief Altera o valor da data na qual a oficina se encontrará novamente disponível
     * @param d1 Objeto da struct Date com a informação acerca da data na qual a oficina se encontrará disponível
     */
    void setDateAvailable( Date& d1);

    /**
     * @brief Overload do operador == para averiguar a igualdade entre duas oficinas
     * @param o1 oficina a comparar com o objeto instanciado
     * @return true se as oficinas forem iguais, false caso contrário
     */
    bool operator==(const Oficina& o1);

    /**
     * @brief Overload do operador < para comparaçao entre duas oficinas e inserçao dos objetos na priority_queue
     * @param o1 Oficina a ser comparada
     * @return true se a Oficina instanciada for menor que a Oficina o1, false caso contrário
     */
    bool operator<(const Oficina& o1) const;

    /**
     * @brief Overload do operador de extração (<<) de modo a mostrar de modo amigável a informação acerca de uma oficina
     * @param out ostream usada para efetuar a extração
     * @param o Oficina a ser mostrada
     * @return Ostream Mesma stream do parâmetro
     */
    friend ostream& operator << (ostream& out, const Oficina& o);

    /**
     * @brief Método que adiciona um serviço a efetuar pela oficina
     * @param marca Marca do camiao a reparar
     * @param tipoServico string com o tipo de serviço: "normal" ou "específico"
     * @return true se o serviço for agendado com sucesso, false caso contrário
     */
    bool addServico(string marca, string tipoServico);
};
