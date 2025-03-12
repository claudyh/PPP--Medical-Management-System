//PPP Project - functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Estrutura.h"
#include "Funcoes.h"
#define TAM 100


//FUNÇÕES---------------------------------------------------------------------------------------------------------------

//Funções de verificação: --------------------------------
int containsOnlyDigits(const char *str) {
    char *newline = strchr(str, '\n');
    if (newline != NULL) { *newline = '\0'; }

    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }

    return 1;
}

void getInt(char buffer[TAM], const char *str) {
    
    while(1){
        printf("|%s: ", str);
        fgets(buffer, TAM, stdin);
        
        if (containsOnlyDigits(buffer)) {
            break;
        } else{
            printf("%s invalido. Por favor, insira um valor numerico inteiro, sem espacos.\n\n", str);
        }
    }
}

void getDouble(char buffer[TAM], double *dado, const char *str) {

    while(1){
        printf("|%s: ", str);
        fgets(buffer, TAM, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        //Verificar valor
        char *endptr;
        *dado = strtod(buffer, &endptr);

        if (*endptr == '\0' && endptr != buffer) {
            break;
        } else {
            printf("Valor de %s invalido.\nPor favor, insira um valor double (com um ponto a separar), sem espacos.\n", str);
        }
    }
}

void getID(int *id, dLista lista_doentes, int unique) {
    char buffer[TAM];

    //Obter ID
    getInt(buffer, "ID");
    *id = atoi(buffer);

    if(unique){
        //Verificar se é único
        if (pesquisa_id(lista_doentes, *id) != NULL) {
            *id = -1;
            printf("\nID invalido. Por favor, insira um ID unico.\n---------------------------\n\n");
        }
    } else{
        //Verificar se existe
        if (pesquisa_id(lista_doentes, *id) == NULL) {
            *id = -1;
            printf("\nID invalido. Por favor, insira um ID existente.\n---------------------------\n\n");
        }
    }
}


int containsOnlyLetters(const char *str) {
    char *newline = strchr(str, '\n');
    if (newline != NULL) { *newline = '\0'; }

    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i]) && str[i] != ' ') {
            return 0;
        }
    }

    return 1;
}

int containsOnlyDigitsOrLetters(const char *str) {
    char *newline = strchr(str, '\n');
    if (newline != NULL) { *newline = '\0'; }

    if (str == NULL) {
        return 0;
    }

    while (*str) {
        if (!isalnum((unsigned char)*str)) {
            return 0;
        }
        str++;
    }

    return 1;
}

void removeExtraSpaces(char *str) {

    //Substituir tabs por espaços
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\t' || str[i] == '\r') {
            str[i] = ' ';
        }
    }

    //Tirar espaços a mais
    char *array[TAM];
    int count = 0;
    char temp[TAM];
    strcpy(temp, str);

    char *token = strtok(temp, " ");
    while (token != NULL) {
        array[count++] = token;
        token = strtok(NULL, " ");
    }

    strcpy(str, "");
    for (int i = 0; i < count; i++) {
        strcat(str, array[i]);
        if (i < count - 1) {
            strcat(str, " ");
        }
    }
}

int containsEmailStruct(const char *str) {
    char *newline = strchr(str, '\n');
    if (newline != NULL) { *newline = '\0'; }

    char *ptr1, *ptr2;
    ptr1 = strchr(str, '@');

    if (ptr1 == NULL) {
        return 0;
    } else {
        int i;
        for (i = 0; str[i] != '@'; i++) {
            if (!isalpha(str[i]) && !isdigit(str[i]) && str[i] != '-' && str[i] != '.') {
                return 0;
            }
        }

        if(i == 0){ return 0; } //no body

        ptr2 = strchr(str, '.');
        
        if (ptr2 == NULL) {
            return 0;
        } else {
            int tam= i+1;
            for (i= i+1; str[i] != '.'; i++) {
                if (!isalpha(str[i])) {
                    return 0;
                }
            }

            if(i == tam){ return 0; } //no domain

            tam= i+1;
            for (i= i+1; str[i] != '\0'; i++) {
                if (!isalpha(str[i])) {
                    return 0;
                }
            }

            if(i == tam){ return 0; } //no final
        }
    }

    return 1;
}

void getString(char buffer[TAM], char dado[TAM], const char *str, int limit) {

    while(1){
        printf("|%s: ", str);
        fgets(buffer, TAM, stdin);

        if(strcmp(str, "Nome") == 0){
            removeExtraSpaces(buffer);
            
            if (containsOnlyLetters(buffer)) {
                strcpy(dado, buffer);
                break;
            } else { printf("Nome invalido. Por favor, insira apenas letras.\n"); }

        } else if(strcmp(str, "Email") == 0){
            if (containsEmailStruct(buffer)) {
                strcpy(dado, buffer);
                break;
            } else { printf("Email invalido. Por favor, insira no formato \"example@domain.com\", sem espacos.\n"); }

        } else if(strcmp(str, "Cartao cidadao") == 0){
            
            //Split por "-"
            char *array[TAM];
            int count = 0;
            
            char *initial;
            strcpy(initial, buffer);

            char *token = strtok(buffer, "-");
            while (token != NULL) {
                array[count++] = token;
                token = strtok(NULL, "-");
            }

            if(count != 3){
                printf("CC invalido. Por favor, insira no formato 00000000-0-XX0.\n");
            } else{
                //Checar valores
                int valid=1;

                for (int i = 0; i < count; i++) {
                    if (i == 0) {
                        int counter= 0;
                        while(array[i][counter] != '\0'){ counter++; }

                        if (!containsOnlyDigits(array[i]) || (counter != limit)) {
                            valid=0;
                            printf("CC invalido. Por favor, insira no formato 00000000-0-XX0.\n");
                            break;
                        }
                    } else if (i == 1) {
                        int counter= 0;
                        while(array[i][counter] != '\0'){ counter++; }

                        if (!containsOnlyDigits(array[i]) || (counter != 1)) {
                            valid=0;
                            printf("CC invalido. Por favor, insira no formato 00000000-0-XX0.\n");
                            break;
                        }
                    } else if (i == 2) {
                        int counter= 0;
                        while(array[i][counter] != '\0'){ counter++; }

                        if (containsOnlyDigitsOrLetters(array[i]) == 0 || (counter-1 != 3)) {
                            valid=0;
                            printf("CC invalido. Por favor, insira no formato 00000000-0-XX0.\n");
                            break;
                        }
                    }
                }

                //store cc
                if(valid){
                    strcpy(dado, initial);
                    break;
                }
            }  
        } else {
            int count= 0;
            while(buffer[count] != '\0'){ count++; }
            
            if (containsOnlyDigits(buffer) && (count-1 == limit)) {
                strcpy(dado, buffer);
                break;
            } else {
                printf("%s invalido. Por favor, insira um número de tamanho %d, sem espacos.\n", str, limit);
            }
        }
    }
}

void getDate(int *dia, int *mes, int *ano){
    char buffer[TAM];
    int invalid = 1;

    while(invalid){
        printf("|Data (DD/MM/AAAA): ");
        fgets(buffer, TAM, stdin);
        char *newline = strchr(buffer, '\n');
        if (newline != NULL) { *newline = '\0'; }

        //Split por "/"
        char *array[TAM];
        int count = 0;
        
        char *token = strtok(buffer, "/");
        while (token != NULL) {
            array[count++] = token;
            token = strtok(NULL, "/");
        }

        if(count != 3){
            printf("Data invalida. Por favor, insira no formato correto.\n");
        } else{
            //Checar valores
            for (int i = 0; i < count; i++) {
                if (containsOnlyDigits(array[i])) {
                    //Checar numeros
                    int num = atoi(array[i]);

                    if (i == 0) {
                        if (num > 0 && num <= 31) {
                            *dia = num;
                        } else {
                            printf("Dia invalido. Por favor, insira um valor entre 1 e 31.\n");
                            break;
                        }
                    } else if (i == 1) {
                        if ((num > 0 && num <= 12)) {
                            if((*dia == 31 && (num == 2 || num == 4 || num == 6 || num == 9 || num == 11)) ||
                            (*dia == 30 && (num == 1 || num == 2 || num == 3 || num == 5 || num == 7 || num == 8 || num == 10 || num == 12))){
                                printf("Data invalida. Por favor, insira um dia existente no mês.\n");
                                break;
                            } else{
                                *mes = num;
                            }
                        } else {
                            printf("Mes invalido. Por favor, insira um valor entre 1 e 12.\n");
                            break;
                        }
                    } else if (i == 2) {
                        if (num >= 1900 && num < 3000) {
                            *ano = num;
                            invalid = 0;
                        } else {
                            printf("Ano invalido. Por favor, insira um valor entre 1900 e 2024.\n");
                            break;
                        }
                    }
                } else{
                    printf("Data invalida. Por favor, insira no formato correto.\n");
                    break;
                }
            }
        }
    }
} //divisivel 4 e nao por 100 ou divisivel por 400


//Funções listas: ----------------------------------------
dLista cria_lista_doentes() {
    dLista aux = (dLista)malloc(sizeof(noLista1));
    if (aux != NULL) {
        aux->d.id = -1;
        aux->prox = NULL;
        aux->registo = NULL;
    }
    return aux;
}

void elimina_doente(dLista lista_doentes, int idDoente) { //Elimina doente
    dLista ant = lista_doentes;
    dLista atual = lista_doentes->prox;

    while (atual != NULL && atual->d.id != idDoente) {
        ant = atual;
        atual = atual->prox;
    }

    if (atual != NULL) {
        rLista reg_atual = atual->registo;
        while (reg_atual != NULL) {
            rLista temp = reg_atual;
            reg_atual = reg_atual->prox;
            free(temp);
        }

        //Remover doente
        ant->prox = atual->prox;
        free(atual);
        printf("\nDoente eliminado!\n");
    } else {
        printf("\nID do doente invalido!\n");
    }
}


void insere_doente(dLista lista_doentes, doente novo) { //insere doentes
    dLista no = (dLista)malloc(sizeof(noLista1));
    if (no != NULL) {
        no->d = novo;
        dLista ant, inutil;
        procura_doente(lista_doentes, novo.nome, &ant, &inutil);
        no->prox = ant->prox;
        ant->prox = no;
        no->registo = NULL;
    }
}

void procura_doente(dLista lista_doentes, char nome[TAM], dLista *ant, dLista *actual) { //doentes ordem alfabetica
    *ant = lista_doentes; *actual = lista_doentes->prox;
    while ((*actual) != NULL && strcmp((*actual)-> d.nome, nome) < 0){
        *ant = *actual;
        *actual = (*actual)->prox;
    }
    if ((*actual) != NULL && strcmp((*actual)-> d.nome, nome) > 0)
        *actual = NULL;
}

void insere_registo(dLista lista_doentes, int idDoente, registo novo_registo) { // insere registo
    dLista paciente = pesquisa_id(lista_doentes, idDoente);
    if (paciente == NULL) {
        printf("Paciente com ID %d nao encontrado.\n", idDoente);
        return;
    }

    rLista novo_no = (rLista)malloc(sizeof(noLista2));
    if (novo_no == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }
    novo_no->r = novo_registo;
    novo_no->prox = NULL;

    if (paciente->registo == NULL) {
        paciente->registo = novo_no;
    } else {
        rLista ant = NULL, atual = paciente->registo;
        procura_registo(atual, novo_registo.tensaoMax, &ant, &atual);
        novo_no->prox = atual;
        if (ant == NULL) {
            paciente->registo = novo_no;
        } else {
            ant->prox = novo_no;
        }
    }
}

void procura_registo(rLista lista_registos, double tensaoMax, rLista *ant, rLista *atual) { // registo por tensaoMax (decrescente)
    *ant = NULL;
    *atual = lista_registos;
    while (*atual != NULL && (*atual)->r.tensaoMax > tensaoMax) {
        *ant = *atual;
        *atual = (*atual)->prox;
    }
}


dLista pesquisa_id(dLista lista_doentes, int id) { //pesquisa doente por id
    dLista aux = lista_doentes->prox;
    while (aux != NULL) {
        if (aux->d.id == id) {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

void info_doente(dLista lista_doentes, int idDoente) { //informacao e registo do doente
    dLista paciente = pesquisa_id(lista_doentes, idDoente);
    if (paciente == NULL) {
        printf("\nID do doente invalido!\n");
        return;
    }

    printf("Nome: %s\n", paciente->d.nome);
    printf("Data: %d/%d/%d\n", paciente->d.data_dia, paciente->d.data_mes, paciente->d.data_ano);
    printf("CC: %s\n", paciente->d.cc);
    printf("Telemovel: %s\n", paciente->d.tele);
    printf("Email: %s\n", paciente->d.email);

    printf("\nRegistos:\n");
    rLista atual = paciente->registo;
    if (atual == NULL) {
        printf("Nenhum registo encontrado.\n");
    } else {
        while (atual != NULL) {
            printf("Data: %d/%d/%d\n", atual->r.dataRegisto_dia, atual->r.dataRegisto_mes, atual->r.dataRegisto_ano);
            printf("Tensao Max: %.2f\n", atual->r.tensaoMax);
            printf("Tensao Min: %.2f\n", atual->r.tensaoMin);
            printf("Peso: %.2f\n", atual->r.peso);
            printf("Altura: %.2f\n", atual->r.altura);
            printf("---------------------------\n");
            atual = atual->prox;
        }
    }
}

void listar_doentes(dLista lista_doentes) { //listar doentes ordem alfabetica
    dLista aux = lista_doentes->prox;
    if(aux == NULL){
        printf("Nao existem doentes.\n");
    } else{
        while (aux!=NULL){
            printf("Nome: %s (ID: %d)\n", aux->d.nome, aux->d.id);
            aux = aux->prox;
        }
    }
}

void listar_tensoes(dLista lista_doentes, int limite) {  //listar tensoes acima limite (decrescente)
    dLista atual_doente = lista_doentes->prox;
    int doente_atual;

    while (atual_doente != NULL) {
        printf("\n");
        doente_atual=1;

        rLista atual_registo = atual_doente->registo;
        while (atual_registo != NULL) {
            if (atual_registo->r.tensaoMax <= limite) {
                break;
            }

            if( doente_atual ){ printf("Nome: %s (ID: %d)\n", atual_doente->d.nome, atual_doente->d.id); }
            doente_atual=0;
            printf("Tensao Max: %.2f\n", atual_registo->r.tensaoMax);
            atual_registo = atual_registo->prox;
        }

        atual_doente = atual_doente->prox;
    }
}


int dlista_vazia(dLista lista_doentes) {
    return (lista_doentes->prox == NULL);
}

int rlista_vazia(rLista lista_registos) {
    return (lista_registos == NULL);
}

dLista destroi_lista_doentes(dLista lista_doentes) {
    dLista temp_ptr_doente;

    //Percorrer lista doentes
    while (!dlista_vazia(lista_doentes)) {
        temp_ptr_doente = lista_doentes->prox;
        lista_doentes->prox = temp_ptr_doente->prox;
        
        //Destruir lista de registos desse doente
        temp_ptr_doente->registo = destroi_lista_registos(temp_ptr_doente->registo);

        //limpar doente
        free(temp_ptr_doente);
    }
    free(lista_doentes);
    return NULL;
}

rLista destroi_lista_registos(rLista lista_registos) {
    rLista temp_ptr;

    //Percorrer lista registos
    while (!rlista_vazia(lista_registos)) {
        temp_ptr = lista_registos;
        lista_registos = lista_registos->prox;
        
        //limpar registo
        free(temp_ptr);
    }
    return NULL;
}


//Funções ficheiros: -------------------------------------
// Por informações existentes nos ficheiros para as listas:
void ler_ficheiro_doentes(dLista lista_doentes) {
    FILE *f = fopen("./doentes.txt", "r");

    if (f == NULL){
        printf("Erro ao abrir ficheiro Doentes.txt .\n");
        exit(1);
    }

    char *espaco;
    char linha[TAM];
    doente introduzido;

    while (!feof(f)){

        if (fgets(linha, TAM, f) != NULL){
            espaco = strtok(linha, "\n");
            introduzido.id = atoi(espaco);
        }
        if (fgets(linha, TAM, f) != NULL){
            espaco = strtok(linha, "\n");
            strcpy(introduzido.nome, espaco);
        }
        if (fgets(linha, TAM, f) != NULL){
            espaco = linha;
            char *tokens[3];
            int token_count = 0;
            char *token_start = linha;
            while (*espaco != '\0'){
                if (*espaco == '/'){
                    *espaco = '\0';
                    tokens[token_count++] = token_start;
                    token_start = espaco + 1;
                }
                espaco++;
            }
            tokens[token_count++] = token_start;
            introduzido.data_dia = atoi(tokens[0]);
            introduzido.data_mes = atoi(tokens[1]);
            introduzido.data_ano = atoi(tokens[2]);
        }

        if (fgets(linha, TAM, f) != NULL){
            strcpy(introduzido.cc, linha);
        }
        if (fgets(linha, TAM, f) != NULL){
            strcpy(introduzido.tele, linha);
        }
        if (fgets(linha, TAM, f) != NULL){
            strcpy(introduzido.email, linha);
        }

        insere_doente(lista_doentes, introduzido);
    }

    fclose(f);
}

void ler_ficheiro_registos(dLista lista_doentes) { // registos
    FILE *i = fopen("./registos.txt", "r");

    if (i == NULL){
        printf("Erro ao abrir o ficheiro Registos.txt .\n");
        exit(1);
    }

    char *espaco;
    char linha[TAM];
    registo introduzida;
    int idnovo;

    while (!feof(i)){
        if (fgets(linha, TAM, i) != NULL){
            idnovo = atoi(linha);
        }
        if (fgets(linha, TAM, i) != NULL){
            espaco = linha;
            char *tokens[3];
            int token_count = 0;
            char *token_start = linha;
            while (*espaco != '\0'){
                if (*espaco == '/'){
                    *espaco = '\0';
                    tokens[token_count++] = token_start;
                    token_start = espaco + 1;
                }
                espaco++;
            }
            tokens[token_count++] = token_start;
            introduzida.dataRegisto_dia = atoi(tokens[0]);
            introduzida.dataRegisto_mes = atoi(tokens[1]);
            introduzida.dataRegisto_ano = atoi(tokens[2]);
        }
        if (fgets(linha, TAM, i) != NULL){
            espaco = strtok(linha, "\n");
            introduzida.tensaoMax = atoi(espaco);
        }
        if (fgets(linha, TAM, i) != NULL){
            espaco = strtok(linha, "\n");
            introduzida.tensaoMin = atoi(espaco);
        }
        if (fgets(linha, TAM, i) != NULL){
            espaco = strtok(linha, "\n");
            introduzida.peso = atoi(espaco);
        }
        if (fgets(linha, TAM, i) != NULL){
            espaco = strtok(linha, "\n");
            introduzida.altura = atoi(espaco);
        }

        insere_registo(lista_doentes, idnovo, introduzida);
    }

    fclose(i);
}

// Por informações existentes nas listas para os ficheiros:
void escrever_ficheiro_doentes(doente d) { // doentes
    FILE *f = fopen("./doentes.txt", "a");

    if (f == NULL){
        printf("Erro.\n");
        exit(1);
    }
    
    //adicionar proteção caso d seja null
    fprintf(f, "%d\n", d.id);
    fprintf(f, "%s\n", d.nome);
    fprintf(f, "%d/%d/%d\n", d.data_dia, d.data_mes, d.data_ano);
    fprintf(f, "%s", d.cc);
    fprintf(f, "%s\n", d.tele);
    fprintf(f, "%s\n", d.email);

    fclose(f);
}

void escrever_ficheiro_registos(registo r, int idDoente) { //registos
    FILE *i = fopen("./registos.txt", "a");
   
    if (i == NULL) {
        printf("Erro.\n");
        exit(1);
    }

    //add protection in case of r is null
    fprintf(i, "%d\n", idDoente);
    fprintf(i, "%d/%d/%d\n", r.dataRegisto_dia, r.dataRegisto_mes, r.dataRegisto_ano);
    fprintf(i, "%.0f\n", r.tensaoMax);
    fprintf(i, "%.0f\n", r.tensaoMin);
    fprintf(i, "%.0f\n", r.peso);
    fprintf(i, "%.0f\n", r.altura);

    fclose(i);
}

//----------------------------------------------------------------------------------------------------------------------