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


//Depositar
ListaClientes Depositar(ListaClientes lista_Clientes, FILE* file);

//Sacar
ListaClientes Sacar(ListaClientes lista_Clientes, FILE* file);

//Taxa comprarCriptomoeda
float CalcularTaxaCriptomoeda(char operacao[], char criptomoeda[], float valor);

//Preco criptomoeda
float CalcularPrecoCriptomoeda(char criptomoedaASerComprada[], float qtdCriptomoeda, Criptomoedas criptomoedas);

//Consultar saldo
void ConsultarSaldo(ListaClientes lista_Clientes);

#endif