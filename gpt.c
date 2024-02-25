#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char tabela[] = "0123456789ABCDEFGHIJKLNMOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz .,;-";

void encriptar2(char texto[], int x, char password[]) {
    int i, j;
    int y = -1; // Initialize y with a value indicating it's not set yet

    // Find the offset corresponding to the first character of the password
    for (int lol = 0; lol < strlen(password); ++lol) {
        if (password[0] == tabela[lol]) {
            y = lol;
            printf("Offset -> %d\n", y); // Print the offset corresponding to the first character of the password
            break;
        }
    }
    printf("[%s]\n", texto);

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

int main() {
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
    int x = 0; // Initialize x with a value (you can change it as per your requirement)

    printf("Digite uma string para encriptar: ");
    fgets(texto, sizeof(texto), stdin);
    texto[strcspn(texto, "\n")] = '\0'; // Remove the newline inserted by fgets

    printf("Texto encriptado e revertido para letras: ");
    encriptar2(texto, x, password);

    free(password);

    return 0;
}
