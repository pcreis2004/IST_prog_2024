#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include "lib.h"

char tabela[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz .,;-";


int desencriptar1(char caracter, char *password, int o) {    
    //incialização das variaveis
    int j;
    int y = -1; 
    char return_value=caracter;    
    // calculo do offset do primeiro caracter
    for (int lol = 0; lol < 67; ++lol) {
        if (password[0] == tabela[lol]) {
            y = lol;
            break;
        }
    }    
    for (j = 0; j < 67; ++j) {
        if (caracter == tabela[j]) {
            int cifrado = (j + 67-y) % 67;
            return_value=tabela[cifrado];//muda o caracter a devolver
            if(o==0){//verifica se imprime caracter no stdout ou no ficheiro de saída
                printf("%c", tabela[cifrado]); 
            }// imprime o caracter desencriptado
            break;
        }
    }
    //imprime o caracter não cifrado caso não pertença à tabela e caso a flag do ficheiro de saída esteja a zero
    if (j == 67 && o==0) {
        printf("%c",caracter);
    }
    
    return return_value;//devolve o caracter
}

void desencriptar1_filtrado(char caracter, char *password, char **buffer,size_t *tamanho,int o) {    
    //incialização das variaveis
    int j;
    int y = -1; 
    static int count=0;
    static int index=0;
   // calculo do offset do primeiro caracter
    for (int lol = 0; lol < 67; ++lol) {
        if (password[0] == tabela[lol]) {
            y = lol;
            break;
        }
    }
    for (j = 0; j < 67; ++j) {

        if (caracter == tabela[j]) {
            int cifrado = (j + 67-y) % 67;
            (*tamanho)++;
            *buffer = (char *)realloc(*buffer, (*tamanho) * sizeof(char));//realoca mais um char para o buffer
            (*buffer)[index] = tabela[cifrado];
            if(o==0){
                printf("%c", tabela[cifrado]); //verifica se imprime caracter no stdout ou no ficheiro de saída
            }
            count++;
            index++;
        if (count == 48) { //muda de linha caso já tenham sido impressos 48 caracteres na linha
            (*tamanho)++;
            *buffer = (char *)realloc(*buffer, ((*tamanho)+1) * sizeof(char));//realoca mais um char para o buffer
            (*buffer)[index] = tabela[cifrado];
            if(o==0){//verifica se imprime caracter no stdout ou no ficheiro de saída
                printf("\n");
            }            
            count = 0;
        }
            break;
        }

    }    
    
}

int encriptar1(char caracter, char *password,int o) {    
    //incialização das variaveis
    int j;
    int y = -1; 
    char return_value=caracter;
    // calculo do offset do primeiro caracter
    for (int lol = 0; lol < 67; ++lol) {
        if (password[0] == tabela[lol]) {
            y = lol;
            
            break;
        }
    }    
    for (j = 0; j < 67; ++j) {
        if (caracter == tabela[j]) {
            int cifrado = (j + y) % 67;
            if(o==0){
                printf("%c", tabela[cifrado]); //verifica se imprime caracter no stdout ou no ficheiro de saída
            }
            return_value=tabela[cifrado];
            break;
        }
    }
    //imprime o caracter não cifrado caso não pertença à tabela e ccaso a flag do ficheiro de saída esteja a zero
    if (j == 67 && o==0) {
        printf("%c",caracter);
    }    
    return return_value;
}

void encriptar1_filtrado(char caracter, char *password, char **buffer, size_t *tamanho,int o) {
    // Incialização das variáveis
    static int count = 0;
    static int index = 0;
    // Calculo do offset do primeiro caracter
    int y = 0;
    for (int lol = 0; lol < 67; ++lol) {
        if (password[0] == tabela[lol]) {
            y = lol;
            break;
        }
    }

    for (int j = 0; j < 67; ++j) {
        if (caracter == tabela[j]) {
            int cifrado = (j + y) % 67;
            (*tamanho)++;
            *buffer = (char *)realloc(*buffer, (*tamanho) * sizeof(char));//realoca mais um char para o buffer
            if(o==0){//verifica se imprime caracter no stdout ou no ficheiro de saída
                printf("%c", tabela[cifrado]); 
            }
            (*buffer)[index] = tabela[cifrado];
            index++;
            count++;

            // Verifica se é preciso mudar de linha
            if (count == 48) {
                if(o==0){//verifica se imprime caracter no stdout ou no ficheiro de saída
                    printf("\n");
                }
                (*tamanho)++;
                *buffer = (char *)realloc(*buffer, (*tamanho) * sizeof(char));//realoca mais um char para o buffer                
                (*buffer)[index] = '\n';
                count = 0;
                index++;
            } else if (count % 6 == 0 && count % 48 != 0) {
                if(o==0){//verifica se imprime caracter no stdout ou no ficheiro de saída
                    printf("_");
                }
                (*tamanho)++;
                *buffer = (char *)realloc(*buffer, (*tamanho) * sizeof(char));//realoca mais um char para o buffer                
                (*buffer)[index] = '_';  
                index++;
            }

            break;
        }
    }
    
}

char encriptar2(char caracter, int x[], int senha_len, int *index, int o) {
    //inicialização das variáveis
    char return_value=caracter;
    int cifrado;
    int mn = (*index) % senha_len; // calculo do índice da senha
    int j;
    
    for (j = 0; j < 67; ++j) {
        if (caracter == tabela[j]) {
            cifrado = (j + x[mn]) % 67;
            if(o==0){//verifica se imprime caracter no stdout ou no ficheiro de saída
                printf("%c", tabela[cifrado]); 
            }
            return_value=tabela[cifrado];//altera o caracter a retornar
            break;
        }
    }

    //imprime o caracter não cifrado caso não pertença à tabela e caso a flag do ficheiro de saída esteja a zero
    if (j == 67 && o==0) {
        printf("%c",caracter);
    }
    //aumenta o índice só se o caracter pertencer à tabela
    if(j!=67){
      (*index)++;  
    }
    
    return return_value; 
}

char desencriptar2(char caracter, int x[], int senha_len, int *index,int o) {
    //inicialização das variáveis
    char return_value=caracter;
    int cifrado;
    int mn = (*index) % senha_len; // calculo do índice da senha
    int j;

    for (j = 0; j < 67; ++j) {
        if (caracter == tabela[j]) {
            cifrado = (j + 67 - x[mn]) % 67;
            if(o==0){//verifica se imprime caracter no stdout ou no ficheiro de saída
                printf("%c", tabela[cifrado]); 
            } 
            return_value=tabela[cifrado];

            break;
        }
    }

    //imprime o caracter não cifrado caso não pertença à tabela e ccaso a flag do ficheiro de saída esteja a zero
    if (j == 67 && o==0) {
        printf("%c",caracter);
    }
    //aumenta o índice só se o caracter pertencer à tabela
    if(j!=67){
      (*index)++;  
    }
    
    return return_value;
}

void encriptar2_filtrado(char caracter, int x[], char **buffer,int senha_len, int *index, size_t *tamanho, int o) {
    //inicialização das variáveis1
    static int count = 0;
    static int i = 0;
    int cifrado;
    int mn = (*index) % senha_len; // calculo do índice da senha
    int j;
   
    for (j = 0; j < 67; ++j) {
        if (caracter == tabela[j]) {
           
            cifrado = (j + x[mn]) % 67;
            if(o==0){//verifica se imprime caracter no stdout ou no ficheiro de saída
                printf("%c", tabela[cifrado]); // imprime o caracter cifrado
            }
            count++;
            (*tamanho)++;
            *buffer = (char *)realloc(*buffer, ((*tamanho)+1) * sizeof(char));//realoca mais um char para o buffer  
            (*buffer)[i] = tabela[cifrado];
            i++;
            if (count == 48) {
                if(o==0){//verifica se imprime caracter no stdout ou no ficheiro de saída
                    printf("\n");
                }
                i++;
                (*tamanho)++;
                *buffer = (char *)realloc(*buffer, ((*tamanho)+1) * sizeof(char));//realoca mais um char para o buffer  
                (*buffer)[i] = '\n';
                count = 0;
            } else if (count % 6 == 0 && count % 48!= 0) {
                if(o==0){//verifica se imprime caracter no stdout ou no ficheiro de saída
                    printf("_"); // Imprime um '_' a cada 7 caracteres, a não ser que seja altura de mudar de linha
                }
                (*tamanho)++;
                *buffer = (char *)realloc(*buffer, ((*tamanho)+1) * sizeof(char));//realoca mais um char para o buffer  
                (*buffer)[i] = '_';
                i++;  
                
            }
            break;
        }
    }
    //aumenta o índice só se o caracter pertencer à tabela
    if(j!=67){
      (*index)++;  
    }
    
}

void desencriptar2_filtrado(char caracter, int x[], char **buffer,int senha_len, int *index, size_t *tamanho, int o) {
    //inicialização das variáveis
    static int count = 0;
    static int i=0;
    int cifrado;
    int mn = (*index) % senha_len; // calculo do índice da senha
    int j;

    
    for (j = 0; j < 67; ++j) {
        if (caracter == tabela[j]) {
            
            cifrado = (j + 67 - x[mn]) % 67;
            if(o==0){//verifica se imprime caracter no stdout ou no ficheiro de saída
                printf("%c", tabela[cifrado]); // imprime o caracter cifrado
            }
            (*tamanho)++;
            *buffer = (char *)realloc(*buffer, ((*tamanho)+1) * sizeof(char));//realoca mais um char para o buffer 
            (*buffer)[i] = tabela[cifrado];
            count++;
            i++;
            if (count == 48) {
                if(o==0){//verifica se imprime caracter no stdout ou no ficheiro de saída
                    printf("\n");
                }
                (*tamanho)++;
                *buffer = (char *)realloc(*buffer, ((*tamanho)+1) * sizeof(char));//realoca mais um char para o buffer 
                (*buffer)[i] = '\n';
                count++;
                i++;
                count = 0;
            }
                        
            break;
        }
    }
    //aumenta o índice só se o caracter pertencer à tabela
    if(j!=67){
      (*index)++;  
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

void estatisticas(Argumentos *argumentos){

    if (argumentos->input==NULL){//verifica se existiu ficheiro de entrada
    //inicialização das variaveis
    
    int j=0;
    int inputSize = 1; 
    char caracter = '\0';
    char *input = (char *)malloc(inputSize * sizeof(char));//alocação de um vetor  com o tamanho de 1 char 
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    while (caracter != EOF) {
        
        if (scanf("%c", &caracter) < 1){

               break;
        }
        inputSize++;
        input = (char *)realloc(input, inputSize * sizeof(char));//realloca o vetor input com um char
        input[j] = caracter;
        j++;
    }
    input[j]='\0';
    int tabela_count[67] = {0};                     //Vetor das ocorrências
    int total_caracteres_tabela = 0;                
    int total_caracteres_ficheiro = strlen(input);   
    int total_outros = 0;                           

    // Calcula a ocorrência de cada caractere da Tabela 1
    for (int i = 0; i < total_caracteres_ficheiro; i++) {
        char caracter = input[i];
        for (int j = 0; j < strlen(tabela); j++) {
            if (caracter == tabela[j]) {
                tabela_count[j]++;
                total_caracteres_tabela++;
                break;
            }
        }
    }

    // Imprime a contagem e a frequência de cada caractere
    for (int i = 0; i < strlen(tabela); i++) {
        double frequencia = (double)tabela_count[i] / total_caracteres_tabela * 100;
        printf("conta('%c')=%d %.6lf%%\n", tabela[i], tabela_count[i], frequencia);
    }

    // Imprime o total de caracteres da Tabela 
    printf("Total: %d caracteres\n", total_caracteres_tabela);

    // Calcula a ocorrência de outros caracteres
    for (int i = 0; i < total_caracteres_ficheiro; i++) {
        char caracter = input[i];
        int encontrado = 0;
        for (int j = 0; j < strlen(tabela); j++) {
            if (caracter == tabela[j]) {
                encontrado = 1;
                break;
            }
        }
        if (!encontrado)
            total_outros++;
    }

    // Imprime a contagem e a frequência de caracteres fora da tabela
    double frequencia_outros = (double)total_outros / total_caracteres_ficheiro * 100;
    printf("conta(outros)=%d %.6lf%%\n", total_outros, frequencia_outros);

    // Imprime o total de caracteres no ficheiro
    printf("Total do ficheiro: %d caracteres\n", total_caracteres_ficheiro);

    }else{

    //inicialização das variaveis
    char *input = argumentos->input;
    int tabela_count[67] = {0};                     //Vetor das ocorrências
    int total_caracteres_tabela = 0; 
    int total_caracteres_ficheiro = strlen(input); 
    int total_outros = 0; 

    // Calcular a ocorrência de cada caractere
    for (int i = 0; i < total_caracteres_ficheiro; i++) {
        char caracter = input[i];
        for (int j = 0; j < strlen(tabela); j++) {
            if (caracter == tabela[j]) {
                tabela_count[j]++;
                total_caracteres_tabela++;
                break;
            }
        }
    }
    
    // Imprime a contagem e a frequência de cada caractere 
    for (int i = 0; i < strlen(tabela); i++) {
        double frequencia = (double)tabela_count[i] / total_caracteres_tabela * 100;
        printf("conta('%c')=%d %.6lf%%\n", tabela[i], tabela_count[i], frequencia);
    }

    // Imprime o total de caracteres 
    printf("Total: %d caracteres\n", total_caracteres_tabela);

    // Calcular a ocorrência de outros caracteres
    for (int i = 0; i < total_caracteres_ficheiro; i++) {
        char caracter = input[i];
        int encontrado = 0;
        for (int j = 0; j < strlen(tabela); j++) {
            if (caracter == tabela[j]) {
                encontrado = 1;
                break;
            }
        }
        if (!encontrado)
            total_outros++;
    }

    // Imprime a contagem e a frequência de outros caracteres
    double frequencia_outros = (double)total_outros / total_caracteres_ficheiro * 100;
    printf("conta(outros)=%d %.6lf%%\n", total_outros, frequencia_outros);

    // Imprime o total de caracteres no ficheiro
    printf("Total do ficheiro: %d caracteres\n", total_caracteres_ficheiro);

    }

}

void estatisticasOut(Argumentos *argumentos,char filename[]) {
    FILE *outfile; 
    // Abre/cria o ficheiro de saída
    outfile = fopen(filename, "w+");
    if (outfile == NULL) {
        fprintf(stderr, "Failed to open output file.\n");
        exit(EXIT_FAILURE);
    }

    if (argumentos->input == NULL) {
        // inicialização das variáveis
        int j = 0;
        int inputSize = 1; 
        char caracter = '\0';
        char *input = (char *)malloc(inputSize * sizeof(char)); //alocação de um vetor  com o tamanho de 1 char 
        if (input == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        while (caracter != EOF) {
            if (scanf("%c", &caracter) < 1) {
                break;
            }
            inputSize++;
            input = (char *)realloc(input, inputSize * sizeof(char)); //realloca o vetor input com um char
            input[j] = caracter;
            j++;
        }

        int tabela_count[67] = {0};                 //Vetor das ocorrências
        int total_caracteres_tabela = 0;
        int total_caracteres_ficheiro = strlen(input); 
        int total_outros = 0; 

        // Calcular a ocorrência de cada caractere
        for (int i = 0; i < total_caracteres_ficheiro; i++) {
            char caracter = input[i];
            for (int j = 0; j < strlen(tabela); j++) {
                if (caracter == tabela[j]) {
                    tabela_count[j]++;
                    total_caracteres_tabela++;
                    break;
                }
            }
        }

         // Imprime a contagem e a frequência de cada caractere 
        for (int i = 0; i < strlen(tabela); i++) {
            double frequencia = (double)tabela_count[i] / total_caracteres_tabela * 100;
            fprintf(outfile, "conta('%c')=%d %.6lf%%\n", tabela[i], tabela_count[i], frequencia);
        }

         // Imprime o total de caracteres 
        fprintf(outfile, "Total: %d caracteres\n", total_caracteres_tabela);

        // Calcular a ocorrência de outros caracteres
        for (int i = 0; i < total_caracteres_ficheiro; i++) {
            char caracter = input[i];
            int encontrado = 0;
            for (int j = 0; j < strlen(tabela); j++) {
                if (caracter == tabela[j]) {
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado)
                total_outros++;
        }
        // Imprime a contagem e a frequência de caracteres fora da tabela
        double frequencia_outros = (double)total_outros / total_caracteres_ficheiro * 100;
        fprintf(outfile, "conta(outros)=%d %.6lf%%\n", total_outros, frequencia_outros);
        // Imprime o total de caracteres no ficheiro
        fprintf(outfile, "Total do ficheiro: %d caracteres\n", total_caracteres_ficheiro);

        free(input);
    } else {
        //Inicialização das variáveis
        char *input = argumentos->input;
        int tabela_count[67] = {0}; // Array to count the occurrence of each character from Table 1
        int total_caracteres_tabela = 0; // Counter for the total characters from Table 1
        int total_caracteres_ficheiro = strlen(input); // Counter for the total characters in the file
        int total_outros = 0; // Counter for the total characters not in Table 1

        // Calcular a ocorrência de cada caractere
        for (int i = 0; i < total_caracteres_ficheiro; i++) {
            char caracter = input[i];
            
            for (int j = 0; j < strlen(tabela); j++) {
                if (caracter == tabela[j]) {
                    tabela_count[j]++;
                    total_caracteres_tabela++;
                    break;
                }
            }
        }

         // Imprime a contagem e a frequência de cada caractere 
        for (int i = 0; i < strlen(tabela); i++) {
            double frequencia = (double)tabela_count[i] / total_caracteres_tabela * 100;
            fprintf(outfile, "conta('%c')=%d %.6lf%%\n", tabela[i], tabela_count[i], frequencia);
            
        }

         // Imprime o total de caracteres 
        fprintf(outfile, "Total: %d caracteres\n", total_caracteres_tabela);
        
        // Calcular a ocorrência de outros caracteres
        for (int i = 0; i < total_caracteres_ficheiro; i++) {
            char caracter = input[i];
            int encontrado = 0;
            for (int j = 0; j < strlen(tabela); j++) {
                if (caracter == tabela[j]) {
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado)
                total_outros++;
        }

        // Imprime a contagem e a frequência de caracteres fora da tabela        
        double frequencia_outros = (double)total_outros / total_caracteres_ficheiro * 100;
        fprintf(outfile, "conta(outros)=%d %.6lf%%\n", total_outros, frequencia_outros);
        
        // Imprime o total de caracteres no ficheiro
        fprintf(outfile, "Total do ficheiro: %d caracteres\n", total_caracteres_ficheiro);
        
    }

    // Close the output file
    fclose(outfile);
}

void isValidCharacter(char *senha) {
    // Verifica se o caracter pertence à tabela
    int j;
    for (int x = 0; x < strlen(senha); x++)
    {        
        for (j = 0; j < 67; ++j) {
                if (senha[x] == tabela[j]) {
                    break;
                }
            }
            if (j == 67) {
                printf("ERRO: Password Inválida\n");
                exit(EXIT_FAILURE);
            }
    }
}

void imprimir(char *filename,Argumentos *argumentos){
    // Abre o ficheiro para escrita
    FILE *ficheiro = fopen(filename, "w+ ");
    // Verifica se houve erro na abertura do ficheiro
    if (ficheiro == NULL) {
        fprintf(stderr, "Erro ao abrir o ficheiro %s\n", filename);
        return;
    }
    // Escreve a string no ficheiro
    fprintf(ficheiro, "%s", argumentos->output);
    // Fecha o ficheiro
    fclose(ficheiro);
}

void lerficheiro(char *filename, Argumentos *argumentos){
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o ficheiro %s\n", filename);
        exit(EXIT_FAILURE);
    }
    
    // Calcula o tamanho do ficheiro
    fseek(file, 0, SEEK_END);           // Vai para o final do ficheiro
    size_t file_size = ftell(file);     // obtém o tamanho do ficheiro
    rewind(file);                       // Volta ao início do ficheiro

    // Aloca memória para o vetor de caracteres
    char *buffer = (char *)malloc(file_size + 1); // adiciona espaço para o caractere nulo
    if (buffer == NULL) {
        fprintf(stderr, "Erro de alocação de memória\n");
        exit(EXIT_FAILURE);
    }

    // coloca o conteúdo do ficheiro no buffer
    size_t bytes_read = fread(buffer, 1, file_size, file);
    if (bytes_read != file_size) {
        fprintf(stderr, "Erro ao ler o ficheiro %s\n", filename);
        exit(EXIT_FAILURE);
    }
    buffer[bytes_read] = '\0'; // termina com o caracter nulo

    // Fecha o ficheiro
    fclose(file);

    // coloca o buffer no input
    
    argumentos->input = buffer;
    

}
