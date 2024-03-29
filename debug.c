#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char tabela[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz .,;-";

typedef struct Argumentos {
    char *input;
    char *output;
    char *senha;
    size_t size; // Tamanho do vetor
} Argumentos;


int encriptar1_filtrado(char caracter, char *password, char *buffer, int *tamanho) {
    //incialização das variaveis
    static int count = 0;
    static int index = 0;
    // calculo do offset do primeiro caracter
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
            printf("%c", tabela[cifrado]); // imprime o caracter cifrado
            (*tamanho)++;
            buffer=(char *)realloc(buffer, (*tamanho)*sizeof(char));
            buffer[index]=tabela[cifrado];
            index++;
            count++;

            // verifica se é preciso mudar de linha
            if (count == 48) {
                printf("\n");
                tamanho++;
                buffer=(char *)realloc(buffer, (*tamanho)*sizeof(char));
                buffer[index]='\n';
                count = 0;
                index++;
            } else if (count % 6 == 0 && count % 48!= 0) { // Imprime um '_' a cada 7 caracteres, a não ser que seja altura de mudar de linha
                printf("_"); 
                (*tamanho)++;
                buffer=(char *)realloc(buffer, (*tamanho)*sizeof(char));
                buffer[index]='_';  
                index++;
            }

            break;
        }
    }
    return (*tamanho);
}


void lerficheiro(char *filename, Argumentos *argumentos){
   
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", filename);
        exit(EXIT_FAILURE);
    }
    printf("Ficheiro aberto com sucesso\n");
    // Calculando o tamanho do arquivo
    fseek(file, 0, SEEK_END); // Indo para o final do arquivo
    size_t file_size = ftell(file); // Obtendo o tamanho do arquivo
    rewind(file); // Voltando para o início do arquivo

    // Alocando memória para o vetor de caracteres
    char *buffer = (char *)malloc(file_size + 1); // +1 para o caractere nulo
    if (buffer == NULL) {
        fprintf(stderr, "Erro de alocação de memória\n");
        exit(EXIT_FAILURE);
    }

    // Lendo o conteúdo do arquivo para o buffer
    size_t bytes_read = fread(buffer, 1, file_size, file);
    if (bytes_read != file_size) {
        fprintf(stderr, "Erro ao ler o arquivo %s\n", filename);
        exit(EXIT_FAILURE);
    }
    buffer[bytes_read] = '\0'; // Adicionando o caractere nulo ao final

    // Fechando o arquivo
    fclose(file);

    // Criando a estrutura FileContent e preenchendo-a
    
    argumentos->input = buffer;
    argumentos->size = bytes_read;
    

}

int main() {
    //inicialização das variáveis
    char *senha="Programacao2024";
    
    int i = 0;
    int tamanho = 1;
    Argumentos *argumentos = malloc(sizeof(Argumentos));
    char filename[]="input.txt";
    lerficheiro(filename,argumentos);
    
    char *buffer = (char *)malloc(tamanho * sizeof(char)); 
    if (buffer == NULL) {
        fprintf(stderr, "Erro de alocação de memória\n");
        free(argumentos);
        return EXIT_FAILURE;
    }

    tamanho = 0;
    while (argumentos->input[i] != '\0') {
        tamanho = encriptar1_filtrado(argumentos->input[i], senha, buffer, &tamanho);
        i++;
    }
    argumentos->output=buffer;
    printf("\nargumentos.input -> [%s]\n", argumentos->input);            
    printf("\nbuffer --> [%s]", buffer);
    printf("\nargumentos.output -> [%s]\n", argumentos->output);
    return 1;
    


    free(argumentos->input);
    free(argumentos->output);
    free(argumentos);
       

    return 0;
}
