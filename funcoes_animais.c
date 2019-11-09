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


void gera_id(char *id){ //gera um valor aleatório único; 
    time_t t;
    unsigned short int i = time(&t);
    int j;
    FILE *f = fopen("id.txt", "r");
    if(f == NULL)
        j = 1; 
    else if(fscanf(f, "%d", &j) != 1)
        j = 1;
    else
        fclose(f);
    sprintf(id, "%s%hu%d", "an-", i, j++);  
    f = fopen("id.txt", "w");
    fprintf(f, "%d", j);
    fclose(f);
}

void grava_lista_bin(panimais lista){  //recebe um ponteiro para o inicio da lista, guarda cada um dos nós, e no final guarda o número de nós
    FILE *f;
    int conta=0;
    f = fopen("animais.dat", "wb");
    if(f==NULL){
        printf("Erro ao criar ficheiro\n");
        return;
    }
    while(lista != NULL){
        fwrite(lista, sizeof(animais), 1, f);
        lista = lista->prox;
        conta++;
        }
    fwrite(&conta, sizeof(int), 1, f);
    fclose(f);
    }

panimais le_lista_bin(parea p, int total_areas){ // lê do ficheiro o número de nós guardados, de seguida vai introduzí-los no início da lista,
    panimais novo, lista = NULL;                 // lendo os nós do final para o início e inserindo os nós à cabeça da lista matém a organização
    FILE *f;                                     //verifica também as restrições de peso e área
    int i, j, total;
    f = fopen("animais.dat", "rb");
    if(f == NULL)
        return NULL;
    fseek(f, -sizeof(int), SEEK_END);
    fread(&total, sizeof(int), 1, f);
    for(i = total-1; i >= 0; i--){
        fseek(f, sizeof(animais)*i, SEEK_SET);
        novo = malloc(sizeof(animais));
        if(novo == NULL){
            fclose(f);
            return lista;
        }
        fread(novo, sizeof(animais),1, f);
        for(j = 0; j < total_areas; j++)
            if(strcmp(p[j].id, novo->area) == 0 && (p+j)->soma_peso+novo->peso < (p+j)->pesomax){      
                p[j].soma_peso += novo->peso;
                novo->prox = lista;
                lista = novo;
            }
    }
    fclose(f);
    return lista;
}

void mostra_especies(panimais p){ //imprime as espécies presentes no zoo
    puts("\nLista de especies:");
    while(p->prox != NULL){   
        if(strcmp(p->especie, p->prox->especie) != 0)
            printf(" * %s\n",p->especie);  
        p = p->prox; 
    }
    printf(" * %s\n",p->especie);
}

 void le_especie(char *st){
    printf("\nNa lista acima pode encontra as especies presentes no zoo.\nEscreva a especie do animal que pretende:"); 
    scanf( "%s", st);
}

panimais devolve_especie(char *especie, panimais pt){ //procura o indice inicial da especie
    while(pt != NULL){
        if(strcmp(pt->especie, especie) == 0){
                return pt;
        }
        pt = pt->prox;
    }
    return pt;
} 

void lista_pai_especie(panimais spc, char *st){    //lista os animais da especie escolhida do utilizador
    puts("\nLista de animais da especie, disponiveis:");
    while (spc != NULL && strcmp(spc->especie, st) == 0){
            printf("Nome: %s\tID: %s\tArea: %s\n", spc->nome, spc->id, spc->area);
        spc = spc->prox;
    }
}

void le_pai(char *id){
    printf("\nNa lista acima consta a identificacao dos animais disponiveis da especie escolhida.\nCopie o ID do animal que pretende: ");
    getchar();
    scanf("%s", id);        
}

panimais devolve_pai(char *pai, panimais esp){
    while(esp != NULL){
        if(strcmp(esp->id, pai) == 0)
            return esp;
        esp = esp->prox; 
    } 
    return esp;
}

panimais devolve_pai_novo(char *pai, panimais esp, panimais pai_1){
    while(esp != NULL){
        if(strcmp(pai, pai_1->id) == 0){
            printf("\n\nO ANIMAL QUE ESCOLHEU JA' E' O PRIMEIRO PROGENITOR...\n\n");
            return NULL;   
        }
        if(strcmp(pai, esp->id) == 0 && strcmp(esp->area, pai_1->area) == 0)
            return esp;       
        esp = esp->prox; 
    }
    printf("\n\nO ANIMAL QUE ESCOLHEU NAO E' VALIDO...\n\n");
    return esp;
}

void lista_pai_especie_novo(panimais spc, char *st, panimais pai_1, int *conta){ //
    puts("\n\nLista de animais da especie:");
    while (spc != NULL && strcmp(spc->especie, st) == 0){
        if(strcmp(pai_1->id, spc->id) != 0 && strcmp(pai_1->area, spc->area) == 0){
                printf("Nome: %s\tID: %s\tArea: %s\n", spc->nome, spc->id, spc->area);
                (*conta)++;
            }
        spc = spc->prox;
    }
}

panimais le_verifica_especie(panimais lista, char *st){ //Recebe um ponteiro para o início da lista e um ponteiro para string que será preenchida com a espécie escolhida pelo utilizador. São feitas as verificações para o caso de haver erro de utilizador
    panimais espec = NULL;                              //Retorna um ponteiro para o início da espécie na lista de animais
    do{
        mostra_especies(lista);
        le_especie(st);
        espec = devolve_especie(st, lista); 
        if(espec == NULL)
            puts("\nA ESPECIE QUE INTRODUZIU NAO EXISTE NO ZOO...");
    }while(espec == NULL);
    return espec;
}

panimais le_verifica_pai(panimais especie, char *idfdr, char *ste){ //Recebe ponteiro para o início da espécie na lista, ponteiro para a string introduzida pelo utilizador, ponteiro para a string onde está guardada a espécie escolhida anteriormente
    panimais prog = NULL;                                              //Retorna um ponteiro para o animal escolhido
    do{
        lista_pai_especie(especie, ste);
        le_pai(idfdr);   
        prog = devolve_pai(idfdr, especie);
        if(prog == NULL || strcmp(prog->especie, ste) != 0)
            puts("\nO ANIMAL QUE INTRODUZIU NAO E' VALIDO...");
    }while(prog == NULL || strcmp(prog->especie, ste) != 0);
    return prog;
}

int se_novo_prog(){ //Verifica se há um segundo progenitor. Retorna a opção do utilizador.
    int novo_prog;
    char op[5];
    do{
        printf("Quer acrescentar mais um progenitor?\n 1-sim\n 2-nao\n> ");
        scanf("%s", op);
        novo_prog = atoi(op);
        if(novo_prog > 2 || novo_prog < 1)
            puts("\nOPCAO INVALIDA...");
    }while(novo_prog > 2 || novo_prog < 1);
    return novo_prog;
}

panimais le_verifica_novo_prog(panimais especie, char *ste, panimais prgtr, char *idnt, int *opt){//Função idêntica à da verificação do primeiro progenitor, recebe mais um ponteiro para o primeiro progenitor e um ponteiro para a opção do utilizador a ser usado na função de onde vem a chamada.
    panimais prog2 = NULL;                                                                         // Retorna um ponteiro para o segundo progenitor, ou NULL em caso de não ser possível escolher um segundo progenitor.
    int conta = 0;
    char op[5];
    do{
        lista_pai_especie_novo(especie, ste, prgtr, &conta);
        if(conta == 0){
            puts("\nNAO EXISTEM MAIS ANIMAIS DA MESMA ESPECIE NA AREA DO PROGENITOR ESCOLHIDO...\nO animal tera apenas 1 progenitor...\n");
            do{
            puts("Continuar criacao com 1 pogenitor?");
            printf(" 1 - sim\n 2 - nao, sair sem guardar\n>");
            scanf("%s", op);
            *opt = atoi(op);
            if(*opt < 1 || *opt > 2)
                puts("OPCAO INVALIDA...");
            }while(*opt < 1 || *opt > 2);
            if(*opt)
                break;
        }       
    le_pai(idnt);
    prog2 = devolve_pai_novo(idnt, especie, prgtr);
    }while(prog2 == NULL);
    return prog2;
}

void preenche_dados_novo(panimais novo, panimais prog, panimais prog2){
    gera_id(novo->id);
    novo->peso = 0;
    printf("\nIntroduza o nome do novo animal: ");
    getchar();
    fscanf(stdin, "%[^\n]", novo->nome);
    strcpy(novo->area, prog->area);
    strcpy(novo->especie, prog->especie);
    strcpy(novo->id_prog1, prog->id);
    novo->peso = prog->peso * 0.2;
    prog->peso = prog->peso*0.8;
    if(prog2 != NULL){
        novo->peso += (prog2->peso*0.2);
        prog2->peso = prog2->peso*0.8;
        strcpy(novo->id_prog2, prog2->id);
    }

}

panimais gera_animal(panimais lista, parea p){  //recebe ponteiro para lista, ponteiro para área cria animal insere-o na lista retorna lista
    panimais especie = NULL, prog = NULL, prog2 = NULL, novo = NULL;
    int opt = 0, novo_pai;
    char st_esp[30], idf[15];
    puts("\n\n\t\t----------CRIACAO DE ANIMAL-----------\n");
    novo = malloc(sizeof(animais));
    if(novo == NULL){
        printf("Erro na alocacao de memoria\n");
        return lista;
    }
    memset(novo, 0, sizeof(animais));
    especie = le_verifica_especie(lista, st_esp);
    prog = le_verifica_pai(especie, idf, st_esp);  
    printf("\nEscolheu o(a) \'%s\' com o nome \'%s\'\n\n",prog->especie, prog->nome);
    novo_pai = se_novo_prog();
    if(novo_pai == 1) 
        prog2 = le_verifica_novo_prog(especie, st_esp, prog, idf, &opt);
    if(opt == 2)
        return lista;
    preenche_dados_novo(novo, prog, prog2);
    lista = insere_animal_novo(lista, novo);
    puts("\nUm novo animal foi gerado com sucesso!\n");
    printf("\nDados do novo animal:\nEspecie: %s\nNome: %s\nID: %s\nArea: %s\nPai(s): %s",
            novo->especie, novo->nome, novo->id, novo->area, prog->nome);
    if(prog2 != NULL)    
            printf(" e %s", prog2->nome);
    printf("\nPeso: %0.2f", novo->peso);
    return lista;
}

panimais insere_animal_novo(panimais lista, panimais novo){//Recebe um ponteiro para a lista e um ponteiro para o novo animal, insere o novo nó na lista ordenado por especie
    panimais aux = NULL;                                    //Retorna um ponteiro para a lista
    if(lista == NULL || strcmp(novo->especie, lista->especie) == 0){
        novo->prox = lista;
        lista = novo;
    }
    else{
        aux = lista;
        while(aux->prox != NULL && strcmp(novo->especie,aux->prox->especie) != 0)
            aux = aux->prox;
        novo->prox = aux->prox;
        aux->prox = novo;
    }
    return lista;
}

void transfere_animal(parea p, panimais a, int total){ //Recebe como argumentos um ponteiro para o vector de áreas, um ponteiro para a lista de animais e o total de áreas.
    char id[15], spc[30], *ar[3]= {NULL}, i, op[5];     //Após fazer todas as verificações de fronteira e peso, muda a área do animal e troca os pesos
    int x = 0, opt;
    panimais especie = NULL, animal = NULL;
    puts("\n\n\t\t----------TRANSFERENCIA DE ANIMAIS-----------\n");
    especie = le_verifica_especie(a , spc);
    animal = le_verifica_pai(especie, id, spc);
    puts("\nLista de areas disponiveis: ");
    for(i = 0; i < total; i++)
        for(int j = 0; j < 3; j++){
            if(p[i].n_adj == 0 || a->peso + p[i].soma_peso > p[i].pesomax)
                break;
            if(!strcmp(animal->area, (p+i)->adj[j])){                
                ar[x] = (p+i)->id;
                printf(" %d: %s\n",x+1, ar[x]);
                x++;
            }
        }
    if(x == 0){
        puts("\nNAO EXISTEM AREAS DISPONIVEIS PARA TRANSFERIR O ANIMAL...");
        return;
    }
    x = 0;
        do{  
            printf("\nDa lista, copie a area para onde pretende transferir o animal: "); 
            scanf("%s", id);
            for(i = 0; i < 3; i++)
                if(!strcmp(ar[i], id)){
                    x++;
                    break;
                }
            if(x == 0)
                puts("\nA AREA NAO EXISTE OU NAO ESTA DISPONIVEL...\n");
        }while(x == 0);
        printf("Ira' transferir o %s %s para a area %s...\nPretende finalizar transferencia?\n",animal->especie, animal->nome, ar[i]);
        do{ 
            printf(" 1 - sim\n 2 - nao, sair sem guardar\n>");
            scanf("%s", op);
            opt = atoi(op);
        }while(opt < 1 || opt > 2);
        if(opt == 1){
            for(i = 0; i < total; i++)
                if(!strcmp (p[i].id, animal->area))
                    break;
            p[i].soma_peso -= animal->peso;
            for(i = 0; i < total; i++)
                if(!strcmp (id, p[i].id))
                    break;
            strcpy(animal->area, p[i].id);
            p[i].soma_peso += animal->peso;
        }
}
    
panimais le_ficheiro_txt(panimais lista, parea areas, int total){ //Recebe como argumentos um ponteiro para o vector de áreas, um ponteiro para a lista de animais e o total de áreas.
    panimais novo = NULL;                                           //Insere os animais do ficheiro na lista ordenando por especie depois de verificar o peso e a área
    char stf[50], id[15];                                           //Retorna um ponteiro para a lista
    int total_an, conta = 0;
    FILE *f;
    puts("\n\n\t\t----------ADICAO DE ANIMAIS-----------\n");
    printf("\nIndique o nome do ficheiro a ser lido:");
    fscanf(stdin, "%s", stf);
    putchar('\n');
    f = fopen(stf, "r");
    if(f == NULL){
        puts("\nErro na leitura do ficheiro...");
        return lista;
    }    
    fscanf(f, "%d", &total_an);
    for(int i = 0; i < total_an; i++){
        novo = malloc(sizeof(animais));
        memset(novo, 0, sizeof(animais));
        fscanf(f, "%s %s %f %s", novo->nome, novo->especie, &novo->peso, novo->area);
        for(int j = 0; j < total; j++)
            if(strcmp(areas[j].id, novo->area) == 0 && (areas+j)->soma_peso+novo->peso < (areas+j)->pesomax){
                conta++;
                gera_id(id);
                strcpy(novo->id, id);
                (areas+j)->soma_peso += novo->peso;
                printf("%s da especie %s carregado...\n", novo->nome, novo->especie);
                lista = insere_animal_novo(lista, novo);  
            }           
    }
    if(conta < total_an)
        printf("\n%d animais nao foram carregados por incompatibilidade de peso ou de area...\n", total_an-conta);
    fclose(f);
    return lista;
}

void mostra_animais(panimais p){
    puts("Lista completa de animais do zoo:");
    while(p != NULL){
        printf("ID: %s\tNome: %s\tEspecie: %s\tArea: %s\t \tPeso: %.2f\n", p->id, p->nome, p->especie, p->area, p->peso);
        p = p->prox;  
    }
}

panimais elimina_animal(panimais p, parea ar, int total){                     //Recebe um ponteiro para a lista de animais, um ponteiro para o vector de áreas e o valor total de áreas
    panimais atual, anterior = NULL, especie = NULL, animal = NULL, aux2 = NULL;      //Retorna um ponteiro para a lista    
    char spc[30], id[15];
    int op;
    especie = le_verifica_especie(p , spc);
    animal = le_verifica_pai(especie, id, spc);
    printf("O%s da especie %s com o ID %s vai ser eliminado, continuar?\n 1 - sim\n 2 - nao\n>", animal->nome, animal->especie, animal->id);
    do{
    scanf("%s", spc);
    op = atoi(spc);
    }while(op < 1 || op >2); 
    if(op == 1){
        atual = p;
        aux2 = p;
        while(atual != NULL && strcmp(atual->id, id) != 0){
            anterior = atual;
            atual = atual->prox;
        }
        if(anterior == NULL)
            p = atual->prox;
        else
            anterior->prox = atual->prox;
        while(aux2 != NULL){
            if(strcmp(aux2->id_prog1, id) == 0)
                strcpy(aux2->id_prog1, '\0');
            if(strcmp(aux2->id_prog2, id) == 0) 
                strcpy(aux2->id_prog2, '\0');
            aux2=aux2->prox;
            for(int i = 0; i < total; i++)
                if(strcmp(animal->area, (ar+i)->id))
                    (ar+i)->soma_peso -= animal->peso;
        }
        free(atual);
    }    
    return p;
}

void ver_animal(panimais p){ // lista animal específico
    char spc[30], id[15];
    panimais especie = NULL, animal = NULL;
    especie = le_verifica_especie(p , spc);
    animal = le_verifica_pai(especie, id, spc);
    printf("\nDados do %s %s:\n\n", animal->especie, animal->nome);
    printf("ID:  %s\nNome:  %s\nEspecie:  %s\nPeso:  %.2f\nArea:  %s\nFilhos:", animal->id, animal->nome, animal->especie, animal->peso, animal->area);
    while(strcmp(especie->especie, spc) == 0){
        if(especie->id_prog1 != NULL)
            printf("%s\t", especie->id_prog1);
        if(especie->id_prog2 != NULL)
            printf("%s\t", especie->id_prog2);
        especie = especie->prox;
    }      
}

void ve_animal_especie(panimais p){
    panimais especie = NULL;
    char spc[30];
    especie = le_verifica_especie(p , spc);
    puts("Lista de animais da especie %s:");
    while(strcmp(spc, especie->especie) == 0){
        printf("ID: %s\tNome: %s\tEspecie: %s\tPeso: %.2f\tArea: %s",especie->id, especie->nome, especie->especie, especie->peso, especie->area);
        especie = especie->prox;
    }
}

void imprime_areas_animais(parea ptr, int total){ //mostra a lista de áreas presentes no vector com informação se podem ser eliminadas
    int conta = 0;
    putchar('\n');
    for(int i = 0; i < total; i++){       
        if((ptr+i)->soma_peso > 0){
            printf(" %s - A area tem %.2f Kg de %.2f Kg preenchidos\n", (ptr+i)->id, (ptr+i)->soma_peso, (ptr+i)->pesomax);    
        }
        else
            printf(" %s - A area nao contem animais\n", (ptr+i)->id);      
            }
}

void busca_area_animais(panimais p, parea a, int total){ //procura a area onde determinado animal se encontra
    char st_area[15];
    int conta = 0;
    imprime_areas_animais(a, total);
    printf("Escreva o nome da area onde estao os animais que pretende listar: ");
    scanf("%s", st_area);
    while(p != NULL){
        if(strcmp(p->area, st_area) == 0){
            printf("ID: %s\tNome: %s\tEspecie: %s\n", p->id, p->nome, p->especie);
            conta++;
        }
    p = p->prox ;      
    }
    if(conta == 0)
        puts("A AREA QUE INDICOU NAO EXISTE OU NAO TEM ANIMAIS...");  
}

void liberta_lista(panimais p){
    panimais aux;
    while(p != NULL){
    aux = p;
    p = p->prox;
    free(aux);
    }
}