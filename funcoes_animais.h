/*
 * Programação
 * Trabalho Prático
 * Zoo Vale das Flores
 * Ricardo Jorge Veiga da Silva
 * Aluno nº 21120616
 */


#ifndef FUNCOES_ANIMAIS_H
#define FUNCOES_ANIMAIS_H

void gera_id();
void grava_lista_bin(panimais lista);
panimais le_lista_bin(parea p, int total_areas);
panimais insere_animal(panimais lista, parea pt);
void preenche(panimais novo, parea p);
void mostra_animais(panimais p);
void mostra_especies(panimais p);
void le_especie();
void lista_pai_especie(panimais spc, char *st);
void le_pai(char *id);
panimais devolve_especie(char *especie, panimais pt);
panimais devolve_pai(char *pai, panimais esp);
panimais gera_animal(panimais lista, parea p);
panimais devolve_pai_novo(char *pai, panimais esp, panimais pai_1);
void lista_pai_especie_novo(panimais p, char *st, panimais pai_1, int *cont);
panimais le_verifica_especie(panimais lista, char *st);
panimais le_verifica_pai(panimais espec, char *idfdr, char *ste);
int se_novo_prog();
panimais le_verifica_novo_prog(panimais especie, char *ste, panimais prgtr, char *idnt, int *opt);
parea busca_area(panimais spc, parea area_todas);
void preenche_dados_novo(panimais novo, panimais prog, panimais prog2);
panimais insere_animal_novo(panimais lista, panimais novo);
void transfere_animal(parea p, panimais a, int total);
panimais le_ficheiro_txt(panimais lista, parea areas, int total);
void insere_animal_lista_txt(panimais lista, panimais novo);
panimais elimina_animal(panimais p, parea ar, int total);
void ver_animal(panimais p);
void ve_animal_especie(panimais p);
void imprime_areas_animais(parea ptr, int total);
void busca_area_animais(panimais p, parea a, int total);
void liberta_lista(panimais p);

#endif /* FUNCOES_ANIMAIS_H */

