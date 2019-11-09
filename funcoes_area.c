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


parea cria_vector(int total){ //cria espaço em memoria para conter as areas a ler do ficheiro, retorna ponteiro para espaço de memória
    parea p = malloc(sizeof(areas)*total);
    if(p == NULL){
        puts("Erro na alocação de memória, tente novamente...");
        return p;
    }
    return p; 
}

void escreve_txt(parea a, FILE *f){ // escreve no ficheiro os dados de cada area
fprintf(f, "%s\t%d\t%.2f\t%s\t%s\t%s\n", a->id, a->n_adj ,a->pesomax, a->adj[0], a->adj[1], a->adj[2]);
}

void guarda_areas_txt(parea p, int total){ //escreve todas as areas presentes no vector dinamico num ficheiro de texto
    FILE *f;
    f = fopen("areas.txt", "w");
    if(f == NULL){
        puts("Erro ao abrir o ficheiro...");
        return;
    }
    fprintf(f, "%d\n", total);
    for(int i = 0; i < total; i++)
    escreve_txt(p+i, f);
    fclose(f);
}

int le_tamanho_txt(){ //lê do ficheiro o primeiro valor que representa o mumero de linhas (areas) presentes no mesmo
FILE *f;
int total;
f = fopen("areas.txt", "r");
if(f == NULL){
printf("Erro no acesso ao ficheiro\n");
exit(0);
}
fscanf(f, "%d", &total);
fclose(f);
return total; 
}

void le_areas_txt(parea fich){ //lê do ficheiro para o vector dinâmico todas as dados das areas
    FILE *f;
    int total;
    f = fopen("areas.txt", "r");
    if(f == NULL){
        printf("Erro no acesso ao ficheiro\n");
        return;
    }
    fscanf(f, "%d", &total);
    while(total-- > 0){
        fscanf(f, "%s %d %f %s %s %s", fich->id, &fich->n_adj, &fich->pesomax, fich->adj[0], fich->adj[1], fich->adj[2]);
        fich->soma_peso = 0;
        fich++;
    }
    fclose(f); 
}

void gera_cod_area(int total_areas, parea area){ //pede um nome para a area
    int i;
    do{
        printf("\n\nEscreva o nome da nova area: ");
        scanf("%s", area[total_areas-1].id);        
        for(i = 0; i < total_areas-1; i++)  
            if(strcmp(area[total_areas-1].id, area[i].id) == 0){
                puts("O NOME QUE INTRODUZIU JA EXISTE...\n");
                break;
            }
        }while(i != total_areas-1);
}

void le_peso_max(parea nova, int total){ //pede ao utilizador um peso máximo para a área a criar
    char st[20];
    do{
    printf("\nQual o peso maximo da nova area? ");
    scanf("%s",st);
    nova[total-1].pesomax = atof(st);
    if(nova[total-1].pesomax == 0)
        puts("\nVALOR INVALIDO...");
    }while(nova[total-1].pesomax == 0);
}

parea realoca_memoria(parea velho, int *total){ //acrescenta espaço no vector dinâmico para conter a nova área
    parea novo;
    if(novo == NULL){
        puts("Erro na realocação de memoria, nova area nao foi criada...");
        return novo;
    }
    (*total)++;
    novo = realloc(velho, sizeof(areas)*(*total));
    return novo; 
}

void preenche_nova(parea pt, int tot){ //preenche área por defeito, sem fronteiras
    (pt+tot-1)->n_adj = 0;
    (pt+tot-1)->soma_peso = 0;
    for(int i = 0; i <= 2; i++)
    strcpy((pt+tot-1)->adj[i],"_");
}

int se_adjacente(){ //verifica se o utilizador pretende que a nova área tenha ou não fronteiras
    int adjac;
    char op[5];
    do{
    printf("Esta nova area tem fronteiras?\n 1-sim\n 2-nao\n> ");
    scanf("%s", op);
    adjac = atoi(op);
    if(adjac < 1 || adjac > 2)
        puts("OPCAO INVALIDA...");
    }while(adjac < 1 || adjac > 2);
    return adjac;
}

int verifica_nadjac(parea ptro, int tamanho){ //verifica no vector quantas areas diferentes tem fronteiras disponiveis
    int conta = 0;
    for(int i = 0; i < tamanho-1; i++)
        for(int j = 0; j < 3; j++)
            if(strcmp((ptro+i)->adj[j], "_") == 0){
                conta++;
                break;
            }   
    return conta; 
}

int le_nadjacentes(int disp){ // pede ao utlizador para escolher as areas que pretende usar como fronteira
    int n_adjct;
    char op[5];
    switch(disp){
        case 0 :    printf("Nao existem areas adjacentes disponiveis...\n"); //caso a função anterior verifique que não existem áreas com fronteiras disponíveis retorna 0 
                    return 0;
        case 1 :    printf("Existe apenas uma area adjacente disponivel...\n"); //caso exista apenas uma área com fronteiras disponíveis retorna 1
                    return 1;
        case 2 :    do{
                        printf("Existem apenas 2 areas adjacentes disponiveis...\nQuantas fronteiras pretende que tenha a nova area? "); //caso existam duas áreas com fronteiras disponíveis limita a escolha a um máximo de 2 áreas
                        scanf("%s", op); 
                        n_adjct = atoi(op);
                        if(n_adjct>2 || n_adjct<1)
                            printf("OPCAO INVALIDA... ");
                    }while(n_adjct>2 || n_adjct<1);
                    return n_adjct;      
        default :       
        do{
            printf("Cada area pode ter no maximo 3 fronteiras...\nQuantas fronteiras pretende que tenha a nova area? ");//caso existam 3 ou mais áreas com fronteiras disponíveis limita a escolha a um máximo de 2 áreas
            scanf("%s", op); 
            n_adjct = atoi(op); 
            if(n_adjct>3 || n_adjct<1)
                printf("OPCAO INVALIDA... ");
        }while(n_adjct>3 || n_adjct<1);
        return n_adjct;
    }
}

void imprime_areas(parea ptr, int total){ //mostra a lista de áreas presentes no vector com informação de quantas fronteiras livres possuem
    putchar('\n');
    puts("Lista de areas:\n");
    for(int i = 0; i < (total-1); i++){       
        if((ptr+i)->n_adj<3){
            printf(" %d - %s, Esta area tem %d fronteira(s) livre(s)\n",i+1, (ptr+i)->id, 3-(ptr+i)->n_adj);    
                }
                else
                    printf(" %d - %s, AREA SEM FRONTEIRAS LIVRES\n",i+1, (ptr+i)->id);
            }
}

int escolhe_area(int v_total){ // pede ao utlizador para escolher a área que vão fazer fronteira com a nova área
    int n_area;
    char op_ar[5];
    printf("\nEscolha da lista, uma fronteira para a nova area: ");
    do{
        scanf("%s", op_ar); 
            n_area = atoi(op_ar);
        if(n_area < 1 || n_area > v_total-1)
            printf("\nA AREA QUE ESCOLHEU NAO EXISTE, tente novamente: ");
    }while(n_area < 1 || n_area > v_total-1);  
    return n_area;
}

void cria_adjc(parea adjc, int val_total, int nareas, int *num_adjc, int *inova){ //função que preenche as fronteiras indicadas pelo utilizador no vector dinâmico
    if((adjc+nareas-1)->n_adj<3) 
        for(int i = 0; i <= 2; i++)
            if(strcmp((adjc+nareas-1)->adj[i], "_") == 0){ 
                for(int it = 0; it <= 2; it++)
                    if(strcmp((adjc+val_total-1)->id, (adjc+nareas-1)->adj[it]) == 0){ 
                        printf("\nA area que seleccionou ja e' adjacente, tente novamente...\n\n");
                        return;   
                    }
                strcpy((adjc+nareas-1)->adj[i], (adjc+val_total-1)->id);        
                strcpy((adjc+val_total-1)->adj[(*inova)++], (adjc+nareas-1)->id);
                (adjc+nareas-1)->n_adj++;   
                (adjc+val_total-1)->n_adj++;
                (*num_adjc)--;          
                if(*num_adjc != 0)
                    printf("\nFalta escolher %d fronteira(s)...\n\n", *num_adjc); 
                return;
            }
    puts("\nAREA INDISPONIVEL\nEscolha novamente...");       
}

parea cria_nova_area(parea existente, int *total){ //função que cria efectivamente a área, chamando todas as funções criadas para o efeito, devolve um ponteiro para o início do novo vector dinâmico
    parea nova = NULL;
    int adj, nadjc, num_area, i_nova = 0, ver_disp = 0;
    puts("\n\n\t\t----------CRIACAO DE NOVA AREA-----------\n");
    nova = realoca_memoria(existente, total);
    if(nova == NULL)
        return existente;
    gera_cod_area(*total, nova);
    le_peso_max(nova, *total); 
    preenche_nova(nova, *total);
    adj = se_adjacente();
    ver_disp = verifica_nadjac(nova, *total);
    if(adj == 1){                          
        nadjc = le_nadjacentes(ver_disp);              
            imprime_areas(nova, *total); 
            while(nadjc > 0){ 
            num_area = escolhe_area(*total);
            cria_adjc(nova, *total, num_area, &nadjc, &i_nova);
        }                   
    }
    printf("\nUma nova area com a referencia \"%s\" foi criada com sucesso...\n\n\n", (nova+(*total-1))->id); 
    return nova;
}

parea elimina_area(parea p, int *total){   //caso existam areas vazias permite eliminar areas, reorganiza vector, devolve ponteiro para o novo vector 
    char ar[5];
    int op, opc;
    puts("\n\n\t\t----------ELIMINAR AREA-----------\n");
    puts("\n\nLista de areas:\n");
    if(!imprime_areas_eliminar(p, *total)){
        puts("\nNAO EXISTEM AREAS QUE POSSAM SER ELIMINADAS...\n");
        menu_areas();
    }
    do{
    printf("\n\nDa lista anterior escolha o numero da area a ser eliminada: "); 
    scanf("%s", ar);
    op = atoi(ar);
    if(op < 0 || op > *total || p[op-1].soma_peso > 0)
        puts("\nOPCAO INVALIDA...\nA area nao existe ou tem animais...");
    }while(op < 0 || op > *total || p[op-1].soma_peso > 0);
    do{
    printf("\nA AREA %s VAI SER ELIMINADA, PRETENDE CONTINUAR?\n 1 - sim\n 2 - nao\n>", p[op-1].id);
    scanf("%s", ar);
    opc = atoi(ar);
    if(opc < 1 || opc > 2)
        puts("\nOPCAO INVALIDA");
    }while(opc < 1 || opc > 2);
    if(opc == 1){
        (*total)--; 
        for(int i = 0; i < *total; i++)
            for(int j = 0; j<3; j++)
                if(strcmp(p[op-1].id, p[i].adj[j])== 0){                                     
                    strcpy(p[i].adj[j], "_");
                    p[i].n_adj--;
                }
        p[op-1] = p[*total]; 
        printf("\nA area foi eliminda com sucesso...\n");
        return realloc(p, *total * sizeof(areas)); 
    }
    else{   
        puts("\nA operacao foi cancelada...\n");
        return p;
    }
}

int imprime_areas_eliminar(parea ptr, int total){ //mostra a lista de áreas presentes no vector com informação se podem ser eliminadas
    int conta = 0;
    putchar('\n');
    for(int i = 0; i < total; i++){       
        if((ptr+i)->soma_peso == 0){
            conta++;
            printf(" %d - %s, A area pode ser eliminada, %.2f Kg de %.2f Kg preenchidos\n",i+1, (ptr+i)->id, (ptr+i)->soma_peso, (ptr+i)->pesomax);    
        }
        else
            printf(" %d - %s, A AREA CONTEM ANIMAIS, %.2f Kg de %.2f Kg preenchidos\n",i+1, (ptr+i)->id, (ptr+i)->soma_peso, (ptr+i)->pesomax);
            }
    return conta;
}

