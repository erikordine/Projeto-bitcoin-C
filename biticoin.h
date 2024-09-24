#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#ifndef BITICOIN_H
#define BITICOIN_H

struct{

  float bitcoin;
  float ethereum;
  float ripple;

}typedef Criptomoedas;


//DEPOSITAR
ListaClientes Depositar(ListaClientes lista_Clientes, FILE* file);

//SACAR
ListaClientes Sacar(ListaClientes lista_Clientes, FILE* file);

//Taxa comprarCriptomoeda
float CalcularTaxaCriptomoeda(char operacao[], char criptomoeda[], float valor);

//Preco criptomoeda
float CalcularPrecoCriptomoeda(char criptomoedaASerComprada[], float qtdCriptomoeda, Criptomoedas criptomoedas);

//Consultar saldo
void ConsultarSaldo(ListaClientes lista_Clientes);

#endif