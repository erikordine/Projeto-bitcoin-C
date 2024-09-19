#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//STRUCTS
struct{

    char cpf[50];
    char senha[50];
    float saldoBitcoin;
    float saldoEthereum;
    float saldoRiple;
    
}typedef Cliente;

struct {

    int qtdClientes;
    Cliente clientes[10];
    float total;

}typedef ListaClientes;

//FUNÇÕES MENU INICIAL
bool VoltarMenu(){
    char opcao;
    bool voltarMenu;
    while(true){
        printf("Deseja recomecar o processo(1) ou voltar ao menu(2)?\n");
        printf("Digite sua opcao aqui: ");
        scanf("%c", &opcao);
        getchar();
        switch(opcao){
            case '1':
                voltarMenu = false;
                break;
            case '2':
                voltarMenu = true;
                break;
            default:
                printf("Opcao invalida\n");
                continue;
                break;
        }
        return voltarMenu;
    }
}

ListaClientes Registrar(ListaClientes lista_Clientes, FILE* file, bool* voltarMenu){
    //INPUT E VERIFICAÇÃO DO CPF
    while(true){
        printf("Digite seu cpf -> Sem traco nem pontos: ");
        char cpf[50];
        fgets(cpf, 50, stdin);
        cpf[strlen(cpf)-1] = '\0';

        bool repetirRegistro = false;
        if(strlen(cpf) != 11){
            printf("Quantidade de caracteres invalido para o CPF\n\n");
            *voltarMenu = VoltarMenu();
            if(*voltarMenu){
                return lista_Clientes;
            }else{
                continue;
            }         
        }

        int i = 0; 
        for(i; i < strlen(cpf); i++){
            if((cpf[i] >= 65 && cpf[i] <= 90) || (cpf[i] >= 97 && cpf[i] <= 122)){
                printf("Utilize apenas numeros no seu CPF\n\n");
                *voltarMenu = VoltarMenu();
                if(*voltarMenu){
                    return lista_Clientes;
                }else{
                    continue;
                }   
            }
        }

        i = 0;
        for(i; i < sizeof(lista_Clientes.clientes) / sizeof(lista_Clientes.clientes[0]); i++){
            if(strcmp(cpf, lista_Clientes.clientes[i].cpf) == 0){
                printf("CPF ja registrado\n\n");
                *voltarMenu = VoltarMenu();
                if(*voltarMenu){
                    return lista_Clientes;
                }else{
                    continue;
                }   
            }
        }

        //INPUT E VERIFICAÇÃO DA SENHA
        printf("Digite sua senha -> Entre 5 e 10 caracteres: ");
        char senha[50];
        fgets(senha, 50, stdin);
        senha[strlen(senha)-1] = '\0';

        if(strlen(senha) < 5 || strlen(senha) > 10){
            printf("Quantidade de caracteres invalido para senha\n\n");
            *voltarMenu = VoltarMenu();
            if(*voltarMenu){
                return lista_Clientes;
            }else{
                continue;
            }   
        }

        //PASSANDO REGISTRO PRO LISTACLIENTES E ATUALIZANDO QTDCLIENTES
        strcpy(lista_Clientes.clientes[lista_Clientes.qtdClientes].senha, senha);
        strcpy(lista_Clientes.clientes[lista_Clientes.qtdClientes].cpf, cpf);
        lista_Clientes.qtdClientes++;

        //PASSANDO REGISTRO PRO TXT 
        file = fopen("teste.txt", "wb");
        fwrite(lista_Clientes.clientes, sizeof(lista_Clientes.clientes), 1, file);
        fclose(file);
        
        return lista_Clientes;
    }
}

void Logar(ListaClientes lista_Clientes, bool* voltarMenu){
    while(true){
        printf("Digite seu cpf: ");
        char cpf[50];
        fgets(cpf, 50, stdin);
        cpf[strlen(cpf)-1] = '\0';

        printf("Digite sua senha: ");
        char senha[50];
        fgets(senha, 50, stdin);
        senha[strlen(senha)-1] = '\0';

        int i = 0;
        for( i ; i < sizeof(lista_Clientes.clientes)/sizeof(lista_Clientes.clientes[0]); i++){
            if(strcmp(cpf, lista_Clientes.clientes[i].cpf) == 0 && strcmp(senha, lista_Clientes.clientes[i].senha) == 0){
                printf("Login efetuado com sucesso\n");
                return;
            }
        }

        printf("Login nao encontrado no sistema\n\n");
        *voltarMenu = VoltarMenu();
        if(*voltarMenu){
            return;
        }
    }
}

ListaClientes TxtToArray(ListaClientes lista_Clientes, FILE* file){
    file = fopen("teste.txt", "rb");
    fread(lista_Clientes.clientes, sizeof(lista_Clientes.clientes), 1, file);
    fclose(file);

    //ATUALIZANDO QUANTIDADE DE CLIENTES
    int i = 0;
    int teste = 0;
    for(i; i < sizeof(lista_Clientes.clientes) / sizeof(lista_Clientes.clientes[0]); i++){
        if(strlen(lista_Clientes.clientes[i].cpf) == 0){
        break;
        }else{
            teste++;
        }
    }
    lista_Clientes.qtdClientes = teste;
    return lista_Clientes;
}

//FUNÇÕES MENU USUÁRIO
//COMPRA
int bitcoin(){
    int buy = 1;

    while (buy)
    {
        printf("Usuario: ");
        int option;
        scanf(" %c", &option);

        switch (option)
        {
        case 1:
            break;

        case 2:
            break;
        
        case 3:
            break;

        case 4:
            break;

        case 5:
            break;

        case 6:
            break;

        case 7:
            break;

        default:
            break;
        }
    }
    
}


//MAIN
int main(){
    FILE *file;
    ListaClientes lista_Clientes;
    lista_Clientes = TxtToArray(lista_Clientes, file);

    //Menu Login/Registro
    bool voltarmenu;
    while(true){
        char menuInicial;
        printf("\nBem vindo!\n");
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
                Logar(lista_Clientes, &voltarmenu);
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
    //Menu Usuário
    // char menu;
    // fgets(&menu, sizeof(menu), stdin);

    // switch (menu)
    // {
    // case 1:
    // //Consultar Saldo
    // break;
    // case 2:
    // //Consultar Extrato
    // break;
    // case 3:
    // //Depositar
    // break;
    // case 4:
    // //Sacar
    // break;
    // case 5:
    // //Comprar cripto
    // break;
    // case 6:
    // //Vender cripto
    // break;
    // case 7:
    // //Atualizar cotação
    // break;
    // default:
    // break;
    // }
}