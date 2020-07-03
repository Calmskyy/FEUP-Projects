#pragma once
#include <string>
#include <iostream>
using namespace std;

/**
 *  Excecao a ser lancada quando se tenta criar um camiao que ja existe
 */
class CamiaoRepetido {
	string marca;
	int id;
public:
	/**
	* @brief Construtor da excecao
	*
	* @param marca Marca do camiao a tentar criar
	* @param id Identificador do camiao a tentar criar
	* @return CamiaoRepetido Excecao criada
	*/
	CamiaoRepetido(string marca, int id);
	/**
	* @brief Retorna a marca do camiao a tentar criar
	*
	* @return string Marca do camiao a tentar criar
	*/
	string getMarca() const;
	/**
	* @brief Retorna o identificador do camiao a tentar criar
	*
	* @return int Identificador do camiao a tentar criar
	*/
	int getId() const;
};

/**
 *  Excecao a ser lancada quando o camiao indicado nao existe na empresa
 */
class CamiaoInexistente {
	string marca;
	int id;
public:
	/**
	* @brief Construtor da excecao
	*
	* @param id Identificador do camiao indicado
	* @param marca Marca do camiao indicado
	* @return CamiaoInexistente Excecao criada
	*/
	CamiaoInexistente(int id, string marca);
	/**
	* @brief Retorna a marca do camiao indicado
	*
	* @return string Marca do camiao indicado
	*/
	string getMarca() const;
	/**
	* @brief Retorna o identificador do camiao indicado
	*
	* @return int Identificador do camiao indicado
	*/
	int getId() const;
};

/**
 *  Representacao de um camiao da empresa
 */
class Camiao {
protected:
	int id;
	static int globalID;
	int capacidade; // Em kilogramas
	string marca;
	double km_percorridos;
public:
	/**
	* @brief Construtor de um camiao
	*
	* @param c Capacidade do camiao
	* @param tipo Marca do camiao
	* @param km_percorridos Km percorridos pelo camiao
	* @return Camiao Camiao criado
	*/
	Camiao(int c, string tipo, double km_percorridos);
	/**
	* @brief Retorna o identificador do camiao
	*
	* @return int Identificador do camiao
	*/
	int getId() const;
	/**
	* @brief Retorna a capacidade do camiao
	*
	* @return int Capacidade do camiao
	*/
	int getCapacidade() const;
	/**
	* @brief Retorna a marca do camiao
	*
	* @return string Marca do camiao
	*/
	string getMarca() const;
	/**
	* @brief Retorna os km percorridos pelo camiao
	*
	* @return double Kilometros percorridos pelo camiao
	*/
	double getKmPercorridos() const;
	/**
	* @brief Destrutor de um camiao
	*
	*/
	virtual ~Camiao() {};
	/**
	* @brief Muda o identificador do camiao
	*
	* @param id Novo valor a ser usado
	*/
	void setId(int id);
	/**
	* @brief Muda a capacidade do camiao
	*
	* @param capacidade Novo valor a ser usado
	*/
	void setCapacidade(int capacidade);
	/**
	* @brief Muda a marca do camiao
	*
	* @param marca Novo valor a ser usado
	*/
	void setMarca(string marca);
	/**
	* @brief Muda a quantidade de km percorridos pelo camiao
	*
	* @param km Novo valor a ser usado
	*/
	void setkmPercorridos(double km);
	/**
	* @brief Overload do operador == para averiguar a igualdade de 2 camioes
	*
	* @param c2 Camiao a ser comparado
	* @return bool True se os camioes sao iguais, false caso contrario
	*/
	bool operator ==(const Camiao c2);
	/**
	* @brief Overload do operador << para escrever numa stream informacao de um camiao
	*
	* @param out Stream a ser utilizada
	* @param c2 Camiao a ser lido
	* @return ostream Mesma stream utilizada como parametro
	*/
	friend ostream& operator <<(ostream& out, const Camiao& c2);
};

/**
 *  Representacao de um camiao especializado em transporte de mercadoria que necessita de congelacao
 */
class Congelacao : public Camiao {
	int tempMin; // Temperatura minima de transporte
public:
	/**
	* @brief Construtor de um camiao de congelacao
	*
	* @param c Capacidade do camiao
	* @param marca Marca do camiao
	* @param km_percorridos Km percorridos pelo camiao
	* @param tempMin Temperatura minima de transporte do camiao
	* @return Congelacao Camiao de congelacao criado
	*/
	Congelacao(int c, string marca, double km_percorridos, int tempMin);
	/**
	* @brief Retorna a temperatura minima de transporte do camiao
	*
	* @return int Temperatura minima de transporte do camiao
	*/
	int getTempMin() const;
	/**
	* @brief Muda a temperatura minima de transporte do camiao
	*
	* @param tempMin Novo valor a ser usado
	*/
	void setTempMin(int tempMin);
};

/**
 *  Representacao de um camiao especializado em transporte de mercadoria perigosa
 */
class Perigosos : public Camiao {
	string nivel; // Nivel de perigo da mercadoria(inflamavel, toxica,...)
public:
	/**
	* @brief Construtor de um camiao de mercadoria perigosa
	*
	* @param c Capacidade do camiao
	* @param marca Marca do camiao
	* @param km_percorridos Km percorridos pelo camiao
	* @param nivel Nivel de perigo da mercadoria do camiao
	* @return Perigosos Camiao de mercadoria perigosa criado
	*/
	Perigosos(int c, string marca, double km_percorridos, string nivel);
	/**
	* @brief Retorna o nivel de perigo da mercadoria do camiao
	*
	* @return string Nivel de perigo do camiao
	*/
	string getNivel() const;
	/**
	* @brief Muda o nivel de perigo da mercadoria do camiao
	*
	* @param nivel Novo valor a ser usado
	*/
	void setNivel(string nivel);
};

/**
 *  Representacao de um camiao sem especializacao da empresa
 */
class Normal : public Camiao {
public:
	/**
	* @brief Construtor de um camiao basico
	*
	* @param c Capacidade do camiao
	* @param marca Marca do camiao
	* @param km_percorridos Km percorridos pelo camiao
	* @return Normal Camiao basico criado
	*/
	Normal(int c, string marca, double km_percorridos);
};

/**
 *  Representacao de um camiao especializado em transporte de animais
 */
class Animais : public Camiao {
	int numAnimais; // Numero maximo de animais a transportar pelo camiao
public:
	/**
	* @brief Construtor de um camiao de transporte de animais
	*
	* @param c Capacidade do camiao
	* @param marca Marca do camiao
	* @param km_percorridos Km percorridos pelo camiao
	* @param numAnimais Numero maximo de animais possiveis de transportar pelo camiao
	* @return Animais Camiao de transporte de animais criado
	*/
	Animais(int c, string marca, double km_percorridos, int numAnimais);
	/**
	* @brief Retorna o numero maximo de animais possiveis de transportar pelo camiao
	*
	* @return int Numero maximo de animais do camiao
	*/
	int getNumAnimais() const;
	/**
	* @brief Muda o numero maximo de animais possiveis de transportar pelo camiao
	*
	* @param numAnimais Novo valor a ser usado
	*/
	void setNumAnimais(int numAnimais);
};

/**
 *  Excecao a ser lancada quando se tenta adicionar um servico a um camiao que se encontra ocupado na hora do servico a adicionar
 */
class CamiaoOcupado {
	Camiao* ca;
public:
	/**
	* @brief Construtor da excecao
	*
	* @param ca Camiao que se encontra ocupado
	* @return CamiaoOcupado Excecao criada
	*/
	CamiaoOcupado(Camiao* ca);
	/**
	* @brief Retorna o identificador do camiao
	*
	* @return int Identificador do camiao
	*/
	int getId() const;
};
