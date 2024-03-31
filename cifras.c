#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>

char tabela[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz .,;-";

typedef struct Argumentos {
    char *input;
    char *output;
    char *senha;
    size_t size; // Tamanho do vetor
} Argumentos;

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
            return_value=tabela[cifrado];
            if(o==0){
                printf("%c", tabela[cifrado]); 
            }// imprime o caracter desencriptado
            break;
        }
    }
    //imprime o caracter não cifrado cajo não pertença à tabela
    if (j == 67 && o==0) {
        printf("%c",caracter);
    }
    
    return return_value;
}

size_t desencriptar1_filtrado(char caracter, char *password, char **buffer,size_t *tamanho,int o) {
    
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
            *buffer = (char *)realloc(*buffer, (*tamanho) * sizeof(char));
            (*buffer)[index] = tabela[cifrado];
            if(o==0){
                printf("%c", tabela[cifrado]); // imprime o caracter desencriptado
            }
            count++;
            index++;
        if (count == 48) { //muda de linha caso já tenham sido impressos 48 caracteres na linha
            (*tamanho)++;
            *buffer = (char *)realloc(*buffer, ((*tamanho)+1) * sizeof(char));
            (*buffer)[index] = tabela[cifrado];
            if(o==0){
                printf("\n");
            }            
            count = 0;
        }
            break;
        }

    }
        
    
    
    return *tamanho;
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
                printf("%c", tabela[cifrado]); // imprime o caracter desencriptado
            }
            return_value=tabela[cifrado];
            break;
        }
    }
    //imprime o caracter não cifrado cajo não pertença à tabela
    if (j == 67 && o==0) {
        printf("%c",caracter);
    }
    
    
    
    return return_value;
}

size_t encriptar1_filtrado(char caracter, char *password, char **buffer, size_t *tamanho,int o) {
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
            *buffer = (char *)realloc(*buffer, (*tamanho) * sizeof(char));

            
           if(o==0){
                printf("%c", tabela[cifrado]); // imprime o caracter desencriptado
            }
            (*buffer)[index] = tabela[cifrado];
            index++;
            count++;

            // Verifica se é preciso mudar de linha
            if (count == 48) {
                if(o==0){
                    printf("\n");
                }
                (*tamanho)++;
                *buffer = (char *)realloc(*buffer, (*tamanho) * sizeof(char));                //printf("tamanho = %ld\n",*tamanho);
                (*buffer)[index] = '\n';
                count = 0;
                index++;
            } else if (count % 6 == 0 && count % 48 != 0) {
                if(o==0){
                    printf("_");
                }
                (*tamanho)++;
                *buffer = (char *)realloc(*buffer, (*tamanho) * sizeof(char));                //printf("tamanho = %ld\n",*tamanho);
                (*buffer)[index] = '_';  
                index++;
            }

            break;
        }
    }
    return *tamanho;
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
            if(o==0){
                printf("%c", tabela[cifrado]); // imprime o caracter desencriptado
            }
            return_value=tabela[cifrado];
            break;
        }
    }

    //imprime o caracter não cifrado cajo não pertença à tabela
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
            if(o==0){
                printf("%c", tabela[cifrado]); // imprime o caracter desencriptado
            } 
            return_value=tabela[cifrado];

            break;
        }
    }

    //imprime o caracter não cifrado cajo não pertença à tabela
    if (j == 67 && o==0) {
        printf("%c",caracter);
    }
    //aumenta o índice só se o caracter pertencer à tabela
    if(j!=67){
      (*index)++;  
    }
    
    return return_value;
}

size_t encriptar2_filtrado(char caracter, int x[], char **buffer,int senha_len, int *index, size_t *tamanho, int o) {
    //inicialização das variáveis1
    static int count = 0;
    static int i = 0;
    int cifrado;
    int mn = (*index) % senha_len; // calculo do índice da senha
    int j;

   
    for (j = 0; j < 67; ++j) {
        if (caracter == tabela[j]) {
           
            cifrado = (j + x[mn]) % 67;
            if(o==0){
                printf("%c", tabela[cifrado]); // imprime o caracter cifrado
            }
            count++;
            (*tamanho)++;
            *buffer = (char *)realloc(*buffer, ((*tamanho)+1) * sizeof(char));
            (*buffer)[i] = tabela[cifrado];
            i++;
            if (count == 48) {
                if(o==0){
                    printf("\n");
                }
                i++;
                (*tamanho)++;
                *buffer = (char *)realloc(*buffer, ((*tamanho)+1) * sizeof(char));
                (*buffer)[i] = '\n';
                count = 0;
            } else if (count % 6 == 0 && count % 48!= 0) {
                if(o==0){
                    printf("_"); // Imprime um '_' a cada 7 caracteres, a não ser que seja altura de mudar de linha
                }
                (*tamanho)++;
                *buffer = (char *)realloc(*buffer, ((*tamanho)+1) * sizeof(char));
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
    return *tamanho;
}

size_t desencriptar2_filtrado(char caracter, int x[], char **buffer,int senha_len, int *index, size_t *tamanho, int o) {
    //inicialização das variáveis
    static int count = 0;
    static int i=0;
    int cifrado;
    int mn = (*index) % senha_len; // calculo do índice da senha
    int j;

    
    for (j = 0; j < 67; ++j) {
        if (caracter == tabela[j]) {
            
            cifrado = (j + 67 - x[mn]) % 67;
            if(o==0){
                printf("%c", tabela[cifrado]); // imprime o caracter cifrado
            }
            (*tamanho)++;
            *buffer = (char *)realloc(*buffer, ((*tamanho)+1) * sizeof(char));
            (*buffer)[i] = tabela[cifrado];
            count++;
            i++;
            if (count == 48) {
                if(o==0){
                    printf("\n");
                }
                (*tamanho)++;
                *buffer = (char *)realloc(*buffer, ((*tamanho)+1) * sizeof(char));
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
    return (*tamanho);
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

    if (argumentos->input==NULL){
    //inicialização das variaveis
    
    int j=0;
    int inputSize = 1; // Tamanho inicial de 1 char 
    char caracter = '\0';
    char *input = (char *)malloc(inputSize * sizeof(char));//alocação de um vetor de chars com o tamanho de 1 char 
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    while (caracter != EOF) {
        
        if (scanf("%c", &caracter) < 1){

               break;
        }
        inputSize++;
        input = (char *)realloc(input, inputSize * sizeof(char));//aumentar o vetor input por um char de cada vez q é lido um caracter
        input[j] = caracter;
        j++;
    }
    input[j]='\0';
    int tabela_count[67] = {0}; // Array para contar a ocorrência de cada caractere da Tabela 1
    int total_caracteres_tabela = 0; // Contador para o total de caracteres da Tabela 1
    int total_caracteres_arquivo = strlen(input); // Contador para o total de caracteres no arquivo
    int total_outros = 0; // Contador para o total de caracteres que não estão na Tabela 1

    // Calcular a ocorrência de cada caractere da Tabela 1
    for (int i = 0; i < total_caracteres_arquivo; i++) {
        char caracter = input[i];
        for (int j = 0; j < strlen(tabela); j++) {
            if (caracter == tabela[j]) {
                tabela_count[j]++;
                total_caracteres_tabela++;
                break;
            }
        }
    }

    // Imprime a contagem e a frequência de cada caractere da Tabela 1
    for (int i = 0; i < strlen(tabela); i++) {
        double frequencia = (double)tabela_count[i] / total_caracteres_tabela * 100;
        printf("conta('%c')=%d %.6lf%%\n", tabela[i], tabela_count[i], frequencia);
    }

    // Imprime o total de caracteres da Tabela 1
    printf("Total: %d caracteres\n", total_caracteres_tabela);

    // Calcular a ocorrência de outros caracteres
    for (int i = 0; i < total_caracteres_arquivo; i++) {
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
    double frequencia_outros = (double)total_outros / total_caracteres_arquivo * 100;
    printf("conta(outros)=%d %.6lf%%\n", total_outros, frequencia_outros);

    // Imprime o total de caracteres no arquivo
    printf("Total do ficheiro: %d caracteres\n", total_caracteres_arquivo);

    
    
    
    }else{


        
    //inicialização das variaveis
    char *input = argumentos->input;
    int tabela_count[67] = {0}; // Array para contar a ocorrência de cada caractere da Tabela 1
    int total_caracteres_tabela = 0; // Contador para o total de caracteres da Tabela 1
    int total_caracteres_arquivo = strlen(input); // Contador para o total de caracteres no arquivo
    int total_outros = 0; // Contador para o total de caracteres que não estão na Tabela 1

    // Calcular a ocorrência de cada caractere da Tabela 1
    for (int i = 0; i < total_caracteres_arquivo; i++) {
        char caracter = input[i];
        for (int j = 0; j < strlen(tabela); j++) {
            if (caracter == tabela[j]) {
                tabela_count[j]++;
                total_caracteres_tabela++;
                break;
            }
        }
    }
    
    // Imprime a contagem e a frequência de cada caractere da Tabela 1
    for (int i = 0; i < strlen(tabela); i++) {
        double frequencia = (double)tabela_count[i] / total_caracteres_tabela * 100;
        printf("conta('%c')=%d %.6lf%%\n", tabela[i], tabela_count[i], frequencia);
    }

    // Imprime o total de caracteres da Tabela 1
    printf("Total: %d caracteres\n", total_caracteres_tabela);

    // Calcular a ocorrência de outros caracteres
    for (int i = 0; i < total_caracteres_arquivo; i++) {
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
    double frequencia_outros = (double)total_outros / total_caracteres_arquivo * 100;
    printf("conta(outros)=%d %.6lf%%\n", total_outros, frequencia_outros);

    // Imprime o total de caracteres no arquivo
    printf("Total do ficheiro: %d caracteres\n", total_caracteres_arquivo);






    }

}



void estatisticasOut(Argumentos *argumentos,char filename[]) {
    FILE *outfile; // File pointer for the output file

    

    // Open the output file for writing
    outfile = fopen(filename, "w+");
    if (outfile == NULL) {
        fprintf(stderr, "Failed to open output file.\n");
        exit(EXIT_FAILURE);
    }

    if (argumentos->input == NULL) {
        // Initialization of variables
        int j = 0;
        int inputSize = 1; // Initial size of 1 char 
        char caracter = '\0';
        char *input = (char *)malloc(inputSize * sizeof(char)); // Allocate a char array with size of 1 char
        if (input == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        while (caracter != EOF) {
            if (scanf("%c", &caracter) < 1) {
                break;
            }
            inputSize++;
            input = (char *)realloc(input, inputSize * sizeof(char)); // Increase the input array by one char each time a character is read
            input[j] = caracter;
            j++;
        }

        int tabela_count[67] = {0}; // Array to count the occurrence of each character from Table 1
        int total_caracteres_tabela = 0; // Counter for the total characters from Table 1
        int total_caracteres_arquivo = strlen(input); // Counter for the total characters in the file
        int total_outros = 0; // Counter for the total characters not in Table 1

        // Calculate the occurrence of each character from Table 1
        for (int i = 0; i < total_caracteres_arquivo; i++) {
            char caracter = input[i];
            for (int j = 0; j < strlen(tabela); j++) {
                if (caracter == tabela[j]) {
                    tabela_count[j]++;
                    total_caracteres_tabela++;
                    break;
                }
            }
        }

        // Write the count and frequency of each character from Table 1 to the output file
        for (int i = 0; i < strlen(tabela); i++) {
            double frequencia = (double)tabela_count[i] / total_caracteres_tabela * 100;
            fprintf(outfile, "conta('%c')=%d %.6lf%%\n", tabela[i], tabela_count[i], frequencia);
        }

        // Write the total characters from Table 1 to the output file
        fprintf(outfile, "Total: %d caracteres\n", total_caracteres_tabela);

        // Calculate the occurrence of other characters
        for (int i = 0; i < total_caracteres_arquivo; i++) {
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

        // Write the count and frequency of other characters to the output file
        double frequencia_outros = (double)total_outros / total_caracteres_arquivo * 100;
        fprintf(outfile, "conta(outros)=%d %.6lf%%\n", total_outros, frequencia_outros);

        // Write the total characters in the file to the output file
        fprintf(outfile, "Total do ficheiro: %d caracteres\n", total_caracteres_arquivo);

        free(input);
    } else {
        
        // Initialization of variables
        char *input = argumentos->input;
        int tabela_count[67] = {0}; // Array to count the occurrence of each character from Table 1
        int total_caracteres_tabela = 0; // Counter for the total characters from Table 1
        int total_caracteres_arquivo = strlen(input); // Counter for the total characters in the file
        int total_outros = 0; // Counter for the total characters not in Table 1

        // Calculate the occurrence of each character from Table 1
        for (int i = 0; i < total_caracteres_arquivo; i++) {
            char caracter = input[i];
            
            for (int j = 0; j < strlen(tabela); j++) {
                if (caracter == tabela[j]) {
                    tabela_count[j]++;
                    total_caracteres_tabela++;
                    break;
                }
            }
        }

        // Write the count and frequency of each character from Table 1 to the output file
        for (int i = 0; i < strlen(tabela); i++) {
            double frequencia = (double)tabela_count[i] / total_caracteres_tabela * 100;
            fprintf(outfile, "conta('%c')=%d %.6lf%%\n", tabela[i], tabela_count[i], frequencia);
            
        }

        // Write the total characters from Table 1 to the output file
        fprintf(outfile, "Total: %d caracteres\n", total_caracteres_tabela);
        
        // Calculate the occurrence of other characters
        for (int i = 0; i < total_caracteres_arquivo; i++) {
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

        // Write the count and frequency of other characters to the output file
        double frequencia_outros = (double)total_outros / total_caracteres_arquivo * 100;
        fprintf(outfile, "conta(outros)=%d %.6lf%%\n", total_outros, frequencia_outros);
        
        // Write the total characters in the file to the output file
        fprintf(outfile, "Total do ficheiro: %d caracteres\n", total_caracteres_arquivo);
        
    }

    // Close the output file
    fclose(outfile);
}


int encriptacao(int metodo,int f,char *senha,Argumentos* argumentos, int o){//função que analisa os argumentos da linha de comando caso seja realizada um operação de encriptação

    if (metodo==1 && f==0){
        //inicialização das variáveis



        
        char caracter = 'l';
        int i = 0;
        int tamanho=1;
        if (argumentos->input==NULL){

            char *buffer = (char *)malloc(tamanho*sizeof(char));
                while(caracter != EOF){//Lê caracter a caracter do stdin até ler um EOF
                
                buffer = (char *)realloc(buffer, tamanho * sizeof(char));
                if (scanf("%c", &caracter) < 1){
                    
                    argumentos->output=buffer;
                    return 1;
                }
                buffer[i]=encriptar1(caracter,senha,o);//função de encriptação dos caracteres
                i++;
                tamanho++;
            }

        }else{

        
        char *buffer = (char *)malloc(tamanho * sizeof(char)); 
        if (buffer == NULL) {
        fprintf(stderr, "Erro de alocação de memória\n");
        exit(EXIT_FAILURE);
        }
        while (argumentos->input[i] != '\0') {
                buffer = (char *)realloc(buffer,tamanho*sizeof(char));
                buffer[i] = encriptar1(argumentos->input[i], senha,o);
                i++;
                tamanho++;
        }


        
        argumentos->output = buffer;



        return 1;
        }

    }else if (metodo == 1 && f==1){
        //inicialização das variáveis
        char caracter = '\0';
        int i = 0;
        size_t tamanho=0; 
        if (argumentos->input==NULL){
        char *buffer = NULL;
        while(caracter != EOF)
        {
            //Lê caracter a caracter do stdin até ler um EOF
            if (scanf("%c", &caracter) < 1){
                printf("\n");
                tamanho++;
                buffer = (char *)realloc(buffer, ((tamanho) * sizeof(char))); 
                argumentos->output=buffer;
                return 1;
                
                }
            tamanho=encriptar1_filtrado(caracter, senha, &buffer, &tamanho,o);//função de encriptação dos caracteres com filtragem

            
        }

        }else{
            
            char *buffer = NULL;
            size_t j=0;
            while (argumentos->input[j] != '\0') {
                tamanho = encriptar1_filtrado(argumentos->input[j], senha, &buffer, &tamanho,o);
                i++;
                j++;
                
            }
            buffer[tamanho+1] = '\0';
            tamanho++;
            buffer = (char *)realloc(buffer, tamanho * sizeof(char));
            buffer[tamanho-1]='\n';
            printf("\n");
            argumentos->output=buffer;
            return 1;
        }

    }
    
    if (metodo==2 && f==0)
    {
        //inicialização das variáveis
        int senha_len = strlen(senha);
        int x[senha_len];
        int index=0;
        char caracter = '\0'; 
        char *buffer = NULL; 
        size_t tamanho=0;
        int i=0;


        if (argumentos->input==NULL){
            
            // Calcula os offsets de todos os caracteres e guarda tudo num vetor de inteiros
            for (int i = 0; i < senha_len; i++) {
                for (int j = 0; j < 67; j++) {
                    if (senha[i] == tabela[j]) {
                        x[i] = j; 
                        
                        break;
                    }
                }
            }
         
            while(caracter != EOF)
            {
                //Lê caracter a caracter do stdin até ler um EOF
                if (scanf("%c", &caracter) < 1){
                    buffer[tamanho+1] = '\0';
                    argumentos->output=buffer;
                    return 1;
                    //exit(EXIT_SUCCESS);
                }
                tamanho++;
                buffer = (char *)realloc(buffer, tamanho * sizeof(char));
                buffer[i]=encriptar2(caracter,x, senha_len,&index,o);//função de encriptação dos caracteres
                //3printf("\n\n[%d]\n\n",index);
                i++;
            }    

        }else{

               // Calcula os offsets de todos os caracteres e guarda tudo num vetor de inteiros
                for (int i = 0; i < senha_len; i++) {
                    for (int j = 0; j < 67; j++) {
                        if (senha[i] == tabela[j]) {
                            x[i] = j; 
                            
                            break;
                        }
                    }
                }

                
                
                int j=0;
                while(argumentos->input[j] != '\0')
                {
                    tamanho++;
                    buffer = (char *)realloc(buffer, tamanho * sizeof(char));
                    buffer[i]=encriptar2(argumentos->input[j],x, senha_len,&index,o);//função de encriptação dos caracteres
                    j++;
                    //3printf("\n\n[%d]\n\n",index);
                    i++;
                }
                buffer[tamanho+1] = '\0';
                argumentos->output=buffer;
                return 1;    

        }



        
    }else if (metodo==2 && f==1)
    {
        //inicialização das variaveis
        int senha_len = strlen(senha);
        int x[senha_len];
        int index=0;
        char caracter = '\0'; 
        size_t tamanho=0;
        if(argumentos->input==NULL){
        // Calcula os offsets de todos os caracteres e guarda tudo num vetor de inteiros
        for (int i = 0; i < senha_len; i++) {
            for (int j = 0; j < 67; j++) {
                if (senha[i] == tabela[j]) {
                    x[i] = j; 
                    
                    break;
                }
            }
        }

        char *buffer=NULL;
        
        
        while(caracter != EOF)
        {
            //Lê caracter a caracter do stdin até ler um EOF
            if (scanf("%c", &caracter) < 1){
                 buffer[tamanho+1] = '\0';
                tamanho++;
                buffer = (char *)realloc(buffer, tamanho * sizeof(char));
                buffer[tamanho-1]='\n';
                printf("\n");
                argumentos->output=buffer;

                return 1;
                
            }
            
            
            tamanho=encriptar2_filtrado(caracter,x, &buffer,senha_len,&index,&tamanho,o);//função de encriptação dos caracteres com filtragem

            
            
            
        }
        }else{

            for (int i = 0; i < senha_len; i++) {
            for (int j = 0; j < 67; j++) {
                if (senha[i] == tabela[j]) {
                    x[i] = j; 
                    
                    break;
                }
            }
        }

        char *buffer=NULL;
        int i = 0;

        while(argumentos->input[i] != '\0')
        {
            tamanho=encriptar2_filtrado(argumentos->input[i],x, &buffer,senha_len,&index,&tamanho,o);//função de encriptação dos caracteres com filtragem
            i++;    
        }
        buffer[tamanho+1] = '\0';
        tamanho++;
        buffer = (char *)realloc(buffer, tamanho * sizeof(char));
        buffer[tamanho-1]='\n';
        printf("\n");
        argumentos->output=buffer;
        return 1;
        }

    }
    
    printf("Operação Errada linha 552\n");
    exit(EXIT_FAILURE);
    return 0;
}

int decriptacao(int metodo,int f,char *senha,Argumentos* argumentos, int o){

    if (metodo==1 && f==0){

    //inicialização das variáveis


        char caracter = 'l';
        int i = 0;
        int tamanho=1;
        if (argumentos->input==NULL){

            char *buffer = (char *)malloc(tamanho*sizeof(char));
                while(caracter != EOF){//Lê caracter a caracter do stdin até ler um EOF
                
                buffer = (char *)realloc(buffer, tamanho * sizeof(char));
                if (scanf("%c", &caracter) < 1){
                    
                    argumentos->output=buffer;
                    return 1;
                }
                buffer[i]=desencriptar1(caracter,senha,o);//função de encriptação dos caracteres
                i++;
                tamanho++;
            }

        }else{

        
        char *buffer = (char *)malloc(tamanho * sizeof(char)); 
        if (buffer == NULL) {
        fprintf(stderr, "Erro de alocação de memória\n");
        exit(EXIT_FAILURE);
        }
        while (argumentos->input[i] != '\0') {
                buffer = (char *)realloc(buffer,tamanho*sizeof(char));
                buffer[i] = desencriptar1(argumentos->input[i], senha,o);
                i++;
                tamanho++;
        }


        
        argumentos->output = buffer;



        return 1;
        }

    }else if (metodo == 1 && f==1){
        
        //inicialização das variáveis
        char caracter = '\0';
        int i = 0;
        size_t tamanho=0; 
        if (argumentos->input==NULL){
        char *buffer = NULL;
        while(caracter != EOF)
        {
            //Lê caracter a caracter do stdin até ler um EOF
            if (scanf("%c", &caracter) < 1){
                printf("\n");
                tamanho++;
                buffer = (char *)realloc(buffer, ((tamanho) * sizeof(char))); 
                argumentos->output=buffer;
                return 1;
                
                }
            tamanho=desencriptar1_filtrado(caracter, senha, &buffer, &tamanho,o);//função de encriptação dos caracteres com filtragem

            
        }

        }else{
            
            char *buffer = NULL;
            size_t j=0;
            while (argumentos->input[j] != '\0') {
                tamanho = desencriptar1_filtrado(argumentos->input[j], senha, &buffer, &tamanho,o);
                i++;
                j++;
                
            }
            buffer[tamanho+1] = '\0';
            tamanho++;
            buffer = (char *)realloc(buffer, tamanho * sizeof(char));
            buffer[tamanho-1]='\n';
            printf("\n");
            argumentos->output=buffer;
            return 1;
        }



    }
    
    if (metodo==2 && f==0)
    {
        //inicialização das variáveis
        
        int senha_len = strlen(senha);
        int x[senha_len];
        int index=0;
        char caracter = '\0'; 
        size_t tamanho=0;
        char *buffer=NULL;
        int i=0;


        if (argumentos->input==NULL){
            
            // Calcula os offsets de todos os caracteres e guarda tudo num vetor de inteiros
            for (int i = 0; i < senha_len; i++) {
                for (int j = 0; j < 67; j++) {
                    if (senha[i] == tabela[j]) {
                        x[i] = j; 
                        
                        break;
                    }
                }
            }
         
            while(caracter != EOF)
            {
                //Lê caracter a caracter do stdin até ler um EOF
                if (scanf("%c", &caracter) < 1){
                    buffer[tamanho+1] = '\0';
                    argumentos->output=buffer;
                    return 1;
                    //exit(EXIT_SUCCESS);
                }
                tamanho++;
                buffer = (char *)realloc(buffer, tamanho * sizeof(char));
                buffer[i]=desencriptar2(caracter,x, senha_len,&index,o);//função de encriptação dos caracteres
                //3printf("\n\n[%d]\n\n",index);
                i++;
            }    

            }else{

                // Calcula os offsets de todos os caracteres e guarda tudo num vetor de inteiros
                    for (int i = 0; i < senha_len; i++) {
                        for (int j = 0; j < 67; j++) {
                            if (senha[i] == tabela[j]) {
                                x[i] = j; 
                                
                                break;
                            }
                        }
                    }

                    
                    
                    int j=0;
                    while(argumentos->input[j] != '\0')
                    {
                        tamanho++;
                        buffer = (char *)realloc(buffer, tamanho * sizeof(char));
                        buffer[i]=desencriptar2(argumentos->input[j],x, senha_len,&index,o);//função de encriptação dos caracteres
                        j++;
                        //3printf("\n\n[%d]\n\n",index);
                        i++;
                    }
                    buffer[tamanho+1] = '\0';
                    argumentos->output=buffer;
                    return 1;    

            }


        
    
    }else if (metodo==2 && f==1)
    {
        //inicialização das variáveis
        
        int senha_len = strlen(senha);
        int x[senha_len];
        int index=0;
        char caracter = '\0'; 
        
        size_t tamanho=0;

        if(argumentos->input==NULL){
            // Calcula os offsets de todos os caracteres e guarda tudo num vetor de inteiros
            for (int i = 0; i < senha_len; i++) {
                for (int j = 0; j < 67; j++) {
                    if (senha[i] == tabela[j]) {
                        x[i] = j; 
                        
                        break;
                    }
                }
            }

            char *buffer=NULL;
            
            
            while(caracter != EOF)
            {
                //Lê caracter a caracter do stdin até ler um EOF
                if (scanf("%c", &caracter) < 1){
                    buffer[tamanho+1] = '\0';
                    
                    argumentos->output=buffer;

                    return 1;
                    
                }
                
                
                tamanho=desencriptar2_filtrado(caracter,x, &buffer,senha_len,&index,&tamanho,o);//função de encriptação dos caracteres com filtragem

                
                
                
            }
        }else{
            


                for (int i = 0; i < senha_len; i++) {
                for (int j = 0; j < 67; j++) {
                    if (senha[i] == tabela[j]) {
                        x[i] = j; 
                        
                        break;
                    }
                }
            }

            char *buffer=NULL;
            int i = 0;

            while(argumentos->input[i] != '\0')
            {
                tamanho=desencriptar2_filtrado(argumentos->input[i],x, &buffer,senha_len,&index,&tamanho,o);//função de encriptação dos caracteres com filtragem
                i++;    
            }
            buffer[tamanho+1] = '\0';
            tamanho++;
            argumentos->output=buffer;
            return 1;




        }
    
    }
    printf("Operação Errada\n");
    exit(EXIT_FAILURE);
    return 0;

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
    // Abre o arquivo para escrita
    FILE *arquivo = fopen(filename, "w+ ");

    // Verifica se houve erro na abertura do arquivo
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", filename);
        return;
    }

    // Escreve a string no arquivo
    fprintf(arquivo, "%s", argumentos->output);

    // Fecha o arquivo
    fclose(arquivo);

}

void lerficheiro(char *filename, Argumentos *argumentos){
   
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", filename);
        exit(EXIT_FAILURE);
    }
    //printf("Ficheiro aberto com sucesso\n");
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

int main(int argc, char *argv[])  { 

    //inicialização das variáveis
    int opt; 
    int operação=-1;
    int metodo=-1;
    int f=0;
    char *senha="Programacao2024";
    char filename[100];
    int teste =0;
    int o=0;
    char filename_out[100];

    Argumentos *argumentos = malloc(sizeof(Argumentos));
    
    
    while ((opt = getopt(argc, argv, "h:s:fc:d:i:o:e")) != -1) {
        switch (opt) {
            case 'h':
                help();//função de ajuda
                exit(EXIT_SUCCESS);
                break;

            case 's':
                //altera a senha original e verifica se é uma senha válida
                senha = optarg;
                isValidCharacter(senha);
                break;

            case 'f':
                //ativa a flag de filtragem
                f = 1;
                
                break;

            case 'c':
                
                if (operação!=-1)//verifica se é a primeira vez q a flag -c ou -d é utilizada
                {
                    printf("Demasiados argumentos linha 750, operação ->%d\n",operação);
                    exit(EXIT_FAILURE);
                }
                
                operação=1;//ativa a flag de encriptação
                metodo=atoi(optarg);//guarda qual a cifra a usar
                
                break;

            case 'd':
                if (operação!=-1)//verifica se é a primeira vez q a flag -c ou -d é utilizada
                {
                    printf("Demasiados argumentos linha 762, operação ->%d\n",operação);
                    exit(EXIT_FAILURE);
                }
                operação=2;//ativa a flag de decriptação
                metodo=atoi(optarg);//guarda qual a cifra a usar
               
                break;
            case 'i':
                strcpy(filename,optarg);
                
                lerficheiro(filename,argumentos);
                break;
            case 'o':
                o=1;//flag para criar ficheiro de output
                strcpy(filename_out,optarg);
                break;
            case 'e':
                if (operação!=-1)//verifica se é a primeira vez q a flag -c ou -d é utilizada
                {
                    printf("Demasiados argumentos aqui\n");
                    exit(EXIT_FAILURE);
                }
                operação=3;
                break;
            default:
                
                help();
                exit(EXIT_FAILURE);
        }
    
    }  
   
    //analiza as flags da operação a utilizar
    if (operação==1){
        
        teste = encriptacao(metodo,f,senha,argumentos,o);
        
    }else if (operação==2){
        teste = decriptacao(metodo,f,senha,argumentos,o);
    }else if (operação==3){
        if (o==0)
        {
            estatisticas(argumentos);/* code */
            free(argumentos->input);
            free(argumentos);
        }else if (o==1)
        {
            estatisticasOut(argumentos,filename_out);
            free(argumentos->input);
            free(argumentos);
            exit(EXIT_SUCCESS);
        }
        
        
        
    }else{
        printf("operação inválida\n");
        exit(EXIT_FAILURE);
    }
    
    if (o==1)
    {
       
        imprimir(filename_out,argumentos);
    }
    
    
    if (teste==1){
    free(argumentos->input);
    free(argumentos->output);
    free(argumentos);
    exit(EXIT_SUCCESS);
    }

    return 0;
}