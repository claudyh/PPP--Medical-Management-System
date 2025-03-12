#ifndef HFUNCOES_H
#define HFUNCOES_H
#include "Estrutura.h"
#define TAM 100


//Funções verificação ---
int containsOnlyDigits(const char *str);
void getInt(char buffer[TAM], const char *str);
void getDouble(char buffer[TAM], double *dado, const char *str);
void getID(int *id, dLista lista_doentes, int unique);

int containsOnlyLetters(const char *str);
int containsOnlyDigitsOrLetters(const char *str);
void removeExtraSpaces(char *str);
int containsEmailStruct(const char *str);
void getString(char buffer[TAM], char dado[TAM], const char *str, int limit);
void getDate(int *dia, int *mes, int *ano);


//Funções listas ---
dLista cria_lista_doentes();
void elimina_doente(dLista lista_doentes, int id);

void insere_doente(dLista lista_doentes, doente novo);
void procura_doente(dLista lista_doentes, char nome[TAM], dLista *ant, dLista *actual);
void insere_registo(dLista lista_doentes, int idDoente, registo novo_registo);
void procura_registo(rLista lista_registos, double tensaoMax, rLista *ant, rLista *atual);

dLista pesquisa_id(dLista lista_doentes, int id);
void info_doente(dLista lista_doentes, int idDoente);
void listar_doentes(dLista lista_doentes);
void listar_tensoes(dLista lista_doentes, int limite);

int dlista_vazia(dLista lista_doentes);
int rlista_vazia(rLista lista_registos);
dLista destroi_lista_doentes(dLista lista_doentes);
rLista destroi_lista_registos(rLista lista_registos);


//Funções ficheiros ---
void ler_ficheiro_doentes(dLista lista_doentes);
void ler_ficheiro_registos(dLista lista_doentes);
void escrever_ficheiro_doentes(doente d);
void escrever_ficheiro_registos(registo r, int idDoente);

#endif