#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>

char tabela[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz .,;-";

void desencriptar1(char caracter, char *password) {
    
    //incialização das variaveis
    int j;
    int y = -1; 
    
    
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
            
            printf("%c", tabela[cifrado]); // imprime o caracter desencriptado
            break;        
        }
    }
    //imprime o caracter não cifrado cajo não pertença à tabela
    if (j == 67) {
        printf("%c",caracter);
    }
    
    
    
}

void desencriptar1_filtrado(char caracter, char *password) {
    
    //incialização das variaveis
    int j;
    int y = -1; 
    static int count=0;
    
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
            
            printf("%c", tabela[cifrado]); // imprime o caracter desencriptado
            count++;

        if (count == 48) { //muda de linha caso já tenham sido impressos 48 caracteres na linha
            printf("\n");
            count = 0;
        }
            break;
        }

    }
        
    
    
    
}

void encriptar1(char caracter, char *password) {
    
    //incialização das variaveis
    int j;
    int y = -1; 

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
            printf("%c", tabela[cifrado]); // imprime o caracter cifrado
            break;
        }
    }
    //imprime o caracter não cifrado cajo não pertença à tabela
    if (j == 67) {
        printf("%c",caracter);
    }
    
    
    
}

void encriptar1_filtado(char caracter, char *password) {
    
    //incialização das variaveis
    static int count = 0;

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

            count++;

            // verifica se é preciso mudar de linha
            if (count == 48) {
                printf("\n");
                count = 0;
            } else if (count % 6 == 0 && count % 48!= 0) { // Imprime um '_' a cada 7 caracteres, a não ser que seja altura de mudar de linha
                printf("_"); 
            }

            break;
        }
    }
}

int encriptar2(char caracter, int x[], int senha_len, int index) {
    //inicialização das variáveis
    int cifrado;
    int mn = index % senha_len; // calculo do índice da senha
    int j;
    

    for (j = 0; j < 67; ++j) {
        if (caracter == tabela[j]) {
            cifrado = (j + x[mn]) % 67;
            printf("%c", tabela[cifrado]); // Imprime o caractere cifrado
            break;
        }
    }

    //imprime o caracter não cifrado cajo não pertença à tabela
    if (j == 67) {
        printf("%c",caracter);
        
    }
    //aumenta o índice só se o caracter pertencer à tabela
    if(j!=67){
      index++;  
    }
    
    return index;
}


int desencriptar2(char caracter, int x[], int senha_len, int index) {
    //inicialização das variáveis
    int cifrado;
    int mn = index % senha_len; // calculo do índice da senha
    int j;

    
    for (j = 0; j < 67; ++j) {
        if (caracter == tabela[j]) {
            cifrado = (j + 67 - x[mn]) % 67;
            printf("%c", tabela[cifrado]); // Imprime o caractere cifrado
            break;
        }
    }

    //imprime o caracter não cifrado cajo não pertença à tabela
    if (j == 67) {
        printf("%c",caracter);
        
    }
    //aumenta o índice só se o caracter pertencer à tabela
    if(j!=67){
      index++;  
    }
    
    return index;
}

int encriptar2_filtrado(char caracter, int x[], int senha_len, int index) {
    //inicialização das variáveis
    static int count = 0;
    int cifrado;
    int mn = index % senha_len; // calculo do índice da senha
    int j;

   
    for (j = 0; j < 67; ++j) {
        if (caracter == tabela[j]) {
           
            cifrado = (j + x[mn]) % 67;
            printf("%c", tabela[cifrado]); // Imprime o caractere cifrado
            count++;
            
            if (count == 48) {
                printf("\n");
                count = 0;
            } else if (count % 6 == 0 && count % 48!= 0) {
                printf("_"); // Imprime um '_' a cada 7 caracteres, a não ser que seja altura de mudar de linha
            }
            break;
        }
    }
    //aumenta o índice só se o caracter pertencer à tabela
    if(j!=67){
      index++;  
    }
    return index;
}

int desencriptar2_filtrado(char caracter, int x[], int senha_len, int index) {
    //inicialização das variáveis
    static int count = 0;
    int cifrado;
    int mn = index % senha_len; // calculo do índice da senha
    int j;

    
    for (j = 0; j < 67; ++j) {
        if (caracter == tabela[j]) {
            
            cifrado = (j + 67 - x[mn]) % 67;
            printf("%c", tabela[cifrado]); // Imprime o caractere cifrado
            count++;
            if (count == 48) {
                printf("\n");
                count = 0;
            }
            
            
            
            break;
        }
    }
    //aumenta o índice só se o caracter pertencer à tabela
    if(j!=67){
      index++;  
    }
    return index;
}

void help(){
    printf("Escolha a opção que pretende utilizar:\n");
    printf("-h ajuda para o utilizador\n");
    printf("-s senha a usar para cifrar/decifrar\n");
    printf("-f filtração do ficheiro de entrada e formatação do ficheiro de saída\n");
    printf("-c nn operação de cifra do método a escolher\n");
    printf("-d nn operação de decifra do método a escolher\n");
}

void encriptacao(int metodo,int f,char *senha){//função que analisa os argumentos da linha de comando caso seja realizada um operação de encriptação

    if (metodo==1 && f==0){
        //inicialização das variáveis
        char caracter = '\0'; 
        
        while(caracter != EOF)
        {
            //Lê caracter a caracter do stdin até ler um EOF
            if (scanf("%c", &caracter) < 1){
                
                
                exit(EXIT_SUCCESS);
            }
            encriptar1(caracter,senha);//função de encriptação dos caracteres

            
        }   
    }else if (metodo == 1 && f==1){
        //inicialização das variáveis
        char caracter = '\0'; 
        
        while(caracter != EOF)
        {
            //Lê caracter a caracter do stdin até ler um EOF
            if (scanf("%c", &caracter) < 1){
                printf("\n");
                
                exit(EXIT_SUCCESS);
            }
            encriptar1_filtado(caracter,senha);//função de encriptação dos caracteres com filtragem

            
        }
    }
    
    if (metodo==2 && f==0)
    {
        //inicialização das variáveis
        int aux;  
        int senha_len = strlen(senha);
        int x[senha_len];
        int index=0;
        char caracter = '\0'; 

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
                
                
                exit(EXIT_SUCCESS);
            }
            
            
            aux=encriptar2(caracter,x, senha_len,index);//função de encriptação dos caracteres
            index = aux;
            
            
        }
    }else if (metodo==2 && f==1)
    {
        //inicialização das variaveis
        int aux;
        int senha_len = strlen(senha);
        int x[senha_len];
        int index=0;
        char caracter = '\0'; 

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
                printf("\n");
                
                exit(EXIT_SUCCESS);
            }
            
            
            aux=encriptar2_filtrado(caracter,x, senha_len,index);//função de encriptação dos caracteres com filtragem

            index = aux;
            
            
        }

    }
    
    printf("Operação Errada\n");
    exit(EXIT_FAILURE);

}

void decriptacao(int metodo,int f,char *senha){

    if (metodo==1 && f==0){

        //inicialização das variáveis

        char caracter = '\0'; 
        
        while(caracter != EOF)
        {
            //Lê caracter a caracter do stdin até ler um EOF
            if (scanf("%c", &caracter) < 1){
                
                
                exit(EXIT_SUCCESS);
            }
            desencriptar1(caracter,senha);//função de decriptação dos caracteres
    
            
        }



    }else if (metodo == 1 && f==1){
        
        //inicialização das variáveis
        char caracter = '\0'; 
        
        while(caracter != EOF)
        {
            //Lê caracter a caracter do stdin até ler um EOF
            if (scanf("%c", &caracter) < 1){
                printf("\n");
                
                exit(EXIT_SUCCESS);
            }
            desencriptar1_filtrado(caracter,senha);//função de decriptação dos caracteres com filtragem
    
            
        }



    }
    
    if (metodo==2 && f==0)
    {
        //inicialização das variáveis
        int aux;
        int senha_len = strlen(senha);
        int x[senha_len];
        int index=0;
        char caracter = '\0'; 
        
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
                
                
                exit(EXIT_SUCCESS);
            }
            
            
            aux=desencriptar2(caracter,x, senha_len,index);//função de decriptação dos caracteres
            index = aux;
            
            
        }



    }else if (metodo==2 && f==1)
    {
        //inicialização das variáveis
        int aux;
        int senha_len = strlen(senha);
        int x[senha_len];
        int index=0;
        char caracter = '\0'; 
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
                printf("\n");
                
                exit(EXIT_SUCCESS);
            }
            
            
            aux=desencriptar2_filtrado(caracter,x, senha_len,index);//função de decriptação dos caracteres com filtragem
            index = aux;
            
            
        }


    }
    
    printf("Operação Errada\n");
    exit(EXIT_FAILURE);

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

int main(int argc, char *argv[])  { 
    //inicialização das variáveis
    int opt; 
    int operação=-1;
    int metodo=-1;
    int f=0;
    char *senha="Programacao2024";

    if (argc>6)//verifica se não foram usados argumentos em demasia
    {
        printf("Demasiados argumentos\n");
        exit(EXIT_FAILURE);
    }
    
    
    
    
    
    while ((opt = getopt(argc, argv, "h:s:fc:d:")) != -1) {
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
                    printf("Demasiados argumentos\n");
                    exit(EXIT_FAILURE);
                }
                
                operação=1;//ativa a flag de encriptação
                metodo=atoi(optarg);//guarda qual a cifra a usar
                
                break;

            case 'd':
                if (operação!=-1)//verifica se é a primeira vez q a flag -c ou -d é utilizada
                {
                    printf("Demasiados argumentos\n");
                    exit(EXIT_FAILURE);
                }
                operação=2;//ativa a flag de decriptação
                metodo=atoi(optarg);//guarda qual a cifra a usar
               
                break;

            default:
                help();
                exit(EXIT_FAILURE);
        }
    
    }  
   
    //analiza as flags da operação a utilizar
    if (operação==1){
        encriptacao(metodo,f,senha);
    }else if (operação==2){
        decriptacao(metodo,f,senha);
    }else{
        printf("operação inválida\n");
        exit(EXIT_FAILURE);
    }
    
    




    return 0;
}