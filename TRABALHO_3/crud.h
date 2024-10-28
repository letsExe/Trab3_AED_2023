#ifndef CRUD_H
#define CRUD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arvore_b.h"


//Descricao: Inicializa um nó da árvore B.
//Entrada: Ponteiro para o nó da árvore B.
//Retorno: O nó da árvore B inicializado.
//Pre-condicao: -
//Pos-condicao: O nó da árvore B é inicializado com suas variáveis devidamente alocadas e valores padrão.
ArvoreB* inicializarNo(ArvoreB* no);

//Descricao: Realiza a busca por uma chave em um nó da árvore B.
//Entrada: Arquivo de índices, posição do nó, ponteiro para a posição da chave, chave a ser buscada.
//Retorno: 1 se a chave é encontrada, 0 caso contrário.
//Pre-condicao: O arquivo de índices deve estar aberto e o nó deve ser válido.
//Pos-condicao: -
int buscaIndiceChave (FILE* fbIndices, int posNo, int* indiceChave, int chave);

//Descricao: Realiza a busca por uma chave em um nó da árvore B e retorna a posição do nó.
//Entrada: Arquivo de índices, posição do nó, ponteiro para a posição da chave, chave a ser buscada.
//Retorno: A posição do nó.
//Pre-condicao: O arquivo de índices deve estar aberto e o nó deve ser válido.
//Pos-condicao: -
int buscarNo (FILE* fbIndices, int pos,  int* indiceChave, int chave);

//Descricao: Realiza o cadastro de um novo produto.
//Entrada: Arquivo de índices, arquivo de dados.
//Retorno: -
//Pre-condicao: Os arquivos de índices e de dados devem estar abertos.
//Pos-condicao: O produto é cadastrado com sucesso ou uma mensagem de erro é exibida.
void cadastrarProduto(FILE* fbIndices, FILE* fbDados);

//Descricao: Lê o valor de um produto no formato 00,00.
//Entrada: -
//Retorno: O valor do produto.
//Pre-condicao: -
//Pos-condicao: -
float lerValorProduto();


//Descricao: Verifica se um nó da árvore B é folha.
//Entrada: Arquivo de índices, posição do nó.
//Retorno: 1 se o nó é folha, 0 caso contrário.
//Pre-condicao: O arquivo de índices deve estar aberto e o nó deve ser válido.
//Pos-condicao: -
int ehFolha_pos(FILE* fbIndices, int posNo);

//Descricao: Verifica se um nó da árvore B é folha.
//Entrada: Nó da árvore B.
//Retorno: 1 se o nó é folha, 0 caso contrário.
//Pre-condicao: O nó deve ser válido.
//Pos-condicao: -
int ehFolha_no(ArvoreB* no);


//Descricao: Verifica se um nó da árvore B está em overflow.
//Entrada: Arquivo de índices, posição do nó.
//Retorno: 1 se o nó está em overflow, 0 caso contrário.
//Pre-condicao: O arquivo de índices deve estar aberto e o nó deve ser válido.
//Pos-condicao: -
int overflow_pos(FILE* fbIndices, int posNo);

//Descricao: Verifica se ocorreu underflow em um nó da árvore B.
//Entrada: Ponteiro para o arquivo binário de índices, posição do nó no arquivo.
//Retorno: TRUE se ocorreu underflow, FALSE caso contrário.
//Pre-condicao: O arquivo de índices deve estar aberto e ser válido. A posição do nó deve ser válida.
//Pos-condicao: Nenhuma (não altera o estado do arquivo).
int underflow_pos(FILE* fbIndices, int posNo);

//Descricao: Verifica se um nó da árvore B está em overflow.
//Entrada: Nó da árvore B.
//Retorno: 1 se o nó está em overflow, 0 caso contrário.
//Pre-condicao: O nó deve ser válido.
//Pos-condicao: -
int overflow_no(ArvoreB* no);


//Descricao: Adiciona um elemento à direita de um nó da árvore B.
//Entrada: Arquivo de índices, posição do nó, posição do novo elemento, posição do filho, chave auxiliar.
//Retorno: -
//Pre-condicao: O arquivo de índices deve estar aberto e as posições devem ser válidas.
//Pos-condicao: O elemento é adicionado à direita do nó.
void adicionarADireita (FILE* fbIndices, int posNo, int posNovo, int posFilho, int codigo, int ptDados);

//Descricao: Verifica se ocorreu underflow em um nó da árvore B.
//Entrada: Ponteiro para o arquivo binário de índices, posição do nó no arquivo.
//Retorno: TRUE se ocorreu underflow, FALSE caso contrário.
//Pre-condicao: O arquivo de índices deve estar aberto e ser válido. A posição do nó deve ser válida.
//Pos-condicao: Nenhuma (não altera o estado do arquivo).
int underflow_pos(FILE* fbIndices, int posNo);

//Descricao: Insere uma chave auxiliar na árvore B.
//Entrada: Ponteiro para o arquivo binário de índices, ponteiro para o arquivo binário de dados, chave auxiliar a ser inserida.
//Retorno: Nenhum.
//Pre-condicao: Os arquivos de índices e de dados devem estar abertos e serem válidos. A chave auxiliar deve ser válida.
//Pos-condicao: A chave auxiliar é inserida na árvore B.
void inserirNo (FILE* fbIndices, FILE* fbDados, Chave_Auxiliar chaveAux);

//Descricao: Insere uma chave auxiliar em um nó não folha da árvore B.
//Entrada: Ponteiro para o arquivo binário de índices, ponteiro para o arquivo binário de dados, posição do nó no arquivo de índices, chave auxiliar a ser inserida.
//Retorno: Nenhum.
//Pre-condicao: Os arquivos de índices e de dados devem estar abertos e serem válidos. A posição do nó deve ser válida. A chave auxiliar deve ser válida.
//Pos-condicao: A chave auxiliar é inserida no nó não folha da árvore B.
void inserirNo_aux (FILE* fbIndices, FILE* fbDados, int posNo, Chave_Auxiliar chaveAux);

//Descricao: Separa um nó da árvore B em dois nós após a inserção de uma chave.
//Entrada: Ponteiro para o arquivo binário de índices, posição do nó no arquivo de índices, ponteiro para a chave que será promovida para o nó pai, ponteiro para o ponteiro de dados que será promovido para o nó pai.
//Retorno: A posição do novo nó criado.
//Pre-condicao: O arquivo de índices deve estar aberto e ser válido. A posição do nó deve ser válida.
//Pos-condicao: O nó é dividido em dois, e a chave e o ponteiro de dados promovidos são retornados para serem inseridos no nó pai.
int separar (FILE* fbIndices, int posNo, int* chaveMedia, int* ptDadosMedio);

//Descricao: Remove um produto da árvore B.
//Entrada: Ponteiro para o arquivo binário de índices, ponteiro para o arquivo binário de dados.
//Retorno: Nenhum.
//Pre-condicao: Os arquivos de índices e de dados devem estar abertos e serem válidos.
//Pos-condicao: O produto é removido da árvore B.
void removerProduto(FILE* fbIndices,FILE* fbDados);

//Descricao: Remove um produto da árvore B de forma recursiva.
//Entrada: Ponteiro para o arquivo binário de índices, ponteiro para o arquivo binário de dados, posição do nó atual, chave auxiliar do produto a ser removido.
//Retorno: Nenhum.
//Pre-condicao: Os arquivos de índices e de dados devem estar abertos e serem válidos. A posição do nó deve ser válida. A chave auxiliar deve ser válida.
//Pos-condicao: O produto é removido da árvore B.
void removerProduto_aux(FILE* fbIndices, FILE* fbDados, int posNo, Chave_Auxiliar chaveAux);

//Descricao: Verifica se a raiz da árvore B está vazia e redefine a raiz para seu único filho, se existir.
//Entrada: Ponteiro para o arquivo binário de índices.
//Retorno: Nenhum.
//Pre-condicao: O arquivo de índices deve estar aberto e ser válido.
//Pos-condicao: A raiz da árvore B é redefinida, se necessário.
void redefinirRaiz (FILE* fbIndices);

//Descricao: Retorna a chave máxima (última chave) de um nó da árvore B.
//Entrada: Ponteiro para o arquivo binário de índices e a posição do nó.
//Retorno: A chave máxima do nó ou -1 se o nó for inválido.
//Pre-condicao: O arquivo de índices deve estar aberto e ser válido.
//Pos-condicao: Nenhuma.
int chaveMaxima(FILE* fbIndices, int posNo);

//Descricao: Retorna o ponteiro de dados máximo (último ponteiro de dados) de um nó da árvore B.
//Entrada: Ponteiro para o arquivo binário de índices e a posição do nó.
//Retorno: O ponteiro de dados máximo do nó ou -1 se o nó for inválido.
//Pre-condicao: O arquivo de índices deve estar aberto e ser válido.
//Pos-condicao: Nenhuma
int ptDadosMaximo(FILE* fbIndices, int posNo);

//Descricao: Verifica se um nó possui chaves suficientes para continuar a operação.
//Entrada: Ponteiro para o arquivo binário de índices e a posição do nó.
//Retorno: TRUE se o nó possui chaves suficientes, FALSE caso contrário.
//Pre-condicao: O arquivo de índices deve estar aberto e ser válido.
//Pos-condicao: Nenhuma
int chavesSuficientes (FILE* fbIndices, int posNo);

//Descricao: Reajusta a árvore B caso ocorra underflow em um nó.
//Entrada: Ponteiro para o arquivo binário de índices, posição do nó pai e índice do filho.
//Retorno: Nenhum.
//Pre-condicao: O arquivo de índices deve estar aberto e ser válido.
//Pos-condicao: A árvore B é reajustada caso ocorra underflow em um nó.
void reajustarUnderflow (FILE* fbIndicies, int posPai, int indiceFilho);

//Descricao: Anula um nó da árvore B, removendo todas as chaves, ponteiros para dados e filhos.
//Entrada: Ponteiro para o nó a ser anulado.
//Retorno: Ponteiro para o nó anulado.
//Pre-condicao: O nó deve existir e ser válido.
//Pos-condicao: O nó é anulado, ficando vazio.
ArvoreB* anularNo (ArvoreB* no);

//Descricao: Concatena dois nós filhos de um nó pai na árvore B.
//Entrada: Arquivo de índices, posição do nó pai, índice do pai, índice do filho esquerdo e índice do filho direito.
//Retorno: void
//Pre-condicao: Os nós pai, filho esquerdo e filho direito devem existir e ser válidos.
//Pos-condicao: Os nós são concatenados, o filho direito é removido e a árvore é ajustada conforme necessário.
void concatenar (FILE* fbIndices, int posPai, int indicePai, int indiceFilhoEsquerdo, int indiceFilhoDireito);

//Descricao: Realiza a operação de empréstimo de chave e ponteiro para a direita entre um nó e seu irmão direito na árvore B.
//Entrada: Arquivo de índices, posição do nó pai, índice do pai, índice do filho esquerdo, índice do filho direito.
//Retorno: void
//Pre-condicao: O nó pai, o nó filho esquerdo e o nó filho direito devem existir e ser válidos.
//Pos-condicao: Uma chave e seu ponteiro são movidos do nó pai para o nó filho direito, e uma chave e seu ponteiro são movidos do nó filho esquerdo para o nó pai.
void emprestarParaDireita (FILE* fbIndices, int posPai, int indicePai, int indiceFilhoEsquerdo, int indiceFilhoDireito);

//Descricao: Realiza a operação de empréstimo de chave e ponteiro para a esquerda entre um nó e seu irmão esquerdo na árvore B.
//Entrada: Arquivo de índices, posição do nó pai, índice do pai, índice do filho esquerdo, índice do filho direito.
//Retorno: void
//Pre-condicao: O nó pai, o nó filho esquerdo e o nó filho direito devem existir e ser válidos.
//Pos-condicao: Uma chave e seu ponteiro são movidos do nó pai para o nó filho esquerdo, e uma chave e seu ponteiro são movidos do nó filho direito para o nó pai.
void emprestarParaEsquerda (FILE* fbIndices, int posPai, int indicePai, int indiceFilhoEsquerdo, int indiceFilhoDireito);

//Descricao: Atualiza o preço de um produto no sistema
//Entrada: Ponteiros para os arquivos de índices e dados
//Retorno: void
//Pre-condicao: Os arquivos de índices e dados devem existir e estar abertos
//Pos-condicao: O preço do produto é atualizado no arquivo de dados
void atualizarPreco(FILE* fbIndices, FILE* fbDados);

//Descricao: Atualiza o preço de um produto no sistema
//Entrada: Ponteiros para os arquivos de índices e dados
//Retorno: void
//Pre-condicao: Os arquivos de índices e dados devem existir e estar abertos
//Pos-condicao: O preço do produto é atualizado no arquivo de dados
void atualizarPreco_aux(FILE* fbIndices, FILE* fbDados, int codigo, float preco);

//Descricao: Atualiza o estoque de um produto no sistema
//Entrada: Ponteiros para os arquivos de índices e dados
//Retorno: void
//Pre-condicao: Os arquivos de índices e dados devem existir e estar abertos
//Pos-condicao: O estoque do produto é atualizado no arquivo de dados
void atualizarEstoque(FILE* fbIndices, FILE* fbDados);

//Descricao: Atualiza o estoque de um produto no arquivo de dados
//Entrada: Ponteiros para os arquivos de índices e dados, código do produto e novo estoque
//Retorno: void
//Pre-condicao: Os arquivos de índices e dados devem existir e estar abertos, o código do produto deve ser válido
//Pos-condicao: O estoque do produto é atualizado no arquivo de dados
void atualizarEstoque_aux(FILE* fbIndices, FILE* fbDados, int codigo, int estoque);

#endif