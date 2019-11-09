/*
 * Programação
 * Trabalho Prático
 * Zoo Vale das Flores
 * Ricardo Jorge Veiga da Silva
 * Aluno nº 21120616
 */


#ifndef FUNCOES_AREA_H
#define FUNCOES_AREA_H

parea cria_vector(int tam);
parea realoca_memoria(parea velho, int *total);
parea cria_nova_area(parea existente, int *total);
void escreve_txt(parea a, FILE *f);
void le_areas_txt(parea y);
void guarda_areas_txt(parea p, int total);
void le_peso_max(parea nova, int total);
void gera_cod_area(int total_areas, parea area);
void preenche_nova(parea pt, int tot);
void imprime_areas(parea ptr, int total);
void cria_adjc(parea adjc, int val_total, int nareas, int *num_adjc, int *inova);
int escolhe_area(int v_total);
int verifica_nadjac(parea ptro, int tamanho);
int le_tamanho_txt();
int se_adjacente();
int le_nadjacentes(int disp);
parea elimina_area(parea p, int *total);
int imprime_areas_eliminar(parea ptr, int total);

#endif /* FUNCOES_AREA_H */

