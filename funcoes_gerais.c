/*
 * Programação
 * Trabalho Prático
 * Zoo Vale das Flores
 * Ricardo Jorge Veiga da Silva
 * Aluno nº 21120616
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dados.h"
#include "funcoes_area.h"
#include "funcoes_gerais.h"
#include "funcoes_animais.h"


void inicio(){
    puts("\n Programacao\n Trabalho Pratico\n Zoo Vale das Flores \n Ricardo Jorge Veiga da Silva\n Aluno  21120616\n\n\n\n");
}

int menu(){
    char st[5];
    int i;
    do{
        puts("\n\n\t\t*MENU PRINCIPAL*\n\n");
        puts("Escolha uma opcao...\n");
        puts(" 1 - Gerir areas");
        puts(" 2 - Gerir animais");
        puts(" 3 - Guardar e sair");
        putchar('>');
        scanf("%s", st);  
        i = atoi(st);
        if(i<1 || i > 3)
            puts("\nOPCAO INVALIDA...");
    }while(i<1 || i > 3);
    return i;
}

int menu_areas(){
    char st[5];
    int i;
    do{
        puts("\n\n\t\t*MENU DE GESTAO DE AREAS*\n\n");
        puts("Escolha uma opcao...\n");
        puts(" 1 - Criar nova area");
        puts(" 2 - Eliminar area");
        puts(" 3 - Listar areas");
        puts(" 4 - Voltar ao menu anterior");
        putchar('>');
        scanf("%s", st);  
        i = atoi(st);   
        if(i<1 || i > 4)
            puts("\nOPCAO INVALIDA...");
    }while(i<1 || i > 4);
    return i;
    }

int menu_animais(){
    char st[5];
    int i;
    do{
        puts("\n\n\t\t*MENU DE GESTAO DE ANIMAIS*\n\n");
        puts("Escolha uma opcao...\n");
        puts(" 1 - Criar novo animal");
        puts(" 2 - Eliminar animal ");
        puts(" 3 - Transferir animal ");
        puts(" 4 - Adicionar animais de um ficheiro");
        puts(" 5 - Ver Informacao de animais");
        puts(" 6 - Voltar ao menu anterior");
        putchar('>');
        scanf("%s", st);  
        i = atoi(st);   
        if(i<1 || i > 6)
            puts("\nOPCAO INVALIDA...");
    }while(i<1 || i > 6);
    return i;
    }


int menu_listagem(){
    char st[5];
    int i;
    do{
        puts("\n\n\t\t*MENU DE CONSULTA DE DADOS DE ANIMAIS*\n\n");
        puts("Escolha uma opcao...\n");
        puts(" 1 - Ver animal ");
        puts(" 2 - Ver todos os animais");
        puts(" 3 - Ver animais por area ");
        puts(" 4 - Ver animais por especie ");
        puts(" 5 - Voltar ao menu anterior ");
        putchar('>');
        scanf("%s", st);  
        i = atoi(st);   
        if(i<1 || i > 5)
            puts("\nOPCAO INVALIDA...");
    }while(i<1 || i > 5);
    return i;
    }

int menu_animais_sem_binario(){
    char st[5];
    int i;
    do{
        puts("\n\n\t\t*MENU DE GESTAO DE ANIMAIS*\n\n");
        puts("Escolha uma opcao...\n");
        puts(" 1 - Adicionar animais de um ficheiro");
        puts(" 2 - Voltar ao menu anterior");
        putchar('>');
        scanf("%s", st);  
        i = atoi(st);   
        if(i<1 || i > 2)
            puts("\nOPCAO INVALIDA...");
    }while(i<1 || i > 2);
    return i;
    }