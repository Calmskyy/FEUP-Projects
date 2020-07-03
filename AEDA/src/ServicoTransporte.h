#pragma once

#include "camiao.h"
#include <vector>
#include <string>
#include <iostream>
#include <map>

/**
 *  Representacao de uma data (dia/mes/ano)
 */
struct Date{
    int dia,mes,ano;
	/**
	* @brief Overload do operador == para averiguar a igualdade de 2 datas
	*
	* @param d1 Data a ser comparada
	* @return bool True se as datas sao iguais, false se nao sao
	*/
    bool operator ==(const Date& d1);	
	/**
	* @brief Overload do operador < para averiguar o tempo de 2 datas
	*
	* @param d1 Data a ser comparada
	* @return bool True se a primeira data e menor que a segunda, caso contrario false
	*/
    bool operator <(const Date& d1);
    /**
     * @brief Overload do operador + para efetuar a soma entre duas datas
     * @param d1 data a ser somada
     * @return Date com o resultado da soma entre ambas as datas
     */
    Date operator +(const Date& d1);
    /**
     * @brief Método que adiciona a uma data un número d de dias
     * @param d Número de dias a ser somado
     * @return Date com o resultado da soma pretendida
     */
    Date addDays(unsigned& d);
};

/**
 *  Excecao a ser lancada quando e indicado uma localizacao nao registada na rede de transportes
 */
class LocalizacaoIndisponivel{
    string nome;
public:
	/**
	* @brief Construtor da excecao
	*
	* @param nome Localizacao indisponivel indicada
	* @return LocalizacaoIndisponivel Excecao criada
	*/
    LocalizacaoIndisponivel(string nome);
	/**
	* @brief Retorna a localizacao indisponivel indicada
	*
	* @return string Localizacao indisponivel indicada
	*/
    string getNome() const;
};

/**
 *  Excecao a ser lancada quando nao ha camioes disponiveis para realizar o servico
 */
class CamioesIndisponiveis{
public:
	/**
	* @brief Construtor da excecao
	*
	* @return CamioesIndisponiveis Excecao criada
	*/
    CamioesIndisponiveis();
};

/**
 *  Excecao a ser lancada quando o servico indicado nao existe na empresa
 */
class ServicoInexistente{
    string origem, destino;
public:	
	/**
	* @brief Construtor da excecao
	*
	* @param origem Local de partida indicado
	* @param destino Local de chegada indicado
	* @return ServicoInexistente Excecao criada
	*/
    ServicoInexistente(string origem, string destino);
	/**
	* @brief Retorna o local de origem do servico indicado
	*
	* @return string Local de origem do servico indicado
	*/
    string getOrigem() const;	
	/**
	* @brief Retorna o local de chegada do servico indicado
	*
	* @return string Local de chegada do servico indicado
	*/
    string getDestino() const;
};

/**
 *  Excecao a ser lancada quando nao ha motoristas disponiveis para o servico indicado
 */
class MotoristasIndisponiveis{
    string origem, destino;
public:	
	/**
	* @brief Construtor da excecao
	*
	* @param origem Local de partida do servico
	* @param destino Local de chegada do servico
	* @return MotoristasIndisponiveis Excecao criada
	*/
    MotoristasIndisponiveis(string origem, string destino);	
	/**
	* @brief Retorna o local de origem do servico
	*
	* @return string Local de origem do servico
	*/
    string getOrigem() const;	
	/**
	* @brief Retorna o local de chegada do servico
	*
	* @return string Local de chegada do servico
	*/
    string getDestino() const;
};

/**
 *  Representacao de um servico da empresa
 */
class ServicoTransporte{
private:
    int id;
    string tipo_camioes; // Os camioes de um serviço possuem um tipo unico
    vector <Camiao *> camioes;
    string origem, destino;
    string horario;
    Date data;
    unsigned servicoDisponivel; // 1 se o servico se encontra disponivel, 0 caso contrario
    unsigned n_horas;
public:	
	/**
	* @brief Retorna o identificador do servico
	*
	* @return int Identificador do servico
	*/
    int getId() const;
	/**
	* @brief Retorna o Local de origem do servico
	*
	* @return string Local de origem do servico
	*/
    string getOrigem() const;	
	/**
	* @brief Retorna o local de chegada do servico
	*
	* @return string Local de chegada do servico
	*/
    string getDestino() const;
	/**
	* @brief Retorna o tipo de servico
	*
	* @return string Tipo de servico
	*/
    string getTipo() const;
	/**
	* @brief Muda os camioes responsaveis pelo servico
	*
	* @param camioes Novo valor a ser usado
	*/
    void setCamioes(vector<Camiao *> camioes);	
	/**
	* @brief Muda a disponibilidade do servico
	*
	* @param b Novo valor a ser usado
	*/
    void setDisponibilidade(unsigned b);
	/**
	* @brief Retorna os camioes responsaveis pelo servico
	*
	* @return vector<Camiao*> Camioes responsaveis pelo servico
	*/
    vector <Camiao *> getCamioes() const;	
	/**
	* @brief Construtor de um servico
	*
	* @param id Identificador do servico
	* @param origem Local de origem do servico
	* @param destino Local de chegada do servico
	* @param tipo_camioes Tipo de camioes responsaveis pelo servico
	* @param camioes Camioes responsaveis pelo servico
	* @param horario Horario em que o servico se vai realizar
	* @param data Data em que o servico se vai realizar
	* @param disponivel Disponibilidade inicial do servico
	* @return ServicoTransporte Servico criado
	*/
    ServicoTransporte(string origem, string destino, string tipo_camioes, vector<Camiao *> camioes, string horario, Date data,unsigned disponivel,
                      unsigned n_horas);
	/**
	* @brief Retorna a disponibilidade do servico
	*
	* @return unsigned Disponibilidade do servico
	*/
    unsigned getDisponibilidade() const;
	/**
	* @brief Muda o local de origem do servico
	*
	* @param origem Novo valor a ser usado
	*/
    void setOrigem(string origem);	
	/**
	* @brief Muda o local de destino do servico
	*
	* @param destino Novo valor a ser usado
	*/
    void setDestino(string destino);	
	/**
	* @brief Muda o identificador do servico
	*
	* @param id Novo valor a ser usado
	*/
    void setId(int id);	
	/**
	* @brief Muda o horario em que o servico se vai realizar
	*
	* @param horario Novo valor a ser usado
	*/
    void setHorario(string horario);	
	/**
	* @brief Muda a data em que o servico se vai realizar
	*
	* @param d Novo valor a ser usado
	*/
    void setDate(const Date& d);	
	/**
	* @brief Retorna a distancia percorrida na rota do servico
	*
	* @param distancias Base de dados onde estao guardadas as distancias para cada rota
	* @return double Distancia percorrida na rota do servico
	*/
    double getDistancia(map<pair<string,string>,double > distancias) const;	
	/**
	* @brief Retorna o horario em que o servico se vai realizar
	*
	* @return string Horario em que o servico se vai realizar
	*/
    string getHorario() const;
	/**
	* @brief Retorna a data em que o servico se vai realizar
	*
	* @return Date Data em que o servico se vai realizar
	*/
    Date getDate() const;
	/**
	* @brief Calcula o preco do servico baseado no tipo e numero de camioes, e distancia a percorrer
	*
	* @param distancias Base de dados onde estao guardadas as distancias para cada rota
	* @return double Preco do servico
	*/
    double getPreco(map<pair<string,string>,double > distancias)const;
    /**
     * @brief Obtem o numero de horas necessarias para o servico
     * @return unsigned int com o numero de horas para o servico
     */
    unsigned getHoras()  const;
    /**
     * @brief Altera o numero de horas necessarias para o servico
     * @param h Novo numero de horas
     */
    void setHoras(unsigned h);
	/**
	* @brief Overload do operador == para averiguar a igualdade de 2 servicos
	*
	* @param st2 Servico a ser comparado
	* @return bool True se os servicos sao iguais, false caso contrario
	*/
    bool operator ==(ServicoTransporte st2);
    /**
     * @brief Metodo que elimina o camiao ca do servico instanciado
     * @param ca Camiao a ser eliminado do servico
     * @return true se o camiao ca for eliminado com sucesso, falso caso contrario
     */
    bool eliminaCamiaoServico(Camiao* ca);
	/**
	* @brief Overload do operador << para escrever numa stream informacao de um servico
	*
	* @param out Stream a ser utilizada
	* @param st Servico a ser lido
	* @return ostream Mesma stream utilizada como parametro
	*/
    friend ostream& operator <<(ostream& out,const ServicoTransporte& st);
    static double NormalMultiplicador;
    static double PerigososMultiplicador;
    static double CongelacaoMultiplicador;
    static double AnimaisMultiplicador;
    static int globalID;
	/**
	* @brief Incrementa o identificador global, usado cada vez que se cria um novo servico
	*
	*/

    //static void atualizaID();
};

//adicionar produtos, motoristas