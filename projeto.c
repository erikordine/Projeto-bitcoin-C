#include "cadastro.c"
#include "criptomoedas.c"
#include <time.h>
#include <stdlib.h>

//MENU USUARIO
// int menuUsuario(){
    
    
// }

void CriptoToTXT(FILE* file, Criptomoedas criptomoedas){
  file = fopen("criptomoedas.txt", "wb");

  char bitcoin[50];
  snprintf(bitcoin, sizeof bitcoin, "%.2f", criptomoedas.bitcoin);
  fwrite(bitcoin, sizeof(bitcoin), 1, file);

  char ethereum[50];
  snprintf(ethereum, sizeof ethereum, "%.2f", criptomoedas.ethereum);
  fwrite(ethereum, sizeof(ethereum), 1, file);

  char ripple[50];
  snprintf(ripple, sizeof ripple, "%.2f", criptomoedas.ripple);
  fwrite(ripple, sizeof(ripple), 1, file);

  fclose(file);
}

Criptomoedas TxtToCripto(FILE* file, Criptomoedas criptomoedas){
  file = fopen("criptomoedas.txt", "rb");

  if (file == NULL){
      file = fopen("criptomoedas.txt", "wb");
      fclose(file);
      criptomoedas.bitcoin = 351115;
      criptomoedas.ethereum = 12980;
      criptomoedas.ripple = 3.27;
      CriptoToTXT(file, criptomoedas);
      return criptomoedas;
  }  

  char bitcoin[50];
  char ethereum[50];
  char ripple[50];
  
  fread(bitcoin, sizeof(bitcoin), 1, file);
  fread(ethereum, sizeof(ethereum), 1, file);
  fread(ripple, sizeof(ripple), 1, file);

  criptomoedas.bitcoin = atof(bitcoin);
  criptomoedas.ethereum = atof(ethereum);
  criptomoedas.ripple = atof(ripple);

  fclose(file);

  return criptomoedas;
}

Criptomoedas AtualizarCotacao(Criptomoedas criptomoedas){
  printf("\nCotacao Antiga:\n ");
  printf("Bitcoin: %.2f\tEthereum: %.2f\tRipple: %.2f\n\n", criptomoedas.bitcoin, criptomoedas.ethereum, criptomoedas.ripple);

  srand(time(0)); 
  float number = (rand() % 11) - 5; // GERA NUMEROS ALEATORIOS DE -5 A 5, SEM NUMEROS DECIMAIS
  number = number/100;
  printf("Atualizacao aplicada: %.2f\n\n", number);
  criptomoedas.bitcoin += criptomoedas.bitcoin * number;
  criptomoedas.ethereum += criptomoedas.ethereum * number;
  criptomoedas.ripple += criptomoedas.ripple * number;

  printf("Nova Cotacao:\n ");
  printf("Bitcoin: %.2f\tEthereum: %.2f\tRipple: %.2f\n\n", criptomoedas.bitcoin, criptomoedas.ethereum, criptomoedas.ripple);
  return criptomoedas;
}

//MAIN
int main(){
    FILE *file;
    ListaClientes lista_Clientes;
    lista_Clientes = TxtToArray(lista_Clientes, file);

    //Menu Login/Registro
    bool voltarmenu = true;
    while(voltarmenu){
        char menuInicial;
        // EscreverLetraPorLetra("Bem vindo!!", 100);
        printf("\nBem vindo!!!\n");
        printf("1. Registrar\n");
        printf("2. Logar\n");
        printf("3. Sair\n\n");
        printf("Digite a opcao desejada: ");
        scanf("%c", &menuInicial);
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
                printf("Opcao invalida!\n");
                break;
        }
    }

    //Menu Usuario
    Criptomoedas criptomoedas;
    FILE* criptoFile;
    criptomoedas = TxtToCripto(criptoFile, criptomoedas);

    while(true){
        char opcao;
        // EscreverLetraPorLetra("Bem Vindo Sir!!", 100);
        printf("\nBem vindo!!!\n");
        printf("1. Consultar Saldo\n");
        printf("2. Consultar Extrato\n");
        printf("3. Depositar\n");
        printf("4. Sacar\n");
        printf("5. Comprar Criptomoeda\n");
        printf("6. Vender Criptomoeda\n");
        printf("7. Atualizar cotacao\n");
        printf("8. Sair\n");
        printf("\nDigite a opcao desejada: ");
        scanf("%c", &opcao);
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
            criptomoedas = AtualizarCotacao(criptomoedas);
            break;
          case '8':
            printf("Saindo...");
            return 0;
            break;
          default:
            
            break;
          }
          ArrayToTXT(file, lista_Clientes);
          CriptoToTXT(criptoFile, criptomoedas);
    }
}