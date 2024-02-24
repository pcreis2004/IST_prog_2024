#include <stdio.h>
#include <string.h>

char tabela[] = "0123456789ABCDEFGHIJKLNMOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz .,;-";

void encriptar(char *texto,int x) {
    int i, j;
    for (i = 0; texto[i] != '\0'; ++i) {
        for (j = 0; j < strlen(tabela); ++j) {
            if (texto[i] == tabela[j]) {
                int novo_indice = (j + x) % strlen(tabela);
                printf("%c", tabela[novo_indice]); // Imprime o caractere correspondente ao novo índice
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
    int v = (29+3)%67;
    printf("[%d]\n",v);
    return 0;
}
