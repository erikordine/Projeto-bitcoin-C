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
            // lista_Clientes = Sacar(lista_Clientes, file);
            break;

          case '5':
            // lista_Clientes = ComprarCriptomoeda(lista_Clientes, file);
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