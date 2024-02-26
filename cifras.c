#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

char tabela[] = "0123456789ABCDEFGHIJKLNMOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz .,;-";



void desencriptar1(char texto[],int x) {
    int i, j;
    for (i = 0; texto[i] != '\0'; ++i) {
        for (j = 0; j < strlen(tabela); ++j) {
            if (texto[i] == tabela[j]) {
                int cifrado = (j + 67 - x) % 67;
                printf("%c", tabela[cifrado]); // Imprime o caractere correspondente ao novo índice
                break;
            }
        }
    }
    printf("\n");
}

int encriptar1(char texto[], char password[]) {
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
    return y;
}
  
   int main(int argc, char *argv[])  
{ 
    int opt; 
      
 
    while((opt = getopt(argc, argv, "hi:oi:si:fi:ci:di:ei:ai:ni:wi:")) != -1)  
    {  
        switch(opt)  
        {  
            case 'h' :
            printf("Escolha a opção que pretende utilizar:\n");
            printf("-h ajuda para o utilizador\n");
            printf("-i nome do ficheiro de entrada\n");
            printf("-o nome do ficheiro de saída\n");
            printf("-s senha a usar para cifrar/decifrar\n");
            printf("-f filtração do ficheiro de entrada e formatação do ficheiro de saída\n");
            printf("-c nn operação de cifra do método a escolher\n");
            printf("-d nn operação de decifra do método a escolher\n");
            printf("-e operação que realiza o calcula das estatísticas\n");
            printf("-a nn operação que realiza o ataque com o método a escolher\n");
            printf("-n nn dimensão maxima da chave para o método 3\n");
            printf("-w nome do ficheiro utilizado\n");
            exit(EXIT_SUCCESS);

            case 'i':
            printf("comando -> i\n");
            exit(EXIT_SUCCESS);
            

            break;

        case 'o':

            printf("comando -> o\n");
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
            exit(EXIT_SUCCESS);
            

            break;

        case 'd':
            printf("comando -> d\n");
            exit(EXIT_SUCCESS);
            

            break;

        case 'e':
            printf("comando -> e\n");
            exit(EXIT_SUCCESS);
            

            break;

        case 'a':
            printf("comando -> a\n");
            exit(EXIT_SUCCESS);
           

            break;

           
        case 'n':
            printf("comando -> n\n");
            exit(EXIT_SUCCESS);


            break;
           
            case 'w':
            printf("comando -> w\n");
            exit(EXIT_SUCCESS);
           

            break;
        
        default:

            printf("Invalid option. Use -h to see available options.\n");
            exit(EXIT_FAILURE);

        
         }  
    }  
      
int max_password_length = 100; // Maximum length of the password
    char *password = (char *)malloc(max_password_length * sizeof(char)); // Dynamically allocate memory for password

    if (password == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        return 1;
    }

    printf("Enter your password: ");

    // Use fgets to read input from the user, it's safer than scanf for reading strings
    if (fgets(password, max_password_length, stdin) != NULL) {
        // Remove the newline character at the end of the password
        password[strcspn(password, "\n")] = '\0'; // Remove the newline inserted by fgets

        printf("Password saved successfully: %s\n", password);
    } else {
        printf("Failed to read password.\n");
        free(password); // Free dynamically allocated memory before exiting
        return 1;
    }

    char texto[100];
    

    printf("Digite uma string para encriptar: ");
    fgets(texto, sizeof(texto), stdin);
    texto[strcspn(texto, "\n")] = '\0'; // Remove the newline inserted by fgets

    printf("Texto encriptado e revertido para letras: ");
    int y = encriptar1(texto, password);
    

       
    printf("Digite uma string para desencriptar: ");
    char texto_encriptado[100];
    fgets(texto_encriptado, sizeof(texto_encriptado), stdin);

    texto_encriptado[strcspn(texto_encriptado, "\n")] = '\0'; // Remove a quebra de linha inserida pelo fgets
    desencriptar1(texto_encriptado,y);
    free(password);

    return 0;
}
