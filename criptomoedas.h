#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "cadastro.h"
#ifndef CRIPTOMOEDAS_H
#define CRIPTOMOEDAS_H

struct{

  float bitcoin;
  float ethereum;
  float ripple;

}typedef Criptomoedas;


//Salvar Extrato
void SalvarExtratoTXT(char operacao[], char qtd[], char criptomoeda[], char preco[], char taxa[], char arquivo[]);

//Consultar Extrato
void ConsultarExtrato(char arquivo[]);

//SALVA A ATUAL COTAÇÃO DAS CRIPTOS EM UM TXT
void CriptoToTXT(FILE* file, Criptomoedas criptomoedas);

//PASSA A ATUAL COTAÇÃO DAS CRIPTOS DO TXT PARA A STRUCT CRIPTOMOEDAS
Criptomoedas TxtToCripto(FILE* file, Criptomoedas criptomoedas);

//ATUALIZA A COTAÇÃO DAS CRIPTOMOEDAS
Criptomoedas AtualizarCotacao(Criptomoedas criptomoedas);

//EXIBE TODAS AS OPERAÇÕES REALIZADAS
void ConsultarExtrato(char arquivo[]);

//Depositar
ListaClientes Depositar(ListaClientes lista_Clientes, FILE* file);

//Sacar
ListaClientes Sacar(ListaClientes lista_Clientes, FILE* file);

//Taxa Operação Com Criptomoedas
float CalcularTaxaCriptomoeda(char operacao[], char criptomoeda[], float valor);

//Preco Criptomoeda
float CalcularPrecoCriptomoeda(char criptomoedaASerComprada[], float qtdCriptomoeda, Criptomoedas criptomoedas);

//Consultar saldo
void ConsultarSaldo(ListaClientes lista_Clientes);

#endif