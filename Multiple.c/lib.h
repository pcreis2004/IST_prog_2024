#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>

typedef struct Argumentos {//estrutura para guardar os dados necessários para o funcionamento do programa
    char *input;
    char *output;
    char *senha;
} Argumentos;

extern char tabela[];

int desencriptar1(char caracter, char *password, int o);//Função de desencriptação com o método de césar
void desencriptar1_filtrado(char caracter, char *password, char **buffer,size_t *tamanho,int o);//Função de desencriptação com o método de césar e filtragem
int encriptar1(char caracter, char *password,int o);//Função de encriptação com o método de césar   
void encriptar1_filtrado(char caracter, char *password, char **buffer, size_t *tamanho,int o);//Função de encriptação com o método de césar e filtragem
char encriptar2(char caracter, int x[], int senha_len, int *index, int o);//Função de encriptação com o método de vigenére
char desencriptar2(char caracter, int x[], int senha_len, int *index,int o);//Função de desencriptação com o método de vigenére
void encriptar2_filtrado(char caracter, int x[], char **buffer,int senha_len, int *index, size_t *tamanho, int o);//Função de encriptação com o método de vigenére e filtragem
void desencriptar2_filtrado(char caracter, int x[], char **buffer,int senha_len, int *index, size_t *tamanho, int o);//Função de desencriptação com o método de vigenére e filtragem
void help();//Função de ajuda
void estatisticas(Argumentos *argumentos);//Função de cálculos de estatísticas em stdout
void estatisticasOut(Argumentos *argumentos,char filename[]);//Função de cálculos de estatísticas num ficheiro de saída
void isValidCharacter(char *senha);//Função que verifica se a senha é válida
void imprimir(char *filename,Argumentos *argumentos);//Função para imprimir os resultados das encriptações/decriptações num ficheiro de saída
void lerficheiro(char *filename, Argumentos *argumentos);//Função para ler ficheiro de entrada




#endif 
