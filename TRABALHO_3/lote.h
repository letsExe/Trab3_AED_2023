#include <stdio.h>
#include <string.h>
#include <stdlib.h>  

//Descricao:    faz a leitura do caminho do arquivo texto e chama a função ler_arq_texto que faz a leitura do conteúdo do arquivo texto
//Entrada:      ponteiro não nulo para o arquivo binário
//Saida:        -
//Pre-condicao: ponteiro não nulo para o arquivo binário
//Pos-condicao: arquivo binario modificado, caso os códigos lidos do arq. texto sejam válidas
void operacaoLote(FILE* fbIndices, FILE* fbDados);

//Descricao:    faz a leitura do conteúdo do arquivo texto, e chama as funções (inserir, remover e/ou alterar) de  acordo com a operação lida ('I','R','A')
//Entrada:      ponteiros não nulos para arq. binário e arq. texto
//Saida:        -
//Pre-condicao: ponteiros não nulos para arq. binário e arq. texto
//Pos-condicao: arquivo binario modificado, caso os códigos lidos do arq. texto sejam válidas
void lerArquivoTexto(FILE* fbIndices, FILE* fbDados, FILE *fr);

//Descricao:    caso a operação lida seja 'I', é chamada essa função. ela faz a leitura do conteúdo do arquivo texto para uma estrutura árvore auxiliar, e então chama a função inserirProduto que é responsável
//              pos inserir essa estrutura auxiliar dentro do arquivo binário
//Entrada:      ponteiro não nulo para o arquivo binário e para o arquivo texto
//Saida:        -
//Pre-condicao: ponteiro não nulo para o arquivo binário e para o arquivo texto. função de inserir já criada.
//Pos-condicao: arquivo binário modificado caso o código do produto ainda não exista na árvore
void inserirLote(FILE* fbIndices, FILE* fbDados, FILE* fr);

//Descricao:    caso a operação lida seja 'R', é chamada essa função. ela faz a leitura do conteúdo do arquivo texto: o código do produto a ser removido, e então chama a função removerNo que é responsável
//              pos remover essa nó do arquivo binário, caso esse código exista.     
//Entrada:      ponteiro não nulo para o arquivo binário e para o arquivo texto
//Saida:        -
//Pre-condicao: ponteiro não nulo para o arquivo binário e para o arquivo texto
//Pos-condicao: arquivo binário modificado caso o código do produto exista na árvore
void removerLote(FILE* fbIndices, FILE* fbDados, FILE *fr);

//Descricao:    caso a operação lida seja 'A', é chamada essa função. ela é responsável por alterar a valor de um protudo já existente, caso o formato da linha no arq. texto seja "A;cod;;valor,valor", ou alterar
//              o estoque, caso o formato seja "A;cod;estoque;", ou ambos, caso o formato seja "A;cod;estoque;valor,valor"
//              a função lê todo conteúdo da linha a partir de "cod;" no formato de uma string token, para sua melhor
//              manipulação, então pode chamar as funções ler_preco e/ou ler_estoque que fazem a conversão da string
//              para seus devídos formatos e então chama as funções responsáveis por alterar os valores no arquivo binario
//Entrada:      ponteiro não nulo para o arquivo binário e para o arquivo texto
//Saida:        -
//Pre-condicao: ponteiro não nulo para o arquivo binário e para o arquivo texto
//Pos-condicao: arquivo binário alterado, caso os códigos lidos sejam válidos
void alterarLote(FILE *fb_index,FILE* fb_data,FILE *fr);

//Descricao:    função responsável por ler o novo valor no formato 00,00 de dentro da string token, que contem a linha do arq. texto a partir de "A;cod;". a leitura começa a partir de token[n] 
//Entrada:      token, que contem a linha do arq. texto a partir de "A;cod;", e n, o inteiro de onde começa a leitura de token
//Saida:        novo valor do produto, obtido a partir de token
//Pre-condicao: chamada pela função alterar_em_lote
//Pos-condicao: -
float lerPreco(char* token, int n);

//Descricao:    função responsável por ler o valor int de estoque a partir da string token. ele passa pela string incrementando a variável n, que depois servirá para a leitura do float valor, caso ele exista
//Entrada:      token, que contem a linha do arq. texto a partir de "A;cod;".
//Saida:        valor do novo estoque do produto, obtivo a partir de token.
//Pre-condicao: chamada pela função alterar_em_lote
//Pos-condicao: n incrementada, tendo lido o valor do estoque do produto
int lerEstoque(char* token, int* n);
