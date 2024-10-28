#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "interface.h"


//Descrição: Função para exibir uma mensagem de boas-vindas ao usuário.
//Etrada: -
//Saida: -
//Pré-condição: -
//Pós-condição: -
void welcome() {
    printf("        _                            __ _   \n");
    printf("  /\\// (_)_ __   ___  ___ _ __ __ _ / _| |_ \n");
    printf(" /    \\| | '_ \\ / _ \\/ __| '__/ _` | |_| __|\n");
    printf("/ /\\/\\ \\ | | | |  __/ (__| | | (_| |  _| |_ \n");
    printf("\\/    \\/_|_| |_|\\___|\\___|_|  \\__,_|_|  \\__|\n");
    printf("                                            \n");
}

//Descrição: Função para exibir o menu de opções.
//Etrada: Ponteiro para a variável que irá armazenar a opção escolhida pelo usuário.
//Saida: -
//Pré-condição: -
//Pós-condição: -
void menuDeOpcoes(int *op){
    printf("\n\n===========Menu de opcoes============\n");
    printf("1 - Manter Produto\n");
    printf("2 - Imprimir\n");    
    printf("3 - Carregar arquivo lote\n");
    printf("4 - Resetar arquivo binario\n");
    printf("0 - Sair\n");
    printf("Digite uma opcao: ");
    scanf("%d%*c",op);
}

//Descrição: Função para exibir o menu de operações CRUD (Create, Read, Update, Delete) de produtos.
//Etrada: Ponteiro para a variável que irá armazenar a opção escolhida pelo usuário.
//Saida: -
//Pré-condição: -
//Pós-condição: -
void menuCrud(int *op){
    printf("\n\n=================Manter Produto===============\n");
    printf("1 - Cadastrar\n");
    printf("2 - Remover\n");    
    printf("3 - Alterar Preco\n");
    printf("4 - Altertar Estoque\n");
    printf("0 - Sair\n");
    printf("Digite uma opcao: ");
    scanf("%d%*c",op);
}

//Descrição: Função para exibir o menu de impressão de produtos.
//Etrada: Ponteiro para a variável que irá armazenar a opção escolhida pelo usuário.
//Saida: -
//Pré-condição: -
//Pós-condição: -
void menuImprimir(int *op){
    printf("\n\n==================Imprimir================\n");
    printf("1 - Produto especifico\n");
    printf("2 - Lista de produtos (In-ordem)\n");
    printf("3 - Arvore B de produtos\n");
    printf("4 - Lista de nos livres (indices)\n");
    printf("5 - Lista de nos livres (dados)\n");
    printf("0 - Sair\n");
    printf("Digite uma opcao: ");
    scanf("%d%*c",op);
}