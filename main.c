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


int main(){
    int op1, op2, op3, op4, total_areas;   
    parea vector_areas = NULL;
    panimais lista = NULL;
    total_areas = le_tamanho_txt();
    vector_areas = cria_vector(total_areas);
    le_areas_txt(vector_areas);
    lista = le_lista_bin(vector_areas, total_areas);    
    inicio();
    if(lista == NULL)
        puts("\nO FICHEIRO DE ANIMAIS NAO FOI CARREGADO, NESTE MOMENTO NAO EXISTEM ANIMAIS NO ZOO..."
                "\nPARA TER ACESSO A TODAS AS OPCOES DO MENU DE GESTAO DE ANIMAIS, ADICIONE ANIMAIS A PARTIR DE UM FICHEIRO, NO MENU \'GERIR ANIMAIS\'...");
    do{
        op1 = menu();
        switch(op1){
            case 1: do{
                        op2 = menu_areas();
                        switch(op2){
                            case 1: vector_areas = cria_nova_area(vector_areas, &total_areas); break;                 
                            case 2: vector_areas = elimina_area(vector_areas, &total_areas); break;
                            case 3: imprime_areas_animais(vector_areas, total_areas);
                        }        
                    }while(op2 != 4);break;
            case 2: if(lista == NULL){
                        do{
                            op3 = menu_animais_sem_binario();
                            switch(op3)
                                case 1: lista = le_ficheiro_txt(lista, vector_areas, total_areas); break;                                                     
                        }while(op3 != 2);
                    }
                    else
                        do{
                            op3 = menu_animais();
                            switch(op3){
                                case 1: lista = gera_animal(lista, vector_areas); break;
                                case 2: lista = elimina_animal(lista, vector_areas, total_areas); break;
                                case 3: transfere_animal(vector_areas, lista, total_areas); break;
                                case 4: lista = le_ficheiro_txt(lista, vector_areas, total_areas); break;
                                case 5: do{
                                            op4 = menu_listagem(); 
                                            switch(op4){
                                                case 1: ver_animal(lista); break;                 
                                                case 2: mostra_animais(lista); break;
                                                case 3: busca_area_animais(lista, vector_areas, total_areas); break;                 
                                                case 4: ve_animal_especie(lista); break;
                                            }        
                                        }while(op4 != 5);
                            }
                        }while(op3 != 6);
        }
    }while(op1 != 3); 
    guarda_areas_txt(vector_areas, total_areas);
    free(vector_areas); 
    grava_lista_bin(lista);
    liberta_lista(lista);
    return (EXIT_SUCCESS); 
}

