#pragma once
#include "menus.h"
#include "ServicoTransporte.h"
#include "Person.h"
#include "camiao.h"
#include "Empresa.h"
#include "Utils.h"
#include <algorithm>
#include "BST.h"

/**
 * @brief Mostrar informacao acerca dos camioes de um determinado tipo
 * @param e1 empresa que contem as informacoes acerca dos camioes
 */
void mostrarCamioesTipo(Empresa& e1); //mostra os camioes do tipo pretendido pelo utilizador

/**
 * @brief Selecciona um camiao registado na empresa e mostra a sua informacao
 *
 * @param e1 Dados dos camioes a ser lidos
 */
void mostrarInformacaoCamioes(Empresa& e1);

/**
 * @brief Selecciona um cliente registado na empresa e mostra a sua informacao
 *
 * @param e1 Dados dos clientes a ser lidos
 */
void mostrarInformacaoClientes(Empresa& e1);

/**
 * @brief Selecciona um servico disponível na empresa e mostra a sua informacao
 *
 * @param e1 Dados dos servicos a ser lidos
 */
void mostrarInformacaoServicos(Empresa& e1);

/**
 * @brief Mostrar no ecra informacao dos motoristas da empresa
 * @param e1 Empresa que contem informacao sobre os motoristas
 */

void mostrarInformacaoMotoristas(Empresa& e1);

/**
 * @brief Mostrar as informações relativas às oficinas
 *
 * @param e1 Empresa que contém informação sobre as oficinas
 */
void mostrarInformacaoOficinas(Empresa& e1);

/**
 * @brief Mostra dados dos utilizadores/servicos e lucro mensal da empresa
 *
 * @param e1 Dados da empresa a ser lidos
 */
void mostrarInformacaoEmpresa(Empresa& e1);

/**
 * @brief Cria e adiciona um novo cliente à base de dados da empresa
 *
 * @param e1 Base de dados onde vai ser guardado o novo cliente
 */
void adicionarClientes(Empresa& e1);

/**
 * @brief Selecciona um cliente existente na empresa e edita a sua informacao
 *
 * @param e1 Base de dados para acessar e editar o cliente
 */
void editarClientes(Empresa& e1);

/**
 * @brief Selecciona um cliente existente na empresa e remove-o
 *
 * @param e1 Base de dados de onde se vai remover o cliente
 */
void eliminarClientes(Empresa& e1);

/**
 * @brief Sub-menu do menu principal, onde se pode aceder às funcoes que dizem respeito aos clientes
 *
 * @param e1 Base de dados para passar às funcoes que operam sobre esta
 */
void gerirClientes(Empresa& e1);

/**
 * @brief Cria e adiciona um novo camiao à base de dados da empresa
 *
 * @param e1 Base de dados onde vai ser guardado o novo camiao
 */
void adicionarCamioes(Empresa& e1);

/**
 * @brief Selecciona um camiao existente na empresa e edita a sua informacao
 *
 * @param e1 Base de dados para acessar e editar o camiao
 */
void editarCamioes(Empresa& e1);

/**
 * @brief Selecciona um camiao existente na empresa e remove-o
 *
 * @param e1 Base de dados de onde se vai remover o camiao
 */
void eliminarCamioes(Empresa& e1);

/**
 * @brief Sub-menu do menu principal, onde se pode aceder às funcoes que dizem respeito aos camioes
 *
 * @param e1 Base de dados para passar às funcoes que operam sobre esta
 */
void gerirCamioes(Empresa& e1);

/**
 * @brief Cria e adiciona um novo servico à base de dados da empresa
 *
 * @param e1 Base de dados onde vai ser guardado o novo servico
 */
void adicionarServicos(Empresa& e1);

/**
 * @brief Selecciona um servico existente na empresa e edita a sua informacao
 *
 * @param e1 Base de dados para acessar e editar o servico
 */
void editarServicos(Empresa& e1);

/**
 * @brief Selecciona um servico existente na empresa e remove-o
 *
 * @param e1 Base de dados de onde se vai remover o servico
 */
void eliminarServicos(Empresa& e1);

/**
 * @brief Sub-menu do menu principal, onde se pode aceder às funcoes que dizem respeito aos servicos
 *
 * @param e1 Base de dados para passar às funcoes que operam sobre esta
 */
void gerirServicos(Empresa& e1);

/**
 * @brief Cria e adiciona um novo motorista à base de dados da empresa
 *
 * @param e1 Base de dados onde vai ser guardado o novo motorista
 */
void adicionarMotoristas(Empresa& e1);

/**
 * @brief Selecciona um motorista existente na empresa e edita a sua informacao
 *
 * @param e1 Base de dados para acessar e editar o motorista
 */
void editarMotoristas(Empresa& e1);

/**
 * @brief Selecciona um motorista existente na empresa e remove-o
 *
 * @param e1 Base de dados de onde se vai remover o motorista
 */
void eliminarMotoristas(Empresa& e1);

/**
 * @brief Sub-menu do menu principal, onde se pode aceder às funcoes que dizem respeito aos motoristas
 *
 * @param e1 Base de dados para passar às funcoes que operam sobre esta
 */
void gerirMotoristas(Empresa& e1);

/**
 * @brief Sub-menu do menu principal, onde se pode aceder às funcoes que dizem respeito a estatistícas
 *
 * @param e1 Base de dados para passar às funcoes que operam sobre esta
 */
void Estatisticas(Empresa& e1);
/**
 * @brief Menu que permite gerir os servicos das oficinas que sao prestados aos camioes
 *
 * @param e1 empresa a ser alterada
 */
void gerirServicosOficinas(Empresa& e1);
/**
 * @brief Menu principal, onde se pode aceder a vários sub-menus para operar sobre um detalhe particular da empresa
 *
 * @param e1 Base de dados para passar às funcoes que operam sobre esta
 * @return unsigned 1 se escolher a opção para saír do programa, 0 para qualquer outra opção
 */
unsigned mainMenu(Empresa& e1);