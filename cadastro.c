#include "cadastro.h"

void ArrayToTXT(FILE* file, ListaClientes lista_Clientes){
    file = fopen("usuario.txt", "wb");
    fwrite(lista_Clientes.clientes, sizeof(lista_Clientes.clientes), 1, file);
    fclose(file);
}   

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
        scanf("%s", cpf);

        bool cpfDuplicado = false;
        for (int i = 0; i < lista_Clientes.qtdClientes; i++) {
            //strcmp retorna == 0 caso estiver um registro com cpf igual
            if (strcmp(cpf, lista_Clientes.clientes[i].cpf) == 0) {
                cpfDuplicado = true;
                break;
            }
        }

        if (cpfDuplicado) {
            printf("CPF ja registrado\n\n");
            *voltarMenu = VoltarMenu();
            if (*voltarMenu) {
                return lista_Clientes;
            } else {
                continue;
            }
        }

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

        //INPUT E VERIFICAÇÃO DA SENHA
        printf("Digite sua senha -> Entre 5 e 10 caracteres: ");
        char senha[50];

        scanf("%s", senha);
        strcpy(lista_Clientes.clientes[lista_Clientes.qtdClientes].senha, senha);


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
        lista_Clientes.clientes[lista_Clientes.qtdClientes].saldoReais = 0;
        lista_Clientes.clientes[lista_Clientes.qtdClientes].saldoBitcoin = 0;
        lista_Clientes.clientes[lista_Clientes.qtdClientes].saldoEthereum= 0;
        lista_Clientes.clientes[lista_Clientes.qtdClientes].saldoRipple = 0;

        //PASSANDO REGISTRO PRO TXT 
        ArrayToTXT(file, lista_Clientes);
        return lista_Clientes;
    }
}

ListaClientes Logar(ListaClientes lista_Clientes, bool* voltarMenu){
    //Verificação de login
    FILE *file = fopen("usuario.txt", "rb");
    if (file == NULL){
        printf("Erro ao abrir o arquivo.");
        return lista_Clientes;
    }

    while(true){
        printf("Digite seu cpf: ");
        char cpf[50];
        scanf("%s", cpf);
        strcpy(lista_Clientes.clientes[lista_Clientes.qtdClientes].cpf, cpf);

        printf("Digite sua senha: ");
        char senha[50];
        scanf("%s", senha);
        getchar();

        strcpy(lista_Clientes.clientes[lista_Clientes.qtdClientes].senha, senha);

        int i = 0;
        for( i ; i < sizeof(lista_Clientes.clientes)/sizeof(lista_Clientes.clientes[0]); i++){
            if(strcmp(cpf, lista_Clientes.clientes[i].cpf) == 0 && strcmp(senha, lista_Clientes.clientes[i].senha) == 0){
                printf("Login efetuado com sucesso\n\n");
                lista_Clientes.clienteAtual = i;
                *voltarMenu = false;
                return lista_Clientes;
            }
        }

        printf("Login nao encontrado no sistema\n\n");
        *voltarMenu = VoltarMenu();
        if(*voltarMenu){
            return lista_Clientes;
        }
    }
}

ListaClientes TxtToArray(ListaClientes lista_Clientes, FILE* file){
    file = fopen("usuario.txt", "rb");
    fread(lista_Clientes.clientes, sizeof(lista_Clientes.clientes), 1, file);
    fclose(file);

    //ATUALIZANDO QUANTIDADE DE CLIENTES
    int i = 0;
    int placeHolder = 0;
    for(i; i < sizeof(lista_Clientes.clientes) / sizeof(lista_Clientes.clientes[0]); i++){
        if(strlen(lista_Clientes.clientes[i].cpf) != 11){
            break;
        }else{
            placeHolder++;
        }
    }
    lista_Clientes.qtdClientes = placeHolder;
    return lista_Clientes;
}