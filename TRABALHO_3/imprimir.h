#ifndef IMPRIMIR_H
#define IMPRIMIR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

    //DESCRICAO:    ESTRUTURA-LISTA DE MODO A AUXILIAR A IMPRESSÃO DOS CÓDIGOS DOS PRODUTOS EM FORMATO DE ÁRVORE BINÁRIA.
    //              A LISTA GUARDA OS CÓDIGOS DOS NÓS DE FORMA ORDENADA COM ALTURA DO NÓ EM RELAÇÃO A RAIZ DA ÁRVORE.
    typedef struct no{
        int codigo;
        int alturaNo;
        int indiceNo;

        struct no* prox;
    }Lista;

    //Descrição: Função para imprimir as informações de um produto a partir de seu código
//Entrada: Ponteiros para os arquivos de índices e dados
//Saida: void
//Pré-condição: Os arquivos de índices e dados devem existir e estar abertos
//Pós-condição: As informações do produto são impressas na tela
void imprimirProduto(FILE* fbIndices, FILE* fbDados);

//Descrição: Função auxiliar para imprimir as informações de um produto a partir de seu código
//Entrada: Ponteiros para os arquivos de índices e dados, e o código do produto
//Saida: void
//Pré-condição: Os arquivos de índices e dados devem existir e estar abertos, o código do produto deve ser válido
//Pós-condição: As informações do produto são impressas na tela
void imprimirProduto_aux (FILE* fbIndices, FILE* fbDados, int chave);

//Descrição: Função para imprimir os produtos em ordem de código
//Entrada: Ponteiros para os arquivos de índices e dados
//Saida: void
//Pré-condição: Os arquivos de índices e dados devem existir e estar abertos
//Pós-condição: Os produtos são impressos em ordem de código na tela
void imprimir_inOrdem(FILE* fbIndices, FILE* fbDados);

//Descrição: Função recursiva para imprimir os produtos em ordem de código
//Entrada: Ponteiros para os arquivos de índices e dados, e a posição atual na árvore
//Saida: void
//Pré-condição: Os arquivos de índices e dados devem existir e estar abertos
//Pós-condição: Os produtos são impressos em ordem de código na tela
void imprimir_inOrder_rec(FILE* fbIndices, FILE* fbDados, int pos);

//Descrição: Função para imprimir a árvore B representando a estrutura de índices
//Entrada: Ponteiro para o arquivo de índices
//Saida: void
//Pré-condição: O arquivo de índices deve existir e estar aberto
//Pós-condição: A árvore B é impressa na tela
void imprimirArvoreB(FILE* fbIndices);

//Descrição: Função recursiva para percorrer a árvore B e montar uma lista ordenada pela altura do nó
//Entrada: Ponteiros para os arquivos de índices e dados, uma lista encadeada, a posição atual na árvore, a altura do nó atual e o índice do nó atual
//Saida: Lista encadeada ordenada pela altura do nó
//Pré-condição: O arquivo de índices deve existir e estar aberto
//Pós-condição: A lista encadeada é montada ordenadamente
Lista* percorrerArvore(FILE* fbIndices, Lista* l, int pos, int alturaNo, int indiceNo);

//Descrição: Função para inserir um código na lista encadeada de forma ordenada pela altura do nó
//Entrada: Uma lista encadeada, o código do produto, a altura do nó e o índice do nó
//Saida: Lista encadeada com o código inserido
//Pré-condição: -
//Pós-condição: O código é inserido na lista ordenadamente
Lista* inserirOrdenado(Lista* l, int codigo, int alturaNo, int indiceNo);

//Descrição: Função para imprimir a lista encadeada de forma a representar a árvore B de índices
//Entrada: Ponteiro para a lista encadeada
//Saida: void
//Pré-condição: -
//Pós-condição: A árvore B é impressa na tela
void imprimirArvore_aux(Lista *l);

//Descrição: Função para liberar a memória alocada pela lista encadeada
//Entrada: Ponteiro para a lista encadeada
//Saida: void
//Pré-condição: -
//Pós-condição: A memória alocada pela lista é liberada
void liberarLista(Lista *l);

//Descrição: Função para imprimir a lista encadeada de nós livres no arquivo de índices
//Entrada: Ponteiro para o arquivo de índices
//Saida: void
//Pré-condição: O arquivo de índices deve existir e estar aberto
//Pós-condição: A lista de nós livres é impressa na tela
void imprimirListaLivre_arqIndices(FILE* fbIndices);

//Descrição: Função recursiva para imprimir a lista encadeada de nós livres no arquivo de índices
//Entrada: Ponteiro para o arquivo de índices e a posição atual
//Saida: void
//Pré-condição: O arquivo de índices deve existir e estar aberto
//Pós-condição: A lista de nós livres é impressa na tela
void imprimirListaLivre_arqIndices_aux(FILE* fbIndices, int pos);

//Descrição: Função para imprimir a lista encadeada de nós livres no arquivo de dados
//Entrada: Ponteiro para o arquivo de dados
//Saida: void
//Pré-condição: O arquivo de dados deve existir e estar aberto
//Pós-condição: A lista de nós livres é impressa na tela
void imprimirListaLivre_arqDados(FILE* fbDados);

//Descrição: Função recursiva para imprimir a lista encadeada de nós livres no arquivo de dados
//Entrada: Ponteiro para o arquivo de dados e a posição atual
//Saida: void
//Pré-condição: O arquivo de dados deve existir e estar aberto
//Pós-condição: A lista de nós livres é impressa na tela
void imprimirListaLivre_arqDados_aux(FILE* fbDados, int pos);
    
#endif