#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>

char tabela[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz .,;-";



void desencriptar1(char caracter, char *password) {
    //printf("[Encriptação]\nCifra de César com a senha: %s\n",password);
    int j;
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
            printf("%c",caracter);
        }
    
    
    
}

void desencriptar1_filtrado(char caracter, char *password) {
    //printf("[Encriptação]\nCifra de César com a senha: %s\n",password);
    int j;
    int y = -1; // Initialize y with a value indicating it's not set yet
    static int count=0;
    
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


                count++;
            if (count == 48) {
                printf("\n");
                count = 0;
            }
                break;
            }
        }
        
    
    
    
}


void encriptar1(char caracter, char *password) {
    //printf("[Encriptação]\nCifra de César com a senha: %s\n",password);
    int j;
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
            printf("%c",caracter);
        }
    
    
    
}


void encriptar1_filtado(char caracter, char *password) {
    static int count = 0;

    // Encontrar o offset correspondente ao primeiro caractere da senha
    int y = 0;
    for (int lol = 0; lol < 67; ++lol) {
        if (password[0] == tabela[lol]) {
            y = lol;
            break;
        }
    }

    // Encriptar o texto
    for (int j = 0; j < 67; ++j) {
        if (caracter == tabela[j]) {
            int cifrado = (j + y) % 67;
            printf("%c", tabela[cifrado]); // Imprimir o caractere correspondente ao novo índice

            count++;

            // Verificar se é hora de imprimir uma nova linha
            if (count == 48) {
                printf("\n");
                count = 0;
            } else if (count % 6 == 0 && count % 48!= 0) {
                printf("_"); // Imprimir sublinhado após cada bloco de 7 caracteres (exceto quando é uma nova linha)
            }

            break;
        }
    }
}

int encriptar2(char caracter, int x[], int senha_len, int index) {
    
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
        printf("%c",caracter);
        index--;
    }
    index++;
    return index;
}


int desencriptar2(char caracter, int x[], int senha_len, int index) {
    
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
        printf("%c",caracter);
        index--;
    }
    index++;
    return index;
}

int encriptar2_filtrado(char caracter, int x[], int senha_len, int index) {
    static int count = 0;
    int cifrado;
    int mn = index % senha_len; // Calcula o índice na senha
    int j;

    // Encripta o caractere usando a cifra de Vigenère
    for (j = 0; j < 67; ++j) {
        if (caracter == tabela[j]) {
            cifrado = (j + x[mn]) % 67;
            printf("%c", tabela[cifrado]); // Imprime o caractere cifrado
            count++;
            
            if (count == 48) {
                printf("\n");
                count = 0;
            } else if (count % 6 == 0 && count % 48!= 0) {
                printf("_"); // Imprimir sublinhado após cada bloco de 7 caracteres (exceto quando é uma nova linha)
            }
            break;
        }
    }

    if (j == 67) {
        
        index--;
    }


    index++;
    return index;
}

int desencriptar2_filtrado(char caracter, int x[], int senha_len, int index) {
    static int count = 0;
    int cifrado;
    int mn = index % senha_len; // Calcula o índice na senha
    int j;

    // Encripta o caractere usando a cifra de Vigenère
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

    if (j == 67) {
        
        index--;
    }


    index++;
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


void encriptacao(int metodo,int f,char *senha){

    if (metodo==1 && f==0){
        char caracter = '\0'; /* inicializar com caractere zero para entrar no ciclo while em baixo */
        //printf("Insert characters: ");
        while(caracter != EOF)
        {
            /* lê caractere e guarda na variável c, validando a leitura */
            if (scanf("%c", &caracter) < 1){
                //printf("\n");
                //printf("Encriptação realizada com sucesso\n");
                exit(EXIT_SUCCESS);
            }
            encriptar1(caracter,senha);

            
        }   
    }else if (metodo == 1 && f==1){
        char caracter = '\0'; /* inicializar com caractere zero para entrar no ciclo while em baixo */
        //printf("Insert characters: ");
        while(caracter != EOF)
        {
            /* lê caractere e guarda na variável c, validando a leitura */
            if (scanf("%c", &caracter) < 1){
                printf("\n");
                //printf("Encriptação realizada com sucesso\n");
                exit(EXIT_SUCCESS);
            }
            encriptar1_filtado(caracter,senha);

            
        }
    }
    
    if (metodo==2 && f==0)
    {
        int aux;  
        int senha_len = strlen(senha);
        int x[senha_len];
        
        // Calcula os offsets para cada caractere da senha
        for (int i = 0; i < senha_len; i++) {
            for (int j = 0; j < 67; j++) {
                if (senha[i] == tabela[j]) {
                    x[i] = j; // Salva o offset para o caractere da senha
                    //printf("Offset -> %d\n", x[i]); // Printa o offset correspondente ao caractere da senha
                    break;
                }
            }
        }

        
        int index=0;
        char caracter = '\0'; /* inicializar com caractere zero para entrar no ciclo while em baixo */
        //printf("Insert characters: ");
        while(caracter != EOF)
        {
            /* lê caractere e guarda na variável c, validando a leitura */
            if (scanf("%c", &caracter) < 1){
                //printf("\n");
                //printf("Encriptação realizada com sucesso\n");
                exit(EXIT_SUCCESS);
            }
            
            
            aux=encriptar2(caracter,x, senha_len,index);
            index = aux;
            
            
        }
    }else if (metodo==2 && f==1)
    {
        int aux;
        char *senha = "Programacao2024"; // Sua senha de exemplo
        int senha_len = strlen(senha);
        int x[senha_len];
        
        // Calcula os offsets para cada caractere da senha
        for (int i = 0; i < senha_len; i++) {
            for (int j = 0; j < 67; j++) {
                if (senha[i] == tabela[j]) {
                    x[i] = j; // Salva o offset para o caractere da senha
                    //printf("Offset -> %d\n", x[i]); // Printa o offset correspondente ao caractere da senha
                    break;
                }
            }
        }

        
        int index=0;
        char caracter = '\0'; /* inicializar com caractere zero para entrar no ciclo while em baixo */
        //printf("Insert characters: ");
        while(caracter != EOF)
        {
            /* lê caractere e guarda na variável c, validando a leitura */
            if (scanf("%c", &caracter) < 1){
                printf("\n");
                //printf("Encriptação realizada com sucesso\n");
                exit(EXIT_SUCCESS);
            }
            
            
            aux=encriptar2_filtrado(caracter,x, senha_len,index);
            index = aux;
            
            
        }

    }
    
    printf("Operação Errada");
    exit(EXIT_FAILURE);

}



void decriptacao(int metodo,int f,char *senha){

    if (metodo==1 && f==0){


        char caracter = '\0'; /* inicializar com caractere zero para entrar no ciclo while em baixo */
        //printf("Insert characters: ");
        while(caracter != EOF)
        {
            /* lê caractere e guarda na variável c, validando a leitura */
            if (scanf("%c", &caracter) < 1){
                //printf("\n");
                //printf("Encriptação realizada com sucesso\n");
                exit(EXIT_SUCCESS);
            }
            desencriptar1(caracter,senha);
    
            
        }



    }else if (metodo == 1 && f==1){
        

        char caracter = '\0'; /* inicializar com caractere zero para entrar no ciclo while em baixo */
        //printf("Insert characters: ");
        while(caracter != EOF)
        {
            /* lê caractere e guarda na variável c, validando a leitura */
            if (scanf("%c", &caracter) < 1){
                //printf("\n");
                //printf("Encriptação realizada com sucesso\n");
                exit(EXIT_SUCCESS);
            }
            desencriptar1_filtrado(caracter,senha);
    
            
        }



    }
    
    if (metodo==2 && f==0)
    {
        
        int aux;
        char *senha = "Programacao2024"; // Sua senha de exemplo
        int senha_len = strlen(senha);
        int x[senha_len];
        
        // Calcula os offsets para cada caractere da senha
        for (int i = 0; i < senha_len; i++) {
            for (int j = 0; j < 67; j++) {
                if (senha[i] == tabela[j]) {
                    x[i] = j; // Salva o offset para o caractere da senha
                    //printf("Offset -> %d\n", x[i]); // Printa o offset correspondente ao caractere da senha
                    break;
                }
            }
        }

        
        int index=0;
        char caracter = '\0'; /* inicializar com caractere zero para entrar no ciclo while em baixo */
        //printf("Insert characters: ");
        while(caracter != EOF)
        {
            /* lê caractere e guarda na variável c, validando a leitura */
            if (scanf("%c", &caracter) < 1){
                //printf("\n");
                //printf("Encriptação realizada com sucesso\n");
                exit(EXIT_SUCCESS);
            }
            
            
            aux=desencriptar2(caracter,x, senha_len,index);
            index = aux;
            
            
        }



    }else if (metodo==2 && f==1)
    {
        


        int aux;
        char *senha = "Programacao2024"; // Sua senha de exemplo
        int senha_len = strlen(senha);
        int x[senha_len];
        
        // Calcula os offsets para cada caractere da senha
        for (int i = 0; i < senha_len; i++) {
            for (int j = 0; j < 67; j++) {
                if (senha[i] == tabela[j]) {
                    x[i] = j; // Salva o offset para o caractere da senha
                    //printf("Offset -> %d\n", x[i]); // Printa o offset correspondente ao caractere da senha
                    break;
                }
            }
        }

        
        int index=0;
        char caracter = '\0'; /* inicializar com caractere zero para entrar no ciclo while em baixo */
        //printf("Insert characters: ");
        while(caracter != EOF)
        {
            /* lê caractere e guarda na variável c, validando a leitura */
            if (scanf("%c", &caracter) < 1){
                printf("\n");
                //printf("Encriptação realizada com sucesso\n");
                exit(EXIT_SUCCESS);
            }
            
            
            aux=desencriptar2_filtrado(caracter,x, senha_len,index);
            index = aux;
            
            
        }


    }
    
    printf("Operação Errada");
    exit(EXIT_FAILURE);

}

int isValidCharacter(char c[]) {
    // Check if the character belongs to the tabela[] array
    for (int j = 0; j < strlen(c); j++)
    {
    
    
    for (int i = 0; i < strlen(tabela); i++) {
        if (c[j] == tabela[i]) {
            return 1; // Character is valid
        }
    }
     return 0;
    }
    return 0;// Character is not valid
}

int main(int argc, char *argv[])  { 
    int opt; 
    int operação=0;
    int metodo=0;
    
    
    int f=0;
    char *senha="Programacao2024";
    
    
    while ((opt = getopt(argc, argv, "h:s:fc:d:")) != -1) {
        switch (opt) {
            case 'h':
                help();
                exit(EXIT_SUCCESS);
                break;

            case 's':
                senha = optarg;
                if (isValidCharacter(senha)==0)
                {
                    printf("ERRO TECLADO\n");
                    exit(EXIT_FAILURE);
                }
                printf("%s",senha);
                
                
                
                break;

            case 'f':
                //printf("comando -> f\n");
                f = 1;
                
                break;

            case 'c':
                //printf("comando -> c\n");
                operação=1;
                metodo=atoi(optarg);
                
                break;

            case 'd':
                operação=2;
                metodo=atoi(optarg);
               
                break;

            default:
                help();
                exit(EXIT_FAILURE);
        }
    
    }  
   

    if (operação==1)
    {
        encriptacao(metodo,f,senha);
    }else if (operação==2)
    {
        decriptacao(metodo,f,senha);
    }else{
        printf("operação inválida\n");
        exit(EXIT_FAILURE);
    }
    
    




    return 0;
}
