#pragma once

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>
#include "ServicoTransporte.h"
#include <ctime>
#include "Person.h"
#include "BST.h"
#include <list>
using namespace std;

/**
 * @brief Processa a string dada como argumento, removendo os espacos existentes nesta
 *
 * @param fullstring String a ser processada
 * @return string String recebida após remocao de espacos
 */
string removeSpaces(string fullstring);

/**
 * @brief Decompoe uma string constituída por números e um caracter delimitador, num vetor de números apenas
 *
 * @param fullstring String a ser decomposta
 * @param delimiter Caracter delimitador usado na string a ser decomposta
 * @return vector<int> Vetor com os números obtidos após a decomposicao da string recebida
 */
vector<int> stringSplit(string fullstring, char delimiter);

/**
 * @brief Obtem um vetor de servicos, ao processar uma string que contém os identificadores destes mesmos
 *
 * @param packs_str String com os identificadores a ser processada
 * @param servicos Servicos existentes para listar usando os identificadores obtidos
 * @return vector<ServicoTransporte> Vetor com os servicos obtidos após a decomposicao da string recebida
 */
vector <ServicoTransporte> servicesBuilder(string packs_str, vector<ServicoTransporte> servicos);

/**
 * @brief Obtem uma string composta pelos identificadores de todos os servicos existentes
 *
 * @param servicos Servicos existentes para serem lidos
 * @return string String com os identificadores dos servicos
 */
string to_string_id(vector<ServicoTransporte> servicos);

/**
 * @brief Separa dois locais existentes numa string que indica a distancia entre estes
 *
 * @param info String a ser processada
 * @return pair<string,string> Primeira string é o local de partida, a segunda é o destino
 */
pair<string, string> distanceSplitter(string info);

/**
 * @brief Separa dois instantes de tempo existentes numa string que indica o horário de um motorista
 *
 * @param horario String a ser processada
 * @return pair<string,string> Primeira string é a hora de comeco, a segunda é a hora final
 */
pair<string, string> toPair(string horario);

/**
 * @brief Decompoe uma string constituída por categorias num vetor de categorias
 *
 * @param categorias String a ser decomposta
 * @return vector<char> Vetor com as categorias obtidas após a decomposicao da string recebida
 */
vector<char> categoryVector(string categorias);

/**
 * @brief Compara 3 valores de tempo, para saber se o primeiro valor encontra-se entre os outros dois
 *
 * @param time Hora a avaliar se esta entre as outras duas
 * @param inicio Hora de início
 * @param fim Hora final
 * @return bool True se time esta entre inicio e fim, false se nao esta
 */
bool compareTime(istringstream& time, istringstream& inicio, istringstream& fim);

/**
 * @brief Obtem a distancia entre dois locais, se existe uma rota entre estes
 *
 * @param origem Local de partida
 * @param destino Destino do servico
 * @param distancias Listagem das distancias das rotas dos servicos
 * @return double Distancia entre os dois locais, -1 se nao existir informacao sobre estes
 */
double distanceFinder(string origem, string destino, map<pair<string, string>, double>  distancias);

/**
 * @brief Obtem um vetor de camioes, ao processar uma string que contém os identificadores destes mesmos
 *
 * @param ids String com os identificadores a ser processada
 * @param camioes Camioes existentes para listar usando os identificadores obtidos
 * @param tipo Tipo de camioes a colocar no vetor 
 * @return vector<Camiao*> Vetor com os camioes obtidos após a decomposicao da string recebida
 */
vector<Camiao*> camioesBuilder(string ids, vector<Camiao*> camioes, string tipo);

/**
 * @brief Obtem uma string composta pelos identificadores de todos os camioes existentes
 *
 * @param camioes Camioes existentes para serem lidos
 * @return string String com os identificadores dos camioes
 */
string to_string_camioes(vector<Camiao*> camioes);

/**
 * @brief Escreve uma mensagem no ecra, e de seguida lê um valor, garantindo que é um número entre determinados valores
 *
 * @param message Mensagem a ser escrita
 * @param min Limite mínimo do valor a ser lido
 * @param max Limite máximo do valor a ser lido
 * @return int Valor lido
 */
int menuValidInput(string message, int min, int max);

/**
 * @brief Escreve uma mensagem no ecra, e de seguida lê um valor, garantindo que é um número entre determinados valores
 *
 * @param message Mensagem a ser escrita
 * @param min Limite mínimo do valor a ser lido
 * @param max Limite máximo do valor a ser lido
 * @return double Valor lido
 */
double menuValidInput(string message, double min, double max);

/**
 * @brief Lê um valor de nível para um camiao, garantido que é um de três valores predefinidos
 *
 * @return string Valor lido
 */
string nivelVerifier();

/**
 * @brief Lê um valor de tipo para um camiao, e guarda no vetor aux todos os camioes deste tipo
 *
 * @param camioes Camioes existentes para serem lidos
 * @param aux Vetor onde sao guardados os camioes do mesmo tipo
 * @return string Valor lido
 */
string camioesTipoVerifier(vector<Camiao*> camioes, vector<Camiao*>& aux);

/**
 * @brief Obtem o valor maximo entre os identificadores do parametro stvect
 * @param stvect Vetor a analisar
 * @return Inteiro com o valor do identificador maximo entre os servicos de transporte do vetor stvect
 */
int GetMaxId(vector<ServicoTransporte> stvect); //obtem o maximo identificaror entre os servicos de transporte

/**
 * @brief Le um valor de horario, averiguando a sua validade
 * @param mensagem Mensagem a ser mostrada no ecrã que pede ao utilizador a insercao da data
 * @return Valor valido da data
 */

string inputHorario(string mensagem);

/**
 * @brief Averigua a validade de uma string contendo um horario
 * @param horario String a ser analisada
 * @return Valor true, se a string for valida, false caso contrario
 */

bool checkHorario(string horario);

/**
 * @brief Le um valor de nif e averigua a sua validade
 * @param mensagem Mensagem mostrada ao utilizador, pedindo a insercao do nif
 * @return Valor valido de um nif
 */

int inputNIF(string mensagem);

/**
 * @brief Transforma um vetor de servicos de transporte numa string, de modo a guardar essa informacao no ficheiro
 * @param servicos Vetor de servicos de transporte a ser transformado em string
 * @return String resultante da transformacao do parametro servicos
 */
string toStringServicos(vector<ServicoTransporte> servicos);

/**
 * @brief Obter um objeto da struct Date a partir de uma dada string
 * @param data String a ser transformada em um objeto da struct Date
 * @return Objeto valido da struct Date
 */
Date dateSplitter(string data);

/**
 * @brief Transformar um objeto da struct Date em uma string
 * @param d Objeto da struct Date a ser convertido em string
 * @return string que contem o parametro d convertido em string
 */

string toStringDate(const Date& d);

/**
 * @brief Obtem um objeto da struct Date contendo a data atual (tempo real)
 * @return Objeto da struct Date contendo a data atual (da execuçao do programa)
 */

Date getCurrentTime();

/**
 * @brief Obter o tipo de mercadorrias transportadas por um camiao
 * @param ca Apontador para o camiao a ser analisado
 * @return String que contem o tipo de mercadorias transportadas pelo camiao apontado por ca
 */

string getTipoCamiao(Camiao* ca);

/**
 * @brief Verifica a validade de uma string ao ser convertida para um objeto da struct Date
 * @param date String a ser analisada
 * @return Valor Booleano - true, caso a string seja valida; false, caso contrario
 */

bool DateVerifier(string date);

/**
 * @brief Le uma data valida (introduzida pelo utilizador)
 * @param mensagem Mensagem mostrada ao utilizador, pedindo a insercao de uma data
 * @return String contendo a data introduzida pelo utilizador
 */

string menuDateInput(string mensagem);

/**
 * @brief Algoritmo de pesquisa binario, aplicada a um vetor de chars
 * @param v Vetor no qual se pretende encontrar o valor x
 * @param x Valor a ser encontrado no vetor v
 * @return Indice do valor x no vetor v; -1 se o valor nao for encontrado
 */

int BinarySearch(const vector<char> &v, char x);

/**
 * @brief Função usada para procurar um motorista numa BST através do seu id
 * @param motoristas BST de motoristas na qual o motorista se encontra
 * @param idx Identificador do motorista a encontrar
 * @return Apontador com o motorista encontrado
 */

Motorista* findMotoristaIndex(BST<Motorista> motoristas, int idx);

/**
 * @brief Verifica se um cliente se encontra ativo
 * @param c1 Cliente a ser verificado
 * @return Inteiro com 1 se o cliente se enc
 */

int activeCheck(Cliente c1);

/**
 * @brief Função que permite separas uma string em uma lista de strings, através de um caracter separador
 * @param fullstring String com todas as strings a colocar na lista resultado
 * @param delimiter Caracter que separa as diferentes strings a colocar na lista
 * @return Lista com as diferentes strings devidamente separadas
 */

list<string> listStringSplit(string fullstring, char delimiter);

/**
 * @brief Função que permite colocar as strings de uma lista em uma string
 * @param marcas Lista com as strings a juntar
 * @return String com todas as strings contidas na lista passada no parâmetro
 */

string toStringMarcas(list <string> marcas);

/**
 * @brief Função que permite encontrar um camião num vetor de camiões através do seu id
 * @param camioes vetor de camiões onde se pretende encontrar o camião
 * @param id Identificador do camião a procurar
 * @return Apontador do camião encontrado
 */

Camiao* findCamioesID(vector <Camiao*> camioes, int id);

/**
 * @brief Função que permite saber o número de dias até uma determinada data
 * @param d Date com a data pretendida
 * @return Inteiro com o número de dias até à data passada no parâmetro
 */

int getNumDays(Date d);

/**
 * @brief Função que permite saber se um ficheiro se encontra vazio
 * @param file Ficheiro a analisar
 * @return true se o ficheiro se encontrar vazio, false caso contrário
 */

bool emptyF(ifstream& file);
