#ifndef HESTRUTURA_H
#define HESTRUTURA_H
#define TAM 100

typedef struct doente{
    int id;
    char nome[TAM];
    int data_dia, data_mes, data_ano;
    char cc[TAM];
    char tele[TAM];
    char email[TAM];
}doente;

typedef struct registo{
    int dataRegisto_dia, dataRegisto_mes, dataRegisto_ano;
    double tensaoMax, tensaoMin, peso, altura;
}registo;

typedef struct noLista2 {
    struct registo r;
    struct noLista2 *prox;
} noLista2;

typedef struct noLista1 {
    struct doente d;
    struct noLista1 *prox;
    struct noLista2 *registo;
} noLista1;

typedef noLista1* dLista;
typedef noLista2* rLista;

#endif