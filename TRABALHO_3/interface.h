#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Descrição: Função para exibir uma mensagem de boas-vindas ao usuário.
//Etrada: -
//Saida: -
//Pré-condição: -
//Pós-condição: -
void welcome();

//Descrição: Função para exibir o menu de opções.
//Etrada: Ponteiro para a variável que irá armazenar a opção escolhida pelo usuário.
//Saida: -
//Pré-condição: -
//Pós-condição: -
void menuDeOpcoes(int *op);

//Descrição: Função para exibir o menu de operações CRUD (Create, Read, Update, Delete) de produtos.
//Etrada: Ponteiro para a variável que irá armazenar a opção escolhida pelo usuário.
//Saida: -
//Pré-condição: -
//Pós-condição: -
void menuCrud(int *op);

//Descrição: Função para exibir o menu de impressão de produtos.
//Etrada: Ponteiro para a variável que irá armazenar a opção escolhida pelo usuário.
//Saida: -
//Pré-condição: -
//Pós-condição: -
void menuImprimir(int *op);

#endif