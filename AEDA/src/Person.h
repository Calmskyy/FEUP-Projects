#pragma once
#include "ServicoTransporte.h"
#include <string>
#include <map>
#include <iostream>

/**
 *  Excecao a ser lancada quando o cliente indicado nao existe na empresa
 */
class ClienteInexistente{
    string name;
    int nif;
public:	
	/**
	* @brief Construtor da excecao
	*
	* @param name Nome do cliente indicado
	* @param nif NIF do cliente indicado
	* @return ClienteInexistente Excecao criada
	*/
    ClienteInexistente(string name, int nif);	
	/**
	* @brief Retorna o nome do cliente indicado
	*
	* @return string Nome do cliente indicado
	*/
    string getName() const;	
	/**
	* @brief Retorna o NIF do cliente indicado
	*
	* @return int NIF do cliente indicado
	*/
    int getNif() const;
};

/**
 *  Excecao a ser lancada quando se tenta criar um cliente que ja existe
 */
class ClienteRepetido{
    string name;
    int age;
public:	
	/**
	* @brief Construtor da excecao
	*
	* @param name Nome do cliente a tentar criar
	* @param age Idade do cliente a tentar criar
	* @return ClienteRepetido Excecao criada
	*/
    ClienteRepetido(string name, int age);	
	/**
	* @brief Retorna o nome do cliente a tentar criar
	*
	* @return string Nome do cliente a tentar criar
	*/
    string getName() const;	
	/**
	* @brief Retorna a idade do cliente a tentar criar
	*
	* @return int Idade do cliente a tentar criar
	*/
    int getAge() const;
};

/**
 *  Excecao a ser lancada quando o motorista indicado nao existe na empresa
 */
class MotoristaInexistente{
    string name;
    int id;
public:	
	/**
	* @brief Construtor da excecao
	*
	* @param name Nome do motorista indicado
	* @param id ID do motorista indicado
	* @return MotoristaInexistente Excecao criada
	*/
	MotoristaInexistente(string name, int id);
	/**
	* @brief Retorna o nome do motorista indicado
	*
	* @return string Nome do motorista indicado
	*/
    string getName() const;
	/**
	* @brief Retorna o ID do motorista indicado
	*
	* @return int ID do motorista indicado
	*/
    int getId() const;
};

/**
 *  Excecao a ser lancada quando se tenta criar um motorista que ja existe
 */
class MotoristaRepetido{
    string name;
    int id;
public:	
	/**
	* @brief Construtor da excecao
	*
	* @param name Nome do motorista a tentar criar
	* @param id ID do motorista a tentar criar
	* @return MotoristaRepetido Excecao criada
	*/
    MotoristaRepetido(string name, int id);
	/**
	* @brief Retorna o nome do motorista a tentar criar
	*
	* @return string Nome do motorista a tentar criar
	*/
    string getName() const;
	/**
	* @brief Retorna o ID do motorista a tentar criar
	*
	* @return int ID do motorista a tentar criar
	*/
    int getId() const;
};

/**
 *  Representacao de uma pessoa
 */
class Person{
protected:
    string name;
    int age;
public:
	/**
	* @brief Construtor de uma pessoa
	*
	* @param name Nome da pessoa
	* @param age Idade da pessoa
	* @return Person Pessoa criada
	*/
    Person(string name, int age);
	/**
	* @brief Retorna o nome da pessoa
	*
	* @return string Nome da pessoa
	*/
    string getName() const{
        return name;
    }
	/**
	* @brief Retorna a idade da pessoa
	*
	* @return int Idade da pessoa
	*/
    int getAge() const{
        return age;
    }	
	/**
	* @brief Muda o nome da pessoa
	*
	* @param name Novo valor a ser usado
	*/
    void setName(string name);	
	/**
	* @brief Muda a idade da pessoa
	*
	* @param age Novo valor a ser usado
	*/
    void setAge(int age);
};

/**
 *  Representacao de um cliente da empresa
 */
class Cliente: public Person{
private:
    int nif;
    int active;
    vector<ServicoTransporte> servicos_adquiridos;
public:	
	/**
	* @brief Retorna o NIF do cliente
	*
	* @return int NIF do cliente
	*/
    int getNif() const;	
	/**
	* @brief Muda o NIF do cliente
	*
	* @param nif Novo valor a ser usado
	*/
    void setNif (int nif);

    void setActive(int act);

    int getActive() const;

	/**
	* @brief Muda os servicos adquiridos pelo cliente
	*
	* @param servicos Novo valor a ser usado
	*/
    void setServicos(vector<ServicoTransporte> servicos);
	/**
	* @brief Adiciona um servico adquirido pelo cliente
	*
	* @param servico Novo servico a adicionar
	*/
    void addServico(ServicoTransporte servico);	
	/**
	* @brief Retorna os servicos adquiridos pelo cliente
	*
	* @return servicos Servicos adquiridos pelo cliente
	*/
    vector<ServicoTransporte> getServicos() const;	
	/**
	* @brief Construtor de um cliente
	*
	* @param name Nome do cliente
	* @param age Idade do cliente
	* @param nif NIF do cliente
	* @param servicos_adquiridos Servicos adquiridos pelo cliente
	* @return Cliente Cliente criado
	*/
    Cliente(string name, int age, int nif, vector<ServicoTransporte> servicos_adquiridos, int act);
	/**
	* @brief Construtor alternativo de um cliente, assumindo que tem 0 servicos adquiridos
	*
	* @param name Nome do cliente
	* @param age Idade do cliente
	* @param nif NIF do cliente
	* @return Cliente Cliente criado
	*/
    Cliente(string name, int age, int nif, int act);
	/**
	* @brief Overload do operador == para averiguar a igualdade de 2 clientes
	*
	* @param c2 Cliente a ser comparado
	* @return bool True se os clientes sao iguais, false caso contrario
	*/
    bool operator==(const Cliente c2);	
	/**
	* @brief Overload do operador << para escrever numa stream informacao de um cliente
	*
	* @param out Stream a ser utilizada
	* @param c Cliente a ser lido
	* @return ostream Mesma stream utilizada como parametro
	*/
    friend ostream& operator << (ostream& out, const Cliente& c);
};

/**
 *  Representacao de um motorista da empresa
 */
class Motorista: public Person{
    unsigned id;
    static unsigned last_id;
    int salario;
    pair <string, string> horario;
    vector<char> categorias;
    unsigned total_horas;
public:
    Motorista();
	/**
	* @brief Retorna o ID do motorista
	*
	* @return unsigned ID do motorista
	*/
    unsigned getId() const;	
	/**
	* @brief Retorna o ID do motorista mais recente
	*
	* @return unsigned ID do motorista mais recente
	*/
    static unsigned getLastId();	
	/**
	* @brief Muda o salario do motorista
	*
	* @param salary Novo valor a ser usado
	*/
    void setSalario(int salary);
    /**
     * @brief Altera o valor do id do mototista
     * @param id novo valor do identificador do motorista

    void setId(int id);*/
	/**
	* @brief Muda o horario do motorista, usando um par de hora de inicio/fim
	*
	* @param time Novo valor a ser usado
	*/
    void setHorario(pair<string, string> time);	
	/**
	* @brief Muda o horario do motorista, usando string separadas de hora de inicio/fim
	*
	* @param inicio Novo valor a ser usado para hora de inicio
	* @param fim Novo valor a ser usado para hora final
	*/
    void setHorario(string inicio, string fim);	
	/**
	* @brief Muda as categorias do motorista
	*
	* @param category Novo valor a ser usado
	*/
    void setCategorias(vector<char> category);	
	/**
	* @brief Retorna o salario do motorista
	*
	* @return int Salario do motorista
	*/
    int getSalario() const;	
	/**
	* @brief Retorna o horario do motorista
	*
	* @return pair<string, string> Horario do motorista
	*/
    pair <string, string> getHorario() const;	
	/**
	* @brief Retorna as categorias do motorista
	*
	* @return vector<char> Categorias do motorista
	*/
    vector<char> getCategorias() const;
    /**
     * @brief Obtem o numero total de horas trabaçhadas pelo motorista
     * @return inteiro com o numero de horas do respetivo motorista
     */
    int getTotalHoras() const;
	/**
	* @brief Averigua se o motorista esta a trabalhar durante a hora especificada
	*
	* @param time Hora especificada
	* @return bool True se o motorista esta a trabalhar nessa hora, false caso contrario
	*/
    bool isWorking(string time) const;
    /**
     * @brief Metodo que acresce o numero total de horas trabalhadas pelo motorista
     * @param h numero de horas a acrescentar
     */
    void addHoras(unsigned h);
	/**
	* @brief Construtor de um motorista
	*
	* @param name Nome do motorista
	* @param age Idade do motorista
	* @param salario Salario do motorista
	* @param horario Horario do motorista
	* @param categorias Categorias do motorista
	* @param total_horas numero total de horas prestadas pelo motorista
	* @return Motorista Motorista criado
	*/
    Motorista(string name, int age, int salario, pair<string, string> horario, vector<char> categorias, unsigned total_horas);
	/**
	* @brief Overload do operador == para averiguar a igualdade de 2 motoristas
	*
	* @param m Motorista a ser comparado
	* @return bool True se os motoristas sao iguais, false caso contrario
	*/
    bool operator==(const Motorista m);	
	/**
	* @brief Overload do operador << para escrever numa stream informacao de um motorista
	*
	* @param out Stream a ser utilizada
	* @param m Motorista a ser lido
	* @return ostream Mesma stream utilizada como parametro
	*/
    friend ostream& operator << (ostream& out, const Motorista& m);
    /**
     * @brief Overload do operador < para comparação entre motoristas
     * @param m motorista a comparar
     * @return bool true se o motorista (*this) for considerado menor que o motorista m
     */
    bool operator <(const Motorista& m) const;


    //void updateLastId();

};


