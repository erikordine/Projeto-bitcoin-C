#include "cadastro.c"
#include "biticoin.c"
#include <time.h>

//MENU USUARIO
// int menuUsuario(){
    
    
// }



//MAIN
int main(){
    FILE *file;
    ListaClientes lista_Clientes;
    lista_Clientes = TxtToArray(lista_Clientes, file);

    //Menu Login/Registro
    bool voltarmenu = true;
    while(voltarmenu){
        char menuInicial;
        EscreverLetraPorLetra("Bem vindo!!", 100);
        printf("1. Registrar\n");
        printf("2. Logar\n");
        printf("3. Sair\n\n");
        printf("Digite a opcao desejada: ");
        scanf(" %c", &menuInicial);
        getchar();
        switch (menuInicial) {
            case '1':
                lista_Clientes = Registrar(lista_Clientes, file, &voltarmenu);
                if(voltarmenu){
                    continue;
                }
                break;
            case '2':
                lista_Clientes = Logar(lista_Clientes, &voltarmenu);
                if(voltarmenu){
                    continue;
                }
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

    //Menu Usuario
    Criptomoedas criptomoedas;
    criptomoedas.bitcoin = 351115;
    criptomoedas.ethereum = 12980;
    criptomoedas.ripple = 3.27;

    while(true){
        char opcao;
        EscreverLetraPorLetra("Bem Vindo Sir!!", 100);
        printf("1. Consultar Saldo\n");
        printf("2. Consultar Extrato\n");
        printf("3. Depositar\n");
        printf("4. Sacar\n");
        printf("5. Comprar Criptomoeda\n");
        printf("6. Vender Criptomoeda\n");
        printf("7. Atualizar cotacao\n");
        printf("\nDigite a opcao desejada: ");
        scanf(" %c", &opcao);
        getchar();
        switch(opcao){
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
            lista_Clientes = ComprarCriptomoeda(lista_Clientes, file, criptomoedas);
            break;
          case '6':
            lista_Clientes = VenderCriptomoeda(lista_Clientes, file, criptomoedas);
            break;
          case '7':
            //ATUALIZAR COTAÇÃO
            break;
          default:
            
            break;
          }
    }
}