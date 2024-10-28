#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore_b.h"
    
//Descricao: Escreve o cabeçalho de índices no arquivo binário.
//Entrada:   Ponteiro para o arquivo binário, ponteiro para o cabeçalho de índices.
//Retorno:   Nenhum.
//Pre-condicao: O arquivo deve estar aberto e ser válido. O ponteiro do cabeçalho não deve ser nulo.
//Pos-condicao: O cabeçalho de índices é escrito no início do arquivo binário.
void escreverCabecalhoIndices(FILE* fb, Cabecalho_Indices* hd){
    fseek(fb, 0, SEEK_SET);//aponta para o começo do ARQUIVO_BINARIO_INDEX
    fwrite(hd, sizeof(Cabecalho_Indices), 1, fb);//copia a ESTRUTURA do cabeçalho em HD para o que foi aponteado em FSEEK
}


//Descricao: Le o cabeçalho de índices do arquivo binário.
//Entrada:   Ponteiro para o arquivo binário.
//Retorno:   Ponteiro para o cabeçalho de índices lido do arquivo.
//Pre-condicao: O arquivo deve estar aberto e ser válido.
//Pos-condicao: O ponteiro para o cabeçalho de índices lido é retornado.
Cabecalho_Indices* lerCabecalhoIndices(FILE* fb){
    Cabecalho_Indices *cab = (Cabecalho_Indices*)malloc(sizeof(Cabecalho_Indices));

    fseek(fb, 0, SEEK_SET);//aponta para o começo do ARQUIVO_BINARIO_INDEX
    fread(cab, sizeof(Cabecalho_Indices), 1, fb);//copia a ESTUTURA do ARQUIVO_BINARIO_INDEX para HD

    return cab;
}


//Descricao: Inicializa a árvore B no arquivo binário.
//Entrada:   Ponteiro para o arquivo binário.
//Retorno:   Nenhum.
//Pre-condicao: O arquivo deve estar aberto e ser válido.
//Pos-condicao: A árvore B é inicializada no arquivo binário.
void initializarArvore(FILE* fb){
    Cabecalho_Indices *cab = (Cabecalho_Indices*)malloc(sizeof(Cabecalho_Indices));

    cab->posRaiz = -1;//inicializar "raiz" como "NULL"
    cab->posTopo = 0;//indica que a proximo posicao livre como a primeira posicao disponivel
    cab->posLivre = -1;//inicializar lista de nós livres como "NULL"

    escreverCabecalhoIndices(fb, cab);//escreve o cabecalho inicializado
    free(cab);//desaloca memória do ponteiro auxiliar
}


//Descricao: Escreve um nó da árvore B no arquivo binário.
//Entrada:   Ponteiro para o arquivo binário, ponteiro para o nó da árvore B, posição do nó no arquivo.
//Retorno:   Nenhum.
//Pre-condicao: O arquivo deve estar aberto e ser válido. O ponteiro para o nó não deve ser nulo.
//Pos-condicao: O nó da árvore B é escrito no arquivo binário na posição especificada.

void escreverArvoreB(FILE* fb, ArvoreB* r, int pos){
    fseek(fb, sizeof(Cabecalho_Indices) + sizeof(ArvoreB) * pos, SEEK_SET);//aponto para a ArvoreB na posicao desejada, pulando os bits do cabecalho
    fwrite(r, sizeof(ArvoreB), 1, fb);//copia a estrutura da arvore para o ARQUIVO_BINARIO_INDEX, de acordo com o que foi apontado em FSEEK
}


//Descricao: Le um nó da árvore B do arquivo binário.
//Entrada:   Ponteiro para o arquivo binário, posição do nó no arquivo.
//Retorno:   Ponteiro para o nó da árvore B lido do arquivo.
//Pre-condicao: O arquivo deve estar aberto e ser válido.
//Pos-condicao: O ponteiro para o nó da árvore B lido é retornado.
ArvoreB* lerArvoreB(FILE* fb, int pos){
    ArvoreB* raiz = (ArvoreB*)malloc(sizeof(ArvoreB));

    fseek(fb, sizeof(Cabecalho_Indices) + sizeof(ArvoreB) * pos, SEEK_SET);//aponta para a ArvoreB na posicao desejada, pulando os bits do cabec
    fread(raiz, sizeof(ArvoreB), 1, fb);//copia para -r- a estrutura ARVORE de acordo com o que foi apontado em FSEEK no ARQUIVO BINARIO

    return raiz;
}


//Descricao: Escreve o cabeçalho de dados no arquivo binário.
//Entrada:   Ponteiro para o arquivo binário, ponteiro para o cabeçalho de dados.
//Retorno:   Nenhum.
//Pre-condicao: O arquivo deve estar aberto e ser válido. O ponteiro do cabeçalho não deve ser nulo.
//Pos-condicao: O cabeçalho de dados é escrito no início do arquivo binário.
void escreverCabecalhoDados(FILE* fb, Cabecalho_Dados* hd){
    fseek(fb, 0, SEEK_SET);//aponta para o começo do ARQUIVO_BINARIO_DATA
    fwrite(hd, sizeof(Cabecalho_Dados), 1, fb);//copia a ESTRUTURA do cabeçalho em HD para o que foi aponteado em FSEEK
}


//Descricao: Le o cabeçalho de dados do arquivo binário.
//Entrada:   Ponteiro para o arquivo binário.
//Retorno:   Ponteiro para o cabeçalho de dados lido do arquivo.
//Pre-condicao: O arquivo deve estar aberto e ser válido.
//Pos-condicao: O ponteiro para o cabeçalho de dados lido é retornado.
Cabecalho_Dados* lerCabecalhoDados(FILE* fb){
    Cabecalho_Dados *cab = (Cabecalho_Dados*)malloc(sizeof(Cabecalho_Dados));

    fseek(fb, 0, SEEK_SET);//aponta para o começo do ARQUIVO_BINARIO_DATA
    fread(cab, sizeof(Cabecalho_Dados), 1, fb);//copia a ESTUTURA do ARQUIVO_BINARIO_DATA para HD

    return cab;
}


//Descricao: Inicializa os dados no arquivo binário.
//Entrada:   Ponteiro para o arquivo binário.
//Retorno:   Nenhum.
//Pre-condicao: O arquivo deve estar aberto e ser válido.
//Pos-condicao: Os dados são inicializados no arquivo binário.
void inicilizarDados(FILE* fb){
    Cabecalho_Dados *cab = (Cabecalho_Dados*)malloc(sizeof(Cabecalho_Dados));

    cab->posTopo = 0;//indica que a proximo posicao livre como a primeira posicao disponivel
    cab->posLivre = -1;//inicializar lista de nós livres como "NULL"

    escreverCabecalhoDados(fb, cab);//escreve o cabecalho inicializado
    free(cab);//desaloca memória do ponteiro auxiliar
}


//Descricao: Escreve um produto no arquivo binário.
//Entrada:   Ponteiro para o arquivo binário, ponteiro para o produto, posição do produto no arquivo.
//Retorno:   Nenhum.
//Pre-condicao: O arquivo deve estar aberto e ser válido. O ponteiro para o produto não deve ser nulo.
//Pos-condicao: O produto é escrito no arquivo binário na posição especificada.
void escreverDados(FILE* fb, Produto* p, int pos){
    fseek(fb, sizeof(Cabecalho_Dados) + sizeof(Produto) * pos, SEEK_SET);//aponto para Produto na posicao desejada, pulando os bits do cabecalho
    fwrite(p, sizeof(Produto), 1, fb);//copia a estrutura do produto para o ARQUIVO_BINARIO_DATA, de acordo com o que foi apontado em FSEEK
}


//Descricao: Le um produto do arquivo binário.
//Entrada:   Ponteiro para o arquivo binário, posição do produto no arquivo.
//Retorno:   Ponteiro para o produto lido do arquivo.
//Pre-condicao: O arquivo deve estar aberto e ser válido.
//Pos-condicao: O ponteiro para o produto lido é retornado.
Produto* lerDados(FILE* fb, int pos){
    Produto* p = (Produto*)malloc(sizeof(Produto));

    fseek(fb, sizeof(Cabecalho_Dados) + sizeof(Produto) * pos, SEEK_SET);//aponta para o Produto na posicao desejada, pulando os bits do cabec
    fread(p, sizeof(Produto), 1, fb);//copia para -r- a estrutura ARVORE de acordo com o que foi apontado em FSEEK no ARQUIVO BINARIO

    return p;
}


//Descricao: Insere um nó na árvore B no arquivo binário.
//Entrada:   Ponteiro para o arquivo binário, ponteiro para o nó da árvore B, flag indicando se é raiz.
//Retorno:   Posição do nó no arquivo.
//Pre-condicao: O arquivo deve estar aberto e ser válido. O ponteiro para o nó não deve ser nulo.
//Pos-condicao: O nó é inserido na árvore B no arquivo binário.
int inserirArquivoBinIndices (FILE* fb, ArvoreB* no, int ehRaiz) {
    Cabecalho_Indices* cab = lerCabecalhoIndices(fb);
    int posIn = -1;

    if(cab->posLivre == -1){
        posIn = cab->posTopo;
        cab->posTopo++;
    }
    else{
        posIn = cab->posLivre;
        ArvoreB* noLivre = lerArvoreB(fb, cab->posLivre);
        cab->posLivre = noLivre->filhos[0]; free(noLivre);
    }

    if(cab->posRaiz == -1 || (ehRaiz)) 
        cab->posRaiz = posIn;

    escreverArvoreB(fb, no, posIn);
    escreverCabecalhoIndices(fb, cab); free(cab);

    return posIn;
}


//Descricao: Remove um nó da árvore B do arquivo binário.
//Entrada:   Ponteiro para o arquivo binário, posição do nó no arquivo.
//Retorno:   Nenhum.
//Pre-condicao: O arquivo deve estar aberto e ser válido. A posição do nó deve ser válida.
//Pos-condicao: O nó é removido da árvore B no arquivo binário.
void removerArquivoBinIndicies(FILE* fb, int pos) {
    Cabecalho_Indices* cab = lerCabecalhoIndices(fb);
    ArvoreB* no = lerArvoreB(fb, pos);

    no->filhos[0] = cab->posLivre;//encadeia a nova cabeça da lista com a cabeça antiga
    cab->posLivre = pos;
    if (cab->posRaiz == pos)
        cab->posRaiz = -1;//raiz foi removida
    
    escreverArvoreB(fb, no, pos);
    escreverCabecalhoIndices(fb, cab);

    free(no);
    free(cab);
}


//Descricao: Insere um produto no arquivo binário.
//Entrada:   Ponteiro para o arquivo binário, ponteiro para o produto.
//Retorno:   Posição do produto no arquivo.
//Pre-condicao: O arquivo deve estar aberto e ser válido. O ponteiro para o produto não deve ser nulo.
//Pos-condicao: O produto é inserido no arquivo binário.
int inserirArquivoBinDados(FILE* fb, Produto* p){
    Cabecalho_Dados* cab = lerCabecalhoDados(fb);
    int posIn;

    if(cab->posLivre == -1){
        posIn = cab->posTopo;
        cab->posTopo++;
    }
    else{
        posIn = cab->posLivre;
        Produto* pLivre = lerDados(fb, cab->posLivre);
        cab->posLivre = pLivre->codigo; free(pLivre);
    }

    escreverDados(fb, p, posIn);
    escreverCabecalhoDados(fb, cab); free(cab);

    return posIn;
}


//Descricao: Remove um produto do arquivo binário.
//Entrada:   Ponteiro para o arquivo binário, posição do produto no arquivo.
//Retorno:   Nenhum.
//Pre-condicao: O arquivo deve estar aberto e ser válido. A posição do produto deve ser válida.
//Pos-condicao: O produto é removido do arquivo binário.
void removerArquivoBinDados(FILE* fb, int pos){
    Produto* p = lerDados(fb, pos);
    Cabecalho_Dados* cab = lerCabecalhoDados(fb);
    
    p->codigo = cab->posLivre;//encadeia a cabeça da lista de posLivre com a antiga cabeça
    cab->posLivre = pos;//nova posição livre
    
    escreverDados(fb, p, pos); free(p);
    escreverCabecalhoDados(fb, cab); free(cab);
}