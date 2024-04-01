#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include "lib.h"

char tabela1[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz .,;-";

//função que analisa os argumentos da linha de comando caso seja realizada um operação de encriptação
int encriptacao(int metodo,int f,char *senha,Argumentos* argumentos, int o){

char *buffer=NULL;//declara o buffer a null
    if (metodo==1 && f==0){
        //inicialização das variáveis
        char caracter = 'l';
        int i = 0;
        int tamanho=2;
        if (argumentos->input==NULL){//verifica se existiu ficheiro de entrada

                buffer = (char *)malloc(tamanho*sizeof(char));//aloca um char para o buffer
                if (buffer == NULL) {
                    fprintf(stderr, "Erro de alocação de memória\n");
                    exit(EXIT_FAILURE);
                }
                while(caracter != EOF){//Lê caracter a caracter do stdin até ler um EOF
                
                buffer = (char *)realloc(buffer,tamanho * sizeof(char));//realoca mais um char para o buffer 
                if (scanf("%c", &caracter) < 1){
                    
                    argumentos->output=buffer;//coloca o buffer na estrutura
                    return 1;
                }
                buffer[i]=encriptar1(caracter,senha,o);//função de encriptação dos caracteres
                i++;
                tamanho++;//incrementa o tamanho do buffer
            }

        }else{

            buffer = (char *)malloc(tamanho * sizeof(char)); //aloca um char para o buffer
            if (buffer == NULL) {
            fprintf(stderr, "Erro de alocação de memória\n");
            exit(EXIT_FAILURE);
            }
            while (argumentos->input[i] != '\0') {
                    buffer = (char *)realloc(buffer,tamanho*sizeof(char));//realoca mais um char para o buffer 
                    buffer[i] = encriptar1(argumentos->input[i], senha,o);
                    i++;
                    tamanho++;//incrementa o tamanho do buffer
            }
            
            argumentos->output = buffer;//coloca o buffer na estrutura

            return 1;
        }

    }else if (metodo == 1 && f==1){
        //inicialização das variáveis
        char caracter = '\0';
        size_t tamanho=1; 
        if (argumentos->input==NULL){//verifica se existiu ficheiro de entrada
        
            while(caracter != EOF)
            {
                //Lê caracter a caracter do stdin até ler um EOF
                if (scanf("%c", &caracter) < 1){
                    printf("\n");
                    tamanho++;//incrementa o tamanho do buffer
                    buffer = (char *)realloc(buffer, ((tamanho) * sizeof(char))); //realoca mais um char para o buffer
                    argumentos->output=buffer;//coloca o buffer na estrutura
                    return 1;
                    
                    }
                encriptar1_filtrado(caracter, senha, &buffer, &tamanho,o);//função de encriptação dos caracteres com filtragem            
            }

        }else{
            size_t j=0;
            while (argumentos->input[j] != '\0') {
                encriptar1_filtrado(argumentos->input[j], senha, &buffer, &tamanho,o);//função de encriptação dos caracteres com filtragem  
                j++;  
            }
            buffer[tamanho+1] = '\0';//termina o buffer
            tamanho++;
            buffer = (char *)realloc(buffer, tamanho * sizeof(char));
            buffer[tamanho-1]='\n';
            printf("\n");
            argumentos->output=buffer;//coloca o buffer na estrutura
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
        size_t tamanho=1;
        int i=0;

        if (argumentos->input==NULL){//verifica se existiu ficheiro de entrada   
            // Calcula os offsets de todos os caracteres e guarda tudo num vetor de inteiros
            for (int i = 0; i < senha_len; i++) {
                for (int j = 0; j < 67; j++) {
                    if (senha[i] == tabela1[j]) {
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
                    argumentos->output=buffer;//coloca o buffer na estrutura
                    return 1;
                    //exit(EXIT_SUCCESS);
                }
                tamanho++;
                buffer = (char *)realloc(buffer, tamanho * sizeof(char));//realoca mais um char para o buffer
                buffer[i]=encriptar2(caracter,x, senha_len,&index,o);//função de encriptação dos caracteres
                i++;
            }    

        }else{

               // Calcula os offsets de todos os caracteres e guarda tudo num vetor de inteiros
                for (int i = 0; i < senha_len; i++) {
                    for (int j = 0; j < 67; j++) {
                        if (senha[i] == tabela1[j]) {
                            x[i] = j; 
                            
                            break;
                        }
                    }
                }                
                int j=0;
                while(argumentos->input[j] != '\0')
                {
                    tamanho++;
                    buffer = (char *)realloc(buffer, tamanho * sizeof(char));//realoca mais um char para o buffer
                    buffer[i]=encriptar2(argumentos->input[j],x, senha_len,&index,o);//função de encriptação dos caracteres
                    j++;
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
        size_t tamanho=1;
            if(argumentos->input==NULL){//verifica se existiu ficheiro de entrada   
            // Calcula os offsets de todos os caracteres e guarda tudo num vetor de inteiros
            for (int i = 0; i < senha_len; i++) {
                for (int j = 0; j < 67; j++) {
                    if (senha[i] == tabela1[j]) {
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
                    tamanho++;//incrementa o tamanho do buffer
                    buffer = (char *)realloc(buffer, tamanho * sizeof(char));//realoca mais um char para o buffer
                    buffer[tamanho-1]='\n';
                    printf("\n");
                    argumentos->output=buffer;//coloca os argumentos do buffer

                    return 1;
                    
                }   
                encriptar2_filtrado(caracter,x, &buffer,senha_len,&index,&tamanho,o);//função de encriptação dos caracteres com filtragem
            }
        }else{
            // Calcula os offsets de todos os caracteres e guarda tudo num vetor de inteiros
            for (int i = 0; i < senha_len; i++) {
            for (int j = 0; j < 67; j++) {
                if (senha[i] == tabela1[j]) {
                    x[i] = j; 
                    
                    break;
                }
            }
        }

        
        int i = 0;

        while(argumentos->input[i] != '\0')
        {
            encriptar2_filtrado(argumentos->input[i],x, &buffer,senha_len,&index,&tamanho,o);//função de encriptação dos caracteres com filtragem
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
char *buffer=NULL;
    if (metodo==1 && f==0){

        //inicialização das variáveis
        char caracter = 'l';
        int i = 0;
        int tamanho=2;
        if (argumentos->input==NULL){//verifica se existiu ficheiro de entrada

            buffer = (char *)malloc(tamanho*sizeof(char));
                while(caracter != EOF){//Lê caracter a caracter do stdin até ler um EOF
                
                buffer = (char *)realloc(buffer, tamanho * sizeof(char));
                if (scanf("%c", &caracter) < 1){
                    
                    argumentos->output=buffer;//coloca os arguemtentos na estrutura
                    return 1;
                }
                buffer[i]=desencriptar1(caracter,senha,o);//função de encriptação dos caracteres
                i++;
                tamanho++;
            }

        }else{

        
        buffer = (char *)malloc(tamanho * sizeof(char)); 
        if (buffer == NULL) {
        fprintf(stderr, "Erro de alocação de memória\n");
        exit(EXIT_FAILURE);
        }
        while (argumentos->input[i] != '\0') {
                buffer = (char *)realloc(buffer,tamanho*sizeof(char));//realoca mais um char para o buffer
                buffer[i] = desencriptar1(argumentos->input[i], senha,o);
                i++;
                tamanho++;
        }
        argumentos->output = buffer;//coloca os arguemtentos na estrutura
        return 1;
        }

    }else if (metodo == 1 && f==1){
        
        //inicialização das variáveis
        char caracter = '\0';
        
        size_t tamanho=1; 
        if (argumentos->input==NULL){//verifica se existiu ficheiro de entrada
        while(caracter != EOF)
        {
            //Lê caracter a caracter do stdin até ler um EOF
            if (scanf("%c", &caracter) < 1){
                printf("\n");
                tamanho++;
                buffer = (char *)realloc(buffer, ((tamanho) * sizeof(char))); //realoca mais um char para o buffer
                argumentos->output=buffer;//coloca os arguemtentos na estrutura
                return 1;
                
                }
            desencriptar1_filtrado(caracter, senha, &buffer, &tamanho,o);//função de encriptação dos caracteres com filtragem   
        }

        }else{
            
            size_t j=0;
            while (argumentos->input[j] != '\0') {
                desencriptar1_filtrado(argumentos->input[j], senha, &buffer, &tamanho,o);//função de encriptação dos caracteres com filtragem 
                
                j++;
                
            }
            buffer[tamanho+1] = '\0';//termina o buffer com um caracter nulo
            tamanho++;
            buffer = (char *)realloc(buffer, tamanho * sizeof(char));//realoca mais um char para o buffer
            buffer[tamanho-1]='\n';
            printf("\n");
            argumentos->output=buffer;//coloca os arguemtentos na estrutura
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
        size_t tamanho=1;
        int i=0;

        if (argumentos->input==NULL){//verifica se existiu ficheiro de entrada
            
            // Calcula os offsets de todos os caracteres e guarda tudo num vetor de inteiros
            for (int i = 0; i < senha_len; i++) {
                for (int j = 0; j < 67; j++) {
                    if (senha[i] == tabela1[j]) {
                        x[i] = j; 
                        
                        break;
                    }
                }
            }
         
            while(caracter != EOF)
            {
                //Lê caracter a caracter do stdin até ler um EOF
                if (scanf("%c", &caracter) < 1){
                    buffer[tamanho+1] = '\0';//termina o buffer com um caracter nulo
                    argumentos->output=buffer;//coloca os arguemtentos na estrutura
                    return 1;
                }
                tamanho++;
                buffer = (char *)realloc(buffer, tamanho * sizeof(char)); 
                buffer[i]=desencriptar2(caracter,x, senha_len,&index,o);//função de encriptação dos caracteres
                i++;
            }    

            }else{

                // Calcula os offsets de todos os caracteres e guarda tudo num vetor de inteiros
                    for (int i = 0; i < senha_len; i++) {
                        for (int j = 0; j < 67; j++) {
                            if (senha[i] == tabela1[j]) {
                                x[i] = j; 
                                
                                break;
                            }
                        }
                    }            
                    int j=0;
                    while(argumentos->input[j] != '\0')
                    {
                        tamanho++;
                        buffer = (char *)realloc(buffer, tamanho * sizeof(char));//realoca mais um char para o buffer
                        buffer[i]=desencriptar2(argumentos->input[j],x, senha_len,&index,o);//função de encriptação dos caracteres
                        j++;
                        i++;
                    }
                    buffer[tamanho+1] = '\0';//termina o buffer com um caracter nulo
                    argumentos->output=buffer;//coloca o buffer na estrutura
                    return 1;    
            }
    }else if (metodo==2 && f==1)
    {
        //inicialização das variáveis
        int senha_len = strlen(senha);
        int x[senha_len];
        int index=0;
        char caracter = '\0'; 
        size_t tamanho=1;

        if(argumentos->input==NULL){//verifica se existiu ficheiro de entrada
            // Calcula os offsets de todos os caracteres e guarda tudo num vetor de inteiros
            for (int i = 0; i < senha_len; i++) {
                for (int j = 0; j < 67; j++) {
                    if (senha[i] == tabela1[j]) {
                        x[i] = j; 
                        
                        break;
                    }
                }
            }
            while(caracter != EOF)
            {
                //Lê caracter a caracter do stdin até ler um EOF
                if (scanf("%c", &caracter) < 1){
                    buffer[tamanho+1] = '\0';//termina o buffer com um caracter nulo
                    argumentos->output=buffer;// coloca o buffer na estrutura 

                    return 1;
                    
                }   
                desencriptar2_filtrado(caracter,x, &buffer,senha_len,&index,&tamanho,o);//função de encriptação dos caracteres com filtragem
            }
        }else{
            // Calcula os offsets de todos os caracteres e guarda tudo num vetor de inteiros
                for (int i = 0; i < senha_len; i++) {
                for (int j = 0; j < 67; j++) {
                    if (senha[i] == tabela1[j]) {
                        x[i] = j;           
                        break;
                    }
                }
            }
            int i = 0;
            while(argumentos->input[i] != '\0')
            {
                desencriptar2_filtrado(argumentos->input[i],x, &buffer,senha_len,&index,&tamanho,o);//função de desencriptação dos caracteres com filtragem
                i++;    
            }
            buffer[tamanho+1] = '\0';//termina o buffer com um caracter nulo
            tamanho++;
            argumentos->output=buffer;//coloca o buffer na estrutura
            return 1;
        }
    }
    printf("Operação Errada\n");
    exit(EXIT_FAILURE);
    return 0;
}


int main(int argc, char *argv[])  { 

    //inicialização das variáveis
    int opt; 
    int operação=-1;
    int metodo=-1;
    int f=0;
    char *senha="Programacao2024";//senha predefinida
    char filename[100];
    int teste =0;
    int o=0;
    char filename_out[100];

    Argumentos *argumentos = malloc(sizeof(Argumentos));//inicialização e alocação de memória para a estrutura
    //inicialização dos argumentos da estrutura
    argumentos->input=NULL;
    argumentos->output=NULL;
    argumentos->senha=NULL;
    
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
                //defini o ficheiro de entrada
                strcpy(filename,optarg);
                //função de leitura do ficheiro
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
                //flag de estatísticas
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
        if (o==0)//verifica se é suposto criar um ficheiro de output
        {
            estatisticas(argumentos);
            free(argumentos->input);//liberta a memória alocada
            free(argumentos);
        }else if (o==1)
        {
            estatisticasOut(argumentos,filename_out);
            free(argumentos->input);//liberta a memória alocada
            free(argumentos);
            exit(EXIT_SUCCESS);
        }
   
    }else{
        printf("operação inválida\n");
        exit(EXIT_FAILURE);
    }
    
    if (o==1)//verifica se é suposto criar um ficheiro de output
    {
        imprimir(filename_out,argumentos);//imprime a os resultados no ficheiro de saída
    }
    if (teste==1){//liberta a memória alocada
    free(argumentos->input);
    free(argumentos->output);
    free(argumentos);
    exit(EXIT_SUCCESS);
    }
    return 0;
}