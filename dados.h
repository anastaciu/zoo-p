/*
 * Programação
 * Trabalho Prático
 * Zoo Vale das Flores
 * Ricardo Jorge Veiga da Silva
 * Aluno nº 21120616
 */


#ifndef DADOS_H
#define DADOS_H

typedef struct area areas, *parea;
typedef struct animal animais, *panimais;

struct area{ //declaraçao da estrutura de áreas
    char id[15];
    float pesomax;
    int n_adj;
    char adj[3][15];
    float soma_peso;
};

struct animal{ //declaraçao da estrutura de animais
    char especie[30];
    char id[15];
    char nome[50];
    float peso;
    char area[15];
    char id_prog1[15];
    char id_prog2[15];
    panimais prox;
};

#endif /* DADOS_H */

