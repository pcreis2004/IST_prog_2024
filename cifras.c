#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

char tabela[] = "0123456789ABCDEFGHIJKLNMOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz .,;-";




void desencriptar1(char texto[], char password[]) {

    int i, j;
    int y = -1; // Initialize y with a value indicating it's not set yet

    // Find the offset corresponding to the first character of the password
    for (int lol = 0; lol < 67; ++lol) {
        if (password[0] == tabela[lol]) {
            y = lol;
            printf("Offset -> %d\n", y); // Print the offset corresponding to the first character of the password
            break;
        }
    }
    

    // Encrypt the text
    for (i = 0; texto[i] != '\0'; ++i) {
        for (j = 0; j < 67; ++j) {
            if (texto[i] == tabela[j]) {
                int cifrado = (j + 67 - y) % 67;
                printf("%c", tabela[cifrado]); // Print the character corresponding to the new index
                break;
            }
        }
        if (j == 67) {
            texto[i] = '\0';
        }
    }
    printf("\n");
}



void encriptar1(char texto[], char password[]) {
    int i, j;
    int y = -1; // Initialize y with a value indicating it's not set yet

    // Find the offset corresponding to the first character of the password
    for (int lol = 0; lol < 67; ++lol) {
        if (password[0] == tabela[lol]) {
            y = lol;
            printf("Offset -> %d\n", y); // Print the offset corresponding to the first character of the password
            break;
        }
    }
    

    // Encrypt the text
    for (i = 0; texto[i] != '\0'; ++i) {
        for (j = 0; j < 67; ++j) {
            if (texto[i] == tabela[j]) {
                int cifrado = (j + y) % 67;
                printf("%c", tabela[cifrado]); // Print the character corresponding to the new index
                break;
            }
        }
        if (j == 67) {
            texto[i] = '\0';
        }
    }
    printf("\n");
    
}


void encriptar2(char texto[], char password[]) {
    int i=0;
    int j;
    int y = -1; // Initialize y with a value indicating it's not set yet
    int x[strlen(password)];

    // Find the offset corresponding to the first character of the password
    for (i = 0; password[i] != '\0'; ++i) {    
        for (int lol = 0; lol < 67; ++lol) {
            if (password[i] == tabela[lol]) {
                x[i] = lol;
                printf("Offset -> %d\n", x[i]); // Print the offset corresponding to the first character of the password
                
            }
        }
    }



    int indice=i;
    int mn=0;
     for (i = 0; texto[i] != '\0'; ++i) {
        for (j = 0; j < 67; ++j) {
            if (texto[i] == tabela[j]) {
                if (mn >= indice) {
                    mn = 0; // Reset mn to 0
                }
                int cifrado = (j + x[mn]) % 67;
                printf("%c", tabela[cifrado]); // Print the character corresponding to the new index
                mn++;
                break;
            }
        }
        if (j == 67) {
            texto[i] = '\0';
        }
    }
    printf("\n");
    
}

void desencriptar2(char texto[],char password[]){

    int i=0;
    int j;
    int y = -1; // Initialize y with a value indicating it's not set yet
    int x[strlen(password)];

    // Find the offset corresponding to the first character of the password
    for (i = 0; password[i] != '\0'; ++i) {    
        for (int lol = 0; lol < 67; ++lol) {
            if (password[i] == tabela[lol]) {
                x[i] = lol;
                printf("Offset -> %d\n", x[i]); // Print the offset corresponding to the first character of the password
                
            }
        }
    }



    int indice=i;
    int mn=0;
     for (i = 0; texto[i] != '\0'; ++i) {
        for (j = 0; j < 67; ++j) {
            if (texto[i] == tabela[j]) {
                if (mn >= indice) {
                    mn = 0; // Reset mn to 0
                }
                int cifrado = (j + 67 - x[mn]) % 67;
                printf("%c", tabela[cifrado]); // Print the character corresponding to the new index
                mn++;
                break;
            }
        }
        if (j == 67) {
            texto[i] = '\0';
        }
    }
    printf("\n");
}

void help(){
    printf("Escolha a opmnão que pretende utilizar:\n");
    printf("-h ajuda para o utilizador\n");
    printf("-s senha a usar para cifrar/decifrar\n");
    printf("-f filtração do ficheiro de entrada e formatação do ficheiro de saída\n");
    printf("-c nn operação de cifra do método a escolher\n");
    printf("-d nn operação de decifra do método a escolher\n");
}


int main(int argc, char *argv[])  { 
    int opt; 
      
 
    while((opt = getopt(argc, argv, "h:s:f:c:d:")) != -1)  
    {  
        switch(opt)  
        {  
            case 'h' :
            help();
            exit(EXIT_SUCCESS);
            break;


        case 's':
            printf("comando -> s\n");
            exit(EXIT_SUCCESS);
           
            break;

        case 'f':
            printf("comando -> f\n");
            exit(EXIT_SUCCESS);

            break;

        case 'c':
            printf("comando -> c\n");
           
            printf("[%s]\n",optarg);
            if (atoi(optarg) ==1){

                char texto[100];
                
                char password[100];
                printf("Digite uma string para password: ");
                fgets(password, sizeof(password), stdin);
                password[strcspn(password, "\n")] = '\0'; // Remove the newline inserted by fgets
                printf("Digite uma string para encriptar: ");
                fgets(texto, sizeof(texto), stdin);
                texto[strcspn(texto, "\n")] = '\0'; // Remove the newline inserted by fgets
                printf("Texto encriptado e revertido para letras: ");
                encriptar1(texto, password);

            exit(EXIT_SUCCESS);
            }           

            if(atoi(optarg)==2)
            {
                char password[100];
                printf("Digite uma string para password: ");
                fgets(password, sizeof(password), stdin);
                password[strcspn(password, "\n")] = '\0'; // Remove the newline inserted by fgets
                char texto_encriptado[100];
                printf("Digite uma string para encriptar: ");
                fgets(texto_encriptado, sizeof(texto_encriptado), stdin);

                texto_encriptado[strcspn(texto_encriptado, "\n")] = '\0'; // Remove a quebra de linha inserida pelo fgets
                printf("Texto encriptado e revertido para letras: ");
                encriptar2(texto_encriptado,password);
                
                exit(EXIT_SUCCESS);
            }else{printf("número inválido\n");
            exit(EXIT_FAILURE);
            }
            
            break;

        case 'd':
            printf("comando -> d\n");
            
            printf("[%s]\n",optarg);
            if (atoi(optarg) ==1){

                char texto[100];
                
                char password[100];
                printf("Digite uma string para password: ");
                fgets(password, sizeof(password), stdin);
                password[strcspn(password, "\n")] = '\0'; // Remove the newline inserted by fgets
                printf("Digite uma string para desencriptar: ");
                fgets(texto, sizeof(texto), stdin);
                texto[strcspn(texto, "\n")] = '\0'; // Remove the newline inserted by fgets
                printf("Texto desencriptado e revertido para letras: ");
                desencriptar1(texto, password);

            exit(EXIT_SUCCESS);
            }           

            if(atoi(optarg)==2)
            {
                char password[100];
                printf("Digite uma string para password: ");
                fgets(password, sizeof(password), stdin);
                password[strcspn(password, "\n")] = '\0'; // Remove the newline inserted by fgets
                char texto_encriptado[100];
                printf("Digite uma string para desencriptar: ");
                fgets(texto_encriptado, sizeof(texto_encriptado), stdin);

                texto_encriptado[strcspn(texto_encriptado, "\n")] = '\0'; // Remove a quebra de linha inserida pelo fgets
                printf("Texto desencriptado e revertido para letras: ");
                desencriptar2(texto_encriptado,password);
                
                exit(EXIT_SUCCESS);
            }else{printf("número inválido\n");
            exit(EXIT_FAILURE);
            }
            
            

            break;
        default:

            help();
            exit(EXIT_FAILURE);

        
         }  
    }  
   /*
    char password[100];
    char texto[100];
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove the newline inserted by fgets

    printf("Digite uma string para encriptar: ");
    fgets(texto, sizeof(texto), stdin);
    texto[strcspn(texto, "\n")] = '\0'; // Remove the newline inserted by fgets
    
    printf("Texto encriptado e revertido para letras: ");
    //encriptar1(texto, password);
    
    encriptar2(texto,password);
       
    printf("Digite uma string para desencriptar: ");
    char texto_encriptado[100];
    fgets(texto_encriptado, sizeof(texto_encriptado), stdin);

    texto_encriptado[strcspn(texto_encriptado, "\n")] = '\0'; // Remove a quebra de linha inserida pelo fgets
    //desencriptar1(texto_encriptado,password);
    
    
    desencriptar2(texto_encriptado,password);
    //free(password);
    */
    help();
    exit(EXIT_FAILURE);
    return 0;
}
