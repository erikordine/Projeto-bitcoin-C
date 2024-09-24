#include "cadastro.c"
#include <time.h>

//MENU USUARIO
int menuUsuario(){
    
    
}

void EscreverLetraPorLetra(const char* texto, long delay) {
    struct timespec req = {0};  // Estrutura para especificar o tempo
    req.tv_sec = 0;             // Segundos (0 segundos)
    req.tv_nsec = delay * 1000000L;  // Delay em nanosegundos (1 milissegundo = 1.000.000 nanosegundos)

    while (*texto) {
        printf("%c", *texto++);
        fflush(stdout);  // Força a saída imediata do caractere
        nanosleep(&req, NULL);  // Atraso entre as letras
    }
    printf("\n");
}

//DEPOSITAR EM REAIS
ListaClientes Depositar(ListaClientes lista_Clientes, FILE* file){
  printf("Quanto voce deseja depositar?\n");
  printf("Digite a quantidade aqui - em numeros: ");
  float deposito;
  scanf("%f", &deposito);
  lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais += deposito;
  ArrayToTXT(file, lista_Clientes);
  return lista_Clientes; 
}

//SACAR EM REAIS
ListaClientes Sacar(ListaClientes lista_Clientes, FILE* file){
  printf("Saldo na carteira: %.2f\n", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais);

  //Solicitar
  printf("Quanto deseja sacar?\n");
  printf("Digite a quantidade aqui - em numeros: ");
  float saque;
  scanf("%f", &saque);

  if (saque > lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais) {
    printf("Saldo insuficiente para fazer o saque!");
  } else {
    lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais -= saque;
    printf("Saque realizado com sucesso! Novo saldo: %.2f\n", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais);

    ArrayToTXT(file, lista_Clientes);
  }

  return lista_Clientes;
}

//Taxa comprarCriptomoeda
float calcularTaxaCompra(char* criptomoeda, float valorCompra){

  if (strcmp(criptomoeda, "Bitcoin") == 0){
    return valorCompra * 0.02;
  } else if (strcmp(criptomoeda, "Ethereum") == 0){
    return valorCompra * 0.01;
  } else if (strcmp(criptomoeda, "Ripple") == 0){
    return valorCompra * 0.01;
  }

  return 0.0;
}

ListaClientes ComprarCriptomoeda(ListaClientes lista_Clientes, FILE* file){
  
  char criptomoeda;
  float valorCompra;
  char senha[50];

  printf("Usuario: %s\n", lista_Clientes.clientes[lista_Clientes.clienteAtual].cpf);
  printf("Saldo na carteira: %.2f\n", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais);

  printf("Digite a criptomoeda que deseja comprar (Bitcoin, Ethereum, Ripple): ");
  scanf("%s", criptomoeda);

  printf("Digite o valor que deseja comprar: ");
  scanf("%f", valorCompra);

  printf("Digite sua senha: ");
  scanf("%s", senha);

  if (strcmp(senha, lista_Clientes.clientes[lista_Clientes.clienteAtual].senha) != 0){
    printf("Senha incorreta!\n");
    return lista_Clientes;
  }

  float taxa = calcularTaxaCompra(criptomoeda, valorCompra);
  float valorTotal = valorCompra + taxa;

  if (valorTotal > lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais) {
    printf("Saldo insuficiente!");
    return lista_Clientes;
  }

  printf("Criptomoeda: %s\n", criptomoeda);
  printf("Valor da compra: %.2f\n", valorCompra);
  printf("Taxa combrada: %.2f\n", taxa);
  printf("Valor total da compra: %.2f\n", valorTotal);

  char confirmarCompra;
  printf("Deseja confirmar sua compra? (s/n): ");
  scanf(" %c", &confirmarCompra);

  if (confirmarCompra == 's' || confirmarCompra == 'S'){
    
    lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais -= valorTotal;
    
    if(strcmp(criptomoeda, "Biticoin") == 0){
      lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoBitcoin += valorCompra;
    } else if (strcmp(criptomoeda, "Ethereum") == 0){
      lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoEthereum += valorCompra;
    } else if (strcmp(criptomoeda, "Ripple") == 0){
      lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoRipple += valorCompra;
    }
    printf("Compra realizada com sucesso!\n");

  } else {
    printf("Compra cancelada.\n");
  }

  return lista_Clientes;

}


void ConsultarSaldo(ListaClientes lista_Clientes){
  printf("\t\nSaldo: %f", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais);
}



// -------------------------------- //

//MAIN
int main(){
    FILE *file;
    ListaClientes lista_Clientes;
    lista_Clientes = TxtToArray(lista_Clientes, file);

    //Menu Login/Registro
    bool voltarmenu;
    bool teste = true;
    while(teste){
        char menuInicial;
        EscreverLetraPorLetra("Bem vindo!", 100);
        printf("1. Registrar\n");
        printf("2. Logar\n");
        printf("3. Sair\n\n");
        printf("Digite a opcao desejada: ");
        scanf(" %c", &menuInicial);

        switch (menuInicial) {
            case '1':
                lista_Clientes = Registrar(lista_Clientes, file, &voltarmenu);
                if(voltarmenu){
                    continue;
                }
                break;
            case '2':
                Logar(lista_Clientes, &voltarmenu);
                if(voltarmenu){
                    continue;
                }
                teste = false; 
                break;
            case '3':
                printf("Saindo...\n");
                return 0;
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    }

    //Menu
    bool voltarmenu;
    while(true){
        char option;
        EscreverLetraPorLetra("Bem vindo ", 100);
        printf("1. Consultar Saldo\n");
        printf("2. Consultar Extrato\n");
        printf("3. Depositar\n");
        printf("4. Sacar\n");
        printf("5. Comprar Criptomoeda\n");
        printf("6. Vender Criptomoeda\n");
        printf("7. Atualizar cotacao\n");
        printf("\nDigite a opcao desejada: ");
        scanf(" %c", &option);
        switch (option){
          case '1':
            ConsultarSaldo(lista_Clientes);
            break;

          case '2':
            //EXTRATO
            break;
    
          case '3':
            lista_Clientes = Depositar(lista_Clientes, file);
            break;

          case '4':
            lista_Clientes = Sacar(lista_Clientes, file);
            break;

          case '5':
            lista_Clientes = ComprarCriptomoeda(lista_Clientes, file);
            break;

          case '6':
            //VENDER CRIPTOS
            break;

          case '7':
            //ATUALIZAR COTAÇÃO
            break;

          default:
            break;
          }
    }
}