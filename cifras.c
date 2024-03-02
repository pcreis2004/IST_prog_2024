#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

char tabela[] = "0123456789ABCDEFGHIJKLNMOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz .,;-";




void desencriptar1(char caracter, char *password) {
    //printf("[Encriptação]\nCifra de César com a senha: %s\n",password);
    int i, j;
    int y = -1; // Initialize y with a value indicating it's not set yet

    // Find the offset corresponding to the first character of the password
    for (int lol = 0; lol < 67; ++lol) {
        if (password[0] == tabela[lol]) {
            y = lol;
            //printf("Offset -> %d\n", y); // Print the offset corresponding to the first character of the password
            break;
        }
    }
    

    // Encrypt the text
    
        for (j = 0; j < 67; ++j) {
            if (caracter == tabela[j]) {
                int cifrado = (j + 67-y) % 67;
                
                printf("%c", tabela[cifrado]); // Print the character corresponding to the new index
                break;
            }
        }
        if (j == 67) {
            caracter = '\0';
        }
    
    
    
}



void encriptar1(char caracter, char *password) {
    //printf("[Encriptação]\nCifra de César com a senha: %s\n",password);
    int i, j;
    int y = -1; // Initialize y with a value indicating it's not set yet

    // Find the offset corresponding to the first character of the password
    for (int lol = 0; lol < 67; ++lol) {
        if (password[0] == tabela[lol]) {
            y = lol;
            //printf("Offset -> %d\n", y); // Print the offset corresponding to the first character of the password
            break;
        }
    }
    

    // Encrypt the text
    
        for (j = 0; j < 67; ++j) {
            if (caracter == tabela[j]) {
                int cifrado = (j + y) % 67;
                printf("%c", tabela[cifrado]); // Print the character corresponding to the new index
                break;
            }
        }
        if (j == 67) {
            caracter = '\0';
        }
    
    
    
}



void encriptar2(char caracter, int x[], int senha_len, int index) {
    
    int cifrado;
    int mn = index % senha_len; // Calcula o índice na senha
    int j;

    // Encripta o caractere usando a cifra de Vigenère
    for (j = 0; j < 67; ++j) {
        if (caracter == tabela[j]) {
            cifrado = (j + x[mn]) % 67;
            printf("%c", tabela[cifrado]); // Imprime o caractere cifrado
            break;
        }
    }

    if (j == 67) {
        caracter = '\0';
    }
    
}


void desencriptar2(char caracter, int x[], int senha_len, int index) {
    
    int cifrado;
    int mn = index % senha_len; // Calcula o índice na senha
    int j;

    // Encripta o caractere usando a cifra de Vigenère
    for (j = 0; j < 67; ++j) {
        if (caracter == tabela[j]) {
            cifrado = (j + 67 - x[mn]) % 67;
            printf("%c", tabela[cifrado]); // Imprime o caractere cifrado
            break;
        }
    }

    if (j == 67) {
        caracter = '\0';
    }
    
}



void help(){
    printf("Escolha a opção que pretende utilizar:\n");
    printf("-h ajuda para o utilizador\n");
    printf("-s senha a usar para cifrar/decifrar\n");
    printf("-f filtração do ficheiro de entrada e formatação do ficheiro de saída\n");
    printf("-c nn operação de cifra do método a escolher\n");
    printf("-d nn operação de decifra do método a escolher\n");
}


int main(int argc, char *argv[])  { 
    int opt; 
    //char password[100]="Programacao2024";
    
    char *senha="Programacao2024";
    printf("Argumentos passados:\n");
        // Imprime os vários argumentos com o argv
        for (int i = 0; i < argc; i++) {
            printf("Argumento %d: %s --> argv[%d]\n", i, argv[i],i);
        }  
 
    while ((opt = getopt(argc, argv, "h:s:f:c:d:")) != -1) {
        switch (opt) {
            case 'h':
                help();
                exit(EXIT_SUCCESS);
                break;

            case 's':
                printf("comando -> s\n");
                printf("[%s]\n", optarg);
                
                senha = optarg;
                printf("Senha --> {{%s}}\n", senha);
                
                break;

            case 'f':
                printf("comando -> f\n");
                break;

            case 'c':
                printf("comando -> c\n");
                
                printf("[%s]\n", optarg);
                if (atoi(optarg) == 1) {

                    char caracter = '\0'; /* inicializar com caractere zero para entrar no ciclo while em baixo */
                    printf("Insert characters: ");
                    while(caracter != EOF)
                    {
                        /* lê caractere e guarda na variável c, validando a leitura */
                        if (scanf("%c", &caracter) < 1){
                            printf("\n");
                            printf("Encriptação realizada com sucesso\n");
                            return EXIT_SUCCESS;
                        }
                        encriptar1(caracter,senha);
             
                        
                    }
                
                } else if (atoi(optarg) == 2) {


                    
                int senha_len = strlen(senha);
                int x[senha_len];
                
                // Calcula os offsets para cada caractere da senha
                for (int i = 0; i < senha_len; i++) {
                    for (int j = 0; j < 67; j++) {
                        if (senha[i] == tabela[j]) {
                            x[i] = j; // Salva o offset para o caractere da senha
                            printf("Offset -> %d\n", x[i]); // Printa o offset correspondente ao caractere da senha
                            break;
                        }
                    }
                }

                
                int index=0;
                char caracter = '\0'; /* inicializar com caractere zero para entrar no ciclo while em baixo */
                printf("Insert characters: ");
                while(caracter != EOF)
                {
                    /* lê caractere e guarda na variável c, validando a leitura */
                    if (scanf("%c", &caracter) < 1){
                        printf("\n");
                        printf("Encriptação realizada com sucesso\n");
                        return EXIT_SUCCESS;
                    }
                    encriptar2(caracter,x, senha_len,index);
                    index++;
                    
                    
                }

                }
                else {
                    printf("número inválido\n");
                    exit(EXIT_FAILURE);
                }
                break;

            case 'd':
                printf("comando -> d\n");
                printf("[%s]\n", optarg);
                if (atoi(optarg) == 1) {
                    
                    char caracter = '\0'; /* inicializar com caractere zero para entrar no ciclo while em baixo */
                    printf("Insert characters: ");
                    while(caracter != EOF)
                    {
                        /* lê caractere e guarda na variável c, validando a leitura */
                        if (scanf("%c", &caracter) < 1){
                            printf("\n");
                            printf("Encriptação realizada com sucesso\n");
                            return EXIT_SUCCESS;
                        }
                        encriptar1(caracter,senha);
             
                        
                    }
                } else if (atoi(optarg) == 2) {
                    

                    
                int senha_len = strlen(senha);
                int x[senha_len];
                
                // Calcula os offsets para cada caractere da senha
                for (int i = 0; i < senha_len; i++) {
                    for (int j = 0; j < 67; j++) {
                        if (senha[i] == tabela[j]) {
                            x[i] = j; // Salva o offset para o caractere da senha
                            printf("Offset -> %d\n", x[i]); // Printa o offset correspondente ao caractere da senha
                            break;
                        }
                    }
                }

                
                int index=0;
                char caracter = '\0'; /* inicializar com caractere zero para entrar no ciclo while em baixo */
                printf("Insert characters: ");
                while(caracter != EOF)
                {
                    /* lê caractere e guarda na variável c, validando a leitura */
                    if (scanf("%c", &caracter) < 1){
                        printf("\n");
                        printf("Encriptação realizada com sucesso\n");
                        return EXIT_SUCCESS;
                    }
                    desencriptar2(caracter,x, senha_len,index);
                    index++;
                    
                    
                }

                } else {
                    printf("número inválido\n");
                    exit(EXIT_FAILURE);
                }
                break;

            default:
                help();
                exit(EXIT_FAILURE);
        }
    
    }  
   
    
    return 0;
}
