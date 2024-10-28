#ifndef ARVORE_B_H
#define ARVORE_B_H

#include <stdio.h>
#include <string.h>

#define ORDEM 7

//DESCRIÇÃO: ESTRUTURA DO CABEÇALHO DO ARQUIVO DE DADOS
    typedef struct{
        int posRaiz;//posição da raiz
        int posLivre;//cabeça da lista de posições livre
        int posTopo;//próxima posição livre
    }Cabecalho_Indices;

    //DESCRIÇÃO: ESTRUTURA DO CABEÇALHO DO ARQUIVO DE ÍNDICES
    typedef struct{
        int posLivre;
        int posTopo;
    }Cabecalho_Dados;

    //DESCRIÇÃO: ESTRUTURA CONTENDO AS INFORMAÇÕES DOS PRODUTOS
    typedef struct{
        int codigo;
        char nome[51];
        char marca[31];
        char categoria[51];
        int estoque;
        float preco;

        int next;    
    }Produto;

    //DESCRIÇÃO: ESTRUTURA DA ÁRVORE BINÁRIA
    typedef struct{
        int nChaves;//quantidade de chaves
        int chaves[ORDEM];//chaves 
        int ptDados[ORDEM];//posição dos códigos no arquivo de DADOS
        int filhos[ORDEM+1];//filhos
    }ArvoreB;

    //DESCRIÇÃO: ESTRUTURA AUXILIAR PARA A CHAVE
    typedef struct{
        int codigo;
        int ptDados;
    }Chave_Auxiliar;


//Descricao: Escreve o cabeçalho de índices no arquivo binário.
//Entrada:   Ponteiro para o arquivo binário, ponteiro para o cabeçalho de índices.
//Retorno:   Nenhum.
//Pre-condicao: O arquivo deve estar aberto e ser válido. O ponteiro do cabeçalho não deve ser nulo.
//Pos-condicao: O cabeçalho de índices é escrito no início do arquivo binário.
void escreverCabecalhoIndices(FILE* fb, Cabecalho_Indices* hd);


//Descricao: Le o cabeçalho de índices do arquivo binário.
//Entrada:   Ponteiro para o arquivo binário.
//Retorno:   Ponteiro para o cabeçalho de índices lido do arquivo.
//Pre-condicao: O arquivo deve estar aberto e ser válido.
//Pos-condicao: O ponteiro para o cabeçalho de índices lido é retornado.
Cabecalho_Indices* lerCabecalhoIndices(FILE* fb);


//Descricao: Inicializa a árvore B no arquivo binário.
//Entrada:   Ponteiro para o arquivo binário.
//Retorno:   Nenhum.
//Pre-condicao: O arquivo deve estar aberto e ser válido.
//Pos-condicao: A árvore B é inicializada no arquivo binário.
void initializarArvore(FILE* fb);


//Descricao: Escreve um nó da árvore B no arquivo binário.
//Entrada:   Ponteiro para o arquivo binário, ponteiro para o nó da árvore B, posição do nó no arquivo.
//Retorno:   Nenhum.
//Pre-condicao: O arquivo deve estar aberto e ser válido. O ponteiro para o nó não deve ser nulo.
//Pos-condicao: O nó da árvore B é escrito no arquivo binário na posição especificada.
void escreverArvoreB(FILE* fb, ArvoreB* r, int pos);


//Descricao: Le um nó da árvore B do arquivo binário.
//Entrada:   Ponteiro para o arquivo binário, posição do nó no arquivo.
//Retorno:   Ponteiro para o nó da árvore B lido do arquivo.
//Pre-condicao: O arquivo deve estar aberto e ser válido.
//Pos-condicao: O ponteiro para o nó da árvore B lido é retornado.
ArvoreB* lerArvoreB(FILE* fb, int pos);


//Descricao: Escreve o cabeçalho de dados no arquivo binário.
//Entrada:   Ponteiro para o arquivo binário, ponteiro para o cabeçalho de dados.
//Retorno:   Nenhum.
//Pre-condicao: O arquivo deve estar aberto e ser válido. O ponteiro do cabeçalho não deve ser nulo.
//Pos-condicao: O cabeçalho de dados é escrito no início do arquivo binário.
void escreverCabecalhoDados(FILE* fb, Cabecalho_Dados* hd);


//Descricao: Le o cabeçalho de dados do arquivo binário.
//Entrada:   Ponteiro para o arquivo binário.
//Retorno:   Ponteiro para o cabeçalho de dados lido do arquivo.
//Pre-condicao: O arquivo deve estar aberto e ser válido.
//Pos-condicao: O ponteiro para o cabeçalho de dados lido é retornado.
Cabecalho_Dados* lerCabecalhoDados(FILE* fb);


//Descricao: Inicializa os dados no arquivo binário.
//Entrada:   Ponteiro para o arquivo binário.
//Retorno:   Nenhum.
//Pre-condicao: O arquivo deve estar aberto e ser válido.
//Pos-condicao: Os dados são inicializados no arquivo binário.
void inicilizarDados(FILE* fb);


//Descricao: Escreve um produto no arquivo binário.
//Entrada:   Ponteiro para o arquivo binário, ponteiro para o produto, posição do produto no arquivo.
//Retorno:   Nenhum.
//Pre-condicao: O arquivo deve estar aberto e ser válido. O ponteiro para o produto não deve ser nulo.
//Pos-condicao: O produto é escrito no arquivo binário na posição especificada.
void escreverDados(FILE* fb, Produto* p, int pos);


//Descricao: Le um produto do arquivo binário.
//Entrada:   Ponteiro para o arquivo binário, posição do produto no arquivo.
//Retorno:   Ponteiro para o produto lido do arquivo.
//Pre-condicao: O arquivo deve estar aberto e ser válido.
//Pos-condicao: O ponteiro para o produto lido é retornado.
Produto* lerDados(FILE* fb, int pos);


//Descricao: Insere um nó na árvore B no arquivo binário.
//Entrada:   Ponteiro para o arquivo binário, ponteiro para o nó da árvore B, flag indicando se é raiz.
//Retorno:   Posição do nó no arquivo.
//Pre-condicao: O arquivo deve estar aberto e ser válido. O ponteiro para o nó não deve ser nulo.
//Pos-condicao: O nó é inserido na árvore B no arquivo binário.
int inserirArquivoBinIndices(FILE* fb, ArvoreB* no, int ehRaiz);


//Descricao: Remove um nó da árvore B do arquivo binário.
//Entrada:   Ponteiro para o arquivo binário, posição do nó no arquivo.
//Retorno:   Nenhum.
//Pre-condicao: O arquivo deve estar aberto e ser válido. A posição do nó deve ser válida.
//Pos-condicao: O nó é removido da árvore B no arquivo binário.
void removerArquivoBinIndicies(FILE* fb, int pos);


//Descricao: Insere um produto no arquivo binário.
//Entrada:   Ponteiro para o arquivo binário, ponteiro para o produto.
//Retorno:   Posição do produto no arquivo.
//Pre-condicao: O arquivo deve estar aberto e ser válido. O ponteiro para o produto não deve ser nulo.
//Pos-condicao: O produto é inserido no arquivo binário.
int inserirArquivoBinDados(FILE* fb, Produto* p);


//Descricao: Remove um produto do arquivo binário.
//Entrada:   Ponteiro para o arquivo binário, posição do produto no arquivo.
//Retorno:   Nenhum.
//Pre-condicao: O arquivo deve estar aberto e ser válido. A posição do produto deve ser válida.
//Pos-condicao: O produto é removido do arquivo binário.
void removerArquivoBinDados(FILE* fb, int pos);


#endif