//PPP Project - main
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Estrutura.h"
#include "Funcoes.h"
#define TAM 100


int main(){

    //Criar lista de doentes:
    dLista lista_doentes= cria_lista_doentes();

    //Inserir informações dos ficheiros:
    ler_ficheiro_doentes(lista_doentes);
    ler_ficheiro_registos(lista_doentes);

    //Menu:
    int opcao=0;
    char buffer[TAM];
    printf("\n--------------------------------HEALTH MANAGER"
           "-----------------------------------\nBem vindo :)\n");

    while(opcao!=7){
        
        //Menu principal:
        printf("\n................ MENU ................\n"
               "\n1- Introduzir novo doente;\n"
               "2- Eliminar doente existente;\n"
               "3- Informação do doente;\n"
               "4- Listar doentes (ordem alfabetica);\n"
               "5- Listagem por tensões acima de um\nvalor (ordem decrescente);\n"
               "6- Fazer um novo registo de um doente;\n"
               "7- Sair.\n"
               "......................................\n"
               "\nQue acao pretende realizar? ");
        
        //Verificar input
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {

              //Ver se é um número
              if (containsOnlyDigits(buffer)) {
                     //Converter para inteiro
                     opcao = atoi(buffer);

                     //Ver se está no range certo
                     if (opcao < 1 || opcao > 7) {
                            opcao= 0;
                            printf("Opcao invalida. Por favor, insira um valor entre 1 e 7, sem espacos.\n");
                     }
              } else {
                     printf("Opcao invalida. Por favor, insira um valor entre 1 e 7, sem espacos.\n");
              }
        }

        //Opções
        switch (opcao){
              case 1:
                     printf("\n\n---------------------------\n"
                     "1 - Introduzir novo doente\n\n");
                     //debug: doente d= {1, "Ana", 1, 1, 2000, "11111111", "111111111", "ana@mail.com"};
                        
                     //Obter dados
                     doente d;
                     getID(&d.id, lista_doentes, 1);
                     //Verificar se é único
                     if(d.id == -1){ break; }
                     getString(buffer, d.nome, "Nome", 0);
                     getDate(&d.data_dia, &d.data_mes, &d.data_ano);
                     getString(buffer, d.cc, "Cartao cidadao", 8);
                     getString(buffer, d.tele, "Telefone", 9);
                     getString(buffer, d.email, "Email", 0);

                     //Inserir novo doente
                     insere_doente(lista_doentes, d);
                     //Dar update ficheiro doentes
                     escrever_ficheiro_doentes(d);
                     printf("\nNovo doente adicionado!\n"
                     "---------------------------\n\n");
                     break;
              case 2:
                     printf("\n\n---------------------------\n"
                     "2 - Eliminar um doente\n\n");

                     //Obter ID
                     getInt(buffer, "ID");
                     int id1 = atoi(buffer);

                     //Eliminar
                     elimina_doente(lista_doentes, id1);
                     //Dar update ficheiro doentes
                     //eliminar_doente_ficheiro(id1);
                     printf("---------------------------\n\n");
                     break;
              case 3:
                     printf("\n\n---------------------------\n"
                     "3 - Informação do doente\n\n");

                     //Obter ID
                     getInt(buffer, "ID");
                     int id2 = atoi(buffer);

                     //Imprimir informação
                     info_doente(lista_doentes, id2);
                     printf("---------------------------\n\n");
                     break;
              case 4:
                     printf("\n\n---------------------------\n"
                     "4 - Listagem de doentes\n\n");

                     //Listar doentes
                     listar_doentes(lista_doentes);
                     printf("---------------------------\n\n");
                     break;
              case 5:
                     printf("\n\n---------------------------\n"
                     "5 - Listagem de tensões acima de um limite\n\n");
                     
                     //Obter Limite
                     getInt(buffer, "Limite");
                     int limite = atoi(buffer);

                     //Listar tensoes
                     listar_tensoes(lista_doentes, limite);
                     printf("---------------------------\n\n");
                     break;
              case 6:
                     printf("\n\n---------------------------\n"
                     "6 - Inserir novo registo\n\n");
                     //debug: registo r1= {1, 1, 2001, 200, 0, 0, 0};
                     //debug: registo r2= {1, 1, 2000, 300, 0, 0, 0};
                        
                     //Obter dados
                     registo r;
                     int idRegisto;
                     getID(&idRegisto, lista_doentes, 0);
                     //Verificar se existe
                     if(idRegisto == -1){ break; }
                     getDate(&r.dataRegisto_dia, &r.dataRegisto_mes, &r.dataRegisto_ano);
                     getDouble(buffer, &r.tensaoMax, "Tensao max");
                     getDouble(buffer, &r.tensaoMin, "Tensao min");
                     getDouble(buffer, &r.peso, "Peso");
                     getDouble(buffer, &r.altura, "Altura");

                     //Inserir novo registo
                     insere_registo(lista_doentes, idRegisto, r);
                     //Dar update ficheiro registos
                     escrever_ficheiro_registos(r, idRegisto);
                     printf("---------------------------\n\n");
                     break;
              default:
                     //Sair
                     break;
        }
    }
    printf("\nAte breve :)\n"
           "---------------------------------------------------------------------------------\n");

    //Libertar memória:
    destroi_lista_doentes(lista_doentes);

    return 0;
}