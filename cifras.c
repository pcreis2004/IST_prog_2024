#include <stdio.h>
#include <string.h>

char tabela[] = "0123456789ABCDEFGHIJKLNMOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz .,;-";

void encriptar(char *texto,int x) {
    int i, j;
    for (i = 0; texto[i] != '\0'; ++i) {

        for (j = 0; j < 67; ++j) {
            if (texto[i] == tabela[j]) {
                int cifrado = (j + x) % 67;
                printf("%c", tabela[cifrado]); // Imprime o caractere correspondente ao novo índice
                break;
            }
        }
        if (j==67)
        {
            texto[i]='\0';
        }
        
    }
    printf("\n");
}

void desencriptar(char *texto,int x) {
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


int main() {
    char texto[100];
    int x;
    printf("Digite o offset: ");
    scanf(" %d",&x);
    getchar(); // Consume o caractere de nova linha deixado pelo scanf()
    printf("Digite uma string para encriptar: ");
    fgets(texto, sizeof(texto), stdin);
    texto[strcspn(texto, "\n")] = '\0'; // Remove a quebra de linha inserida pelo fgets

    printf("Texto encriptado e revertido para letras: ");
    encriptar(texto,x);
    /*int v = (29+3)%67;
    printf("[%d]\n",v);
    int r = (v+67-3)%67;
    printf("[%d]\n",r);*/
    printf("Digite uma string para desencriptar: ");
    char texto_encriptado[100];
    fgets(texto_encriptado, sizeof(texto_encriptado), stdin);
    
    texto_encriptado[strcspn(texto_encriptado, "\n")] = '\0'; // Remove a quebra de linha inserida pelo fgets
    desencriptar(texto_encriptado,x);

    return 0;
}
