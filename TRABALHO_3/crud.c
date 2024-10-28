#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "crud.h"
#include "imprimir.h"

#define TRUE 1
#define FALSE 0


/*
//Descricao: Inicializa um nó da árvore B.
//Entrada: Ponteiro para o nó da árvore B.
//Retorno: O nó da árvore B inicializado.
//Pre-condicao: -
//Pos-condicao: O nó da árvore B é inicializado com suas variáveis devidamente alocadas e valores padrão.
*/
ArvoreB* inicializarNo(ArvoreB* no){
    no = (ArvoreB*)malloc(sizeof(ArvoreB));

    no->nChaves = 0;
    
    for(int i = 0; i <= ORDEM; i++) 
        no->filhos[i] = -1;
    
    for(int i = 0; i < ORDEM; i++){
        no->chaves[i] = -1;
        no->ptDados[i] = -1;
    }

    return no;
}

/*
//Descricao: Realiza a busca por uma chave em um nó da árvore B.
//Entrada: Arquivo de índices, posição do nó, ponteiro para a posição da chave, chave a ser buscada.
//Retorno: 1 se a chave é encontrada, 0 caso contrário.
//Pre-condicao: O arquivo de índices deve estar aberto e o nó deve ser válido.
//Pos-condicao: -
*/
int buscaIndiceChave (FILE* fbIndices, int posNo, int* indiceChave, int chave) {
    if(posNo == -1)
        return FALSE;
    
    ArvoreB* noAux = lerArvoreB(fbIndices, posNo);

    for((*indiceChave) = 0; (*indiceChave) < noAux->nChaves; (*indiceChave)++){
        if(chave == noAux->chaves[(*indiceChave)]){
            free(noAux);
            return TRUE;
        }
        else if(chave < noAux->chaves[(*indiceChave)]){
            free(noAux);
            break;
        }
    }
    
    return FALSE;
}

/*
//Descricao: Realiza a busca por uma chave em um nó da árvore B e retorna a posição do nó.
//Entrada: Arquivo de índices, posição do nó, ponteiro para a posição da chave, chave a ser buscada.
//Retorno: A posição do nó.
//Pre-condicao: O arquivo de índices deve estar aberto e o nó deve ser válido.
//Pos-condicao: -
*/
int buscarNo (FILE* fbIndices, int pos,  int* indiceChave, int chave) {
    if(pos == -1)
        return -1;
    
    ArvoreB* no = lerArvoreB(fbIndices, pos);
    
    int i;
    for(i = 0; i < no->nChaves && no->chaves[i] < chave; i++) ;//busca a posição da chave

    if((i+1) > no->nChaves || no->chaves[i] > chave){
        int noFilhosI = no->filhos[i];
        free(no);
        return buscarNo(fbIndices, noFilhosI, indiceChave, chave);//nao encontrado
    }
    
    *indiceChave = i;//posição da chave ou posição que chave deveria estar
    
    return pos;
}

/*
//Descricao: Realiza o cadastro de um novo produto.
//Entrada: Arquivo de índices, arquivo de dados.
//Retorno: -
//Pre-condicao: Os arquivos de índices e de dados devem estar abertos.
//Pos-condicao: O produto é cadastrado com sucesso ou uma mensagem de erro é exibida.
*/
void cadastrarProduto(FILE* fbIndices, FILE* fbDados){
    Produto* pNovo = (Produto*)malloc(sizeof(Produto));
    Cabecalho_Indices* cabIndices = lerCabecalhoIndices(fbIndices);
    Chave_Auxiliar chaveAux;
    int posRaiz = cabIndices->posRaiz; free(cabIndices);

    printf("Cadastro do novo Produto\n\n");

    printf("Digite o codigo do novo produto: ");
    scanf("%d%*c", &chaveAux.codigo);
    pNovo->codigo = chaveAux.codigo;

    int posChave;
    if(buscarNo(fbIndices, posRaiz, &posChave, chaveAux.codigo) == -1){//não permite inserir um codigo já existente

        printf("Digite o nome do novo produto (maximo de 50 caracteres): ");
        scanf("%[^\n]%*c", pNovo->nome); pNovo->nome[50] = '\0';//apaga o possível excesso de caracteres

        printf("Digite a marca do novo produto (maximo de 30 caracteres): ");
        scanf("%[^\n]%*c", pNovo->marca); pNovo->marca[30] = '\0';//apaga o possível excesso de caracteres

        printf("Digite a categoria do novo produto (maximo de 50 caracteres): ");
        scanf("%[^\n]%*c", pNovo->categoria); pNovo->categoria[50] = '\0';//apaga o possível excesso de caracteres

        printf("Digite a quantidade em estoque: ");
        scanf("%d%*c", &pNovo->estoque);

        printf("Digite o valor do novo produto (00,00): R$ ");
        pNovo->preco = lerValorProduto();//le o valor no formato 00,00

        chaveAux.ptDados = inserirArquivoBinDados(fbDados, pNovo);
        inserirNo(fbIndices, fbDados, chaveAux);

        printf("Produto cadastrado com sucesso\n");
    }
    else
        printf("Nao foi possivel cadastrar novo produto. Codigo ja existente\n");
}

/*
//Descricao: Lê o valor de um produto no formato 00,00.
//Entrada: -
//Retorno: O valor do produto.
//Pre-condicao: -
//Pos-condicao: -
*/
float lerValorProduto(){
    float c1, c2;
    
    scanf("%f,", &c1);
    scanf("%f%*c", &c2);

    return c1 + c2/100;
}

/*
//Descricao: Verifica se um nó da árvore B é folha.
//Entrada: Arquivo de índices, posição do nó.
//Retorno: 1 se o nó é folha, 0 caso contrário.
//Pre-condicao: O arquivo de índices deve estar aberto e o nó deve ser válido.
//Pos-condicao: -
*/
int ehFolha_pos(FILE* fbIndices, int posNo){
    if(posNo != -1){
        ArvoreB* noAux = lerArvoreB(fbIndices, posNo);
        
        if(noAux->filhos[0] == -1){
            free(noAux);
            return TRUE;
        }
        else{
            free(noAux);
            return FALSE;
        }
    }     
    else
        return FALSE;
}

/*
//Descricao: Verifica se um nó da árvore B é folha.
//Entrada: Nó da árvore B.
//Retorno: 1 se o nó é folha, 0 caso contrário.
//Pre-condicao: O nó deve ser válido.
//Pos-condicao: -
*/
int ehFolha_no(ArvoreB* no){
    return (no->filhos[0] == -1);
}

/*
//Descricao: Verifica se um nó da árvore B está em overflow.
//Entrada: Arquivo de índices, posição do nó.
//Retorno: 1 se o nó está em overflow, 0 caso contrário.
//Pre-condicao: O arquivo de índices deve estar aberto e o nó deve ser válido.
//Pos-condicao: -
*/
int overflow_pos(FILE* fbIndices, int posNo){
    if(posNo != -1){
        ArvoreB* noAux = lerArvoreB(fbIndices, posNo);
        
        if(noAux->nChaves == ORDEM){
            free(noAux);
            return TRUE;
        }
        else{
            free(noAux);
            return FALSE;
        }
    }
    else
        return FALSE;
}

int underflow_pos(FILE* fbIndices, int posNo){
    if(posNo != -1){
        ArvoreB* noAux = lerArvoreB(fbIndices, posNo);
        
        if(noAux->nChaves < (int)ORDEM/2){
            free(noAux);
            return TRUE;
        }
        else{
            free(noAux);
            return FALSE;
        }
    }
    else
        return FALSE;
}


/*
//Descricao: Verifica se um nó da árvore B está em overflow.
//Entrada: Nó da árvore B.
//Retorno: 1 se o nó está em overflow, 0 caso contrário.
//Pre-condicao: O nó deve ser válido.
//Pos-condicao: -
*/
int overflow_no(ArvoreB* no){
    return (no->nChaves == ORDEM);
}

/*
//Descricao: Adiciona um elemento à direita de um nó da árvore B.
//Entrada: Arquivo de índices, posição do nó, posição do novo elemento, posição do filho, chave auxiliar.
//Retorno: -
//Pre-condicao: O arquivo de índices deve estar aberto e as posições devem ser válidas.
//Pos-condicao: O elemento é adicionado à direita do nó.
*/
void adicionarADireita (FILE* fbIndices, int posNo, int posNovo, int posFilho, int codigo, int ptDados){
    ArvoreB* noAux = lerArvoreB(fbIndices, posNo);

    //Deslocamento:
    for(int i = noAux->nChaves; i > posNovo; i--){
        noAux->chaves[i] = noAux->chaves[i-1];
        noAux->ptDados[i] = noAux->ptDados[i-1];
        noAux->filhos[i+1] = noAux->filhos[i];
    }
    //Atribuição da nova posição
    noAux->chaves[posNovo] = codigo;
    noAux->ptDados[posNovo] = ptDados;
    noAux->filhos[posNovo+1] = posFilho;
    noAux->nChaves++;
    escreverArvoreB(fbIndices, noAux, posNo); free(noAux);
}

//Descricao: insere um novo nó na árvore B
//Entrada: ponteiro para arquivo de índices, ponteiro para arquivo de dados, chave auxiliar contendo o código e o ponteiro para os dados do novo nó
//Saida: -
//Pre-condicao: ponteiros não nulos para os arquivos de índices e dados
//Pos-condicao: novo nó inserido na árvore B, arquivos de índices e dados modificados conforme necessário
void inserirNo (FILE* fbIndices, FILE* fbDados, Chave_Auxiliar chaveAux){
    Cabecalho_Indices* cabIndices = lerCabecalhoIndices(fbIndices);
    int posRaiz = cabIndices->posRaiz; free(cabIndices);

    if(posRaiz == -1){//árvore vazia
        ArvoreB* raizNova = inicializarNo(raizNova);

        raizNova->chaves[0] = chaveAux.codigo;
        raizNova->ptDados[0] = chaveAux.ptDados;
        raizNova->nChaves = 1;

        inserirArquivoBinIndices(fbIndices, raizNova, TRUE); free(raizNova);
    }
    else{//árvore não vazia
        inserirNo_aux(fbIndices, fbDados, posRaiz, chaveAux);

        ArvoreB* raiz = lerArvoreB(fbIndices, posRaiz);
        if (overflow_no(raiz)) {//overflow da raiz
            int posFilhoEsquerdo = posRaiz; free(raiz);
            int chaveMedia, ptDadosMedio;
            int posFilhoDireito = separar(fbIndices, posRaiz, &chaveMedia, &ptDadosMedio);

            ArvoreB* raizNova = inicializarNo(raizNova);
            raizNova->chaves[0] = chaveMedia;
            raizNova->ptDados[0] = ptDadosMedio;
            raizNova->filhos[0] = posFilhoEsquerdo;
            raizNova->filhos[1] = posFilhoDireito;
            raizNova->nChaves = 1;
            inserirArquivoBinIndices(fbIndices, raizNova, TRUE); free(raizNova);

            ArvoreB* filhoEsquerdo = lerArvoreB(fbIndices, posFilhoEsquerdo);
            for (int i = (((int) ORDEM/2)+1); i < ORDEM; i++) 
                filhoEsquerdo->filhos[i] = -1;
            
            escreverArvoreB(fbIndices, filhoEsquerdo, posFilhoEsquerdo); free(filhoEsquerdo);
        }
    }   
}
// Descrição: Função para inserir uma chave auxiliar em uma árvore B auxiliar.
// Entrada: Ponteiros para os arquivos de índices e dados, posição do nó atual na árvore B, e a chave auxiliar a ser inserida.
// Retorno: void
// Pré-condição: O arquivo de índices e dados devem estar abertos e válidos.
// Pós-condição: A chave auxiliar é inserida na árvore B, respeitando as propriedades da estrutura.
void inserirNo_aux (FILE* fbIndices, FILE* fbDados, int posNo, Chave_Auxiliar chaveAux) {
    int indiceChave;

    if (!buscaIndiceChave(fbIndices, posNo, &indiceChave, chaveAux.codigo)) {            
        if (ehFolha_pos(fbIndices, posNo))
            adicionarADireita(fbIndices, posNo, indiceChave, -1, chaveAux.codigo, chaveAux.ptDados);

        else {
            ArvoreB* noAux = lerArvoreB(fbIndices, posNo);
            int posFilho = noAux->filhos[indiceChave]; free(noAux);
            
            inserirNo_aux(fbIndices, fbDados, posFilho, chaveAux);

            noAux = lerArvoreB(fbIndices, posNo);
            posFilho = noAux->filhos[indiceChave]; free(noAux);

            if (overflow_pos(fbIndices, posFilho)) {//filho ultrapassou numero de nós
                int chaveMedia, ptDadosMedio;
                int posFilhoDireito = separar(fbIndices, posFilho, &chaveMedia, &ptDadosMedio);
                adicionarADireita(fbIndices, posNo, indiceChave, posFilhoDireito, chaveMedia, ptDadosMedio);
            }
        }
    }
}


// Descrição: Função para separar um nó da árvore B em dois, a fim de resolver o overflow.
// Entrada: Ponteiro para o arquivo de índices, posição do nó a ser dividido, ponteiros para armazenar a chave mediana e o ponteiro de dados mediano.
// Retorno: A posição do novo nó criado.
// Pré-condição: O arquivo de índices deve estar aberto e válido. O nó a ser dividido deve estar corretamente estruturado.
// Pós-condição: O nó é dividido em dois, mantendo as propriedades da árvore B.
int separar (FILE* fbIndices, int posNo, int* chaveMedia, int* ptDadosMedio) {
    ArvoreB* no = lerArvoreB(fbIndices, posNo);
    ArvoreB* noFilhoDireito = inicializarNo(noFilhoDireito);
    int q = (no->nChaves)/2, posFilhoDireito;

    noFilhoDireito->nChaves = no->nChaves - q - 1;
    no->nChaves = q;
    *chaveMedia = no->chaves[q];
    *ptDadosMedio = no->ptDados[q];

    noFilhoDireito->filhos[0] = no->filhos[q+1];
    for(int i = 0; i < noFilhoDireito->nChaves; i++) {
        noFilhoDireito->chaves[i] = no->chaves[q+1+i];
        noFilhoDireito->ptDados[i] = no->ptDados[q+1+i];
        noFilhoDireito->filhos[i+1] = no->filhos[q+1+i+1];
    }

    escreverArvoreB(fbIndices, no, posNo); free(no);
    posFilhoDireito = inserirArquivoBinIndices(fbIndices, noFilhoDireito, FALSE); free(noFilhoDireito);

    return posFilhoDireito;
}

// Descrição: Função principal para remover um produto da árvore B.
// Entrada: Ponteiros para os arquivos de índices e dados.
// Retorno: void
// Pré-condição: Os arquivos de índices e dados devem estar abertos e válidos.
// Pós-condição: O produto é removido da árvore B, mantendo as propriedades da estrutura.
void removerProduto(FILE* fbIndices,FILE* fbDados){
    Cabecalho_Indices* cabIndices = lerCabecalhoIndices(fbIndices);
    int posRaiz = cabIndices->posRaiz; free(cabIndices);

    printf("Remover Produto\n\n");

    if(posRaiz != -1){
        imprimir_inOrdem(fbIndices, fbDados);        

        Chave_Auxiliar chaveAux;
        printf("Digite o codigo do produto que deseja remover: "); 
        scanf("%d%*c", &chaveAux.codigo);
        
        int posChave, posNo = buscarNo(fbIndices, posRaiz, &posChave, chaveAux.codigo);
        if(posNo == -1)
            printf("O codigo digitado nao existe\n");
        else{
            ArvoreB* no = lerArvoreB(fbIndices, posNo);
            chaveAux.ptDados = no->ptDados[posChave]; free(no);
            
            removerProduto_aux(fbIndices, fbDados, posRaiz, chaveAux);
            
            printf("Produto removido com sucesso\n");
        }
    }
    else
        printf("Nao foi possivel remover. Nao ha produtos cadastrados\n");
}


// Descrição: Função auxiliar para remover um produto de um nó da árvore B.
// Entrada: Ponteiros para os arquivos de índices e dados, posição do nó atual na árvore B, e a chave auxiliar do produto a ser removido.
// Retorno: void
// Pré-condição: O arquivo de índices deve estar aberto e válido. O nó atual e suas estruturas devem estar corretamente definidos.
// Pós-condição: O produto é removido do nó atual, mantendo as propriedades da árvore B.
void removerProduto_aux(FILE* fbIndices, FILE* fbDados, int posNo, Chave_Auxiliar chaveAux) {
    ArvoreB* no = lerArvoreB(fbIndices, posNo);
    
    int i;
    for(i = 0; i < no->nChaves && chaveAux.codigo > no->chaves[i]; i++) ;//buscar a posição

    if(i < no->nChaves && chaveAux.codigo == no->chaves[i]){//no encontrado
        if(ehFolha_pos(fbIndices, posNo)){
            removerArquivoBinDados(fbDados, chaveAux.ptDados);

            for(int j = i; j < no->nChaves - 1; j++){
                no->chaves[j] = no->chaves[j+1];
                no->ptDados[j] = no->ptDados[j+1];
            }
            no->nChaves--;

            escreverArvoreB(fbIndices, no, posNo);

            free(no);
        }
        else{
            chaveAux.ptDados = no->ptDados[i];
            no->chaves[i] = chaveMaxima(fbIndices, no->filhos[i]);
            no->ptDados[i] = ptDadosMaximo(fbIndices, no->filhos[i]);
            int posFilhoI = no->filhos[i];
            chaveAux.codigo = no->chaves[i];
            escreverArvoreB(fbIndices, no, posNo); free(no);

            removerProduto_aux(fbIndices, fbDados, posFilhoI, chaveAux);
            
            reajustarUnderflow(fbIndices, posNo, i);    
        }
    }
    else{//nao encontrado
        if (!ehFolha_pos(fbIndices, posNo)) { //nao eh folha
            int posFilhoI = no->filhos[i]; free(no);

            removerProduto_aux(fbIndices, fbDados, posFilhoI, chaveAux);

            reajustarUnderflow(fbIndices, posNo, i);
        }
    }

    //Caso da raiz "engolida":
    redefinirRaiz(fbIndices);
}

// Descrição: Função para redefinir a raiz da árvore B, caso a raiz atual esteja vazia.
// Entrada: Ponteiro para o arquivo de índices.
// Retorno: void
// Pré-condição: O arquivo de índices deve estar aberto e válido.
// Pós-condição: A raiz é redefinida, mantendo as propriedades da árvore B.
void redefinirRaiz (FILE* fbIndices) {
    Cabecalho_Indices* cabIndices = lerCabecalhoIndices(fbIndices);
    int posRaiz = cabIndices->posRaiz; free(cabIndices);
    ArvoreB* raiz = lerArvoreB(fbIndices, posRaiz);
    
    if(raiz->nChaves == 0 && raiz->filhos[0] != -1){
        int posFilho = raiz->filhos[0]; free(raiz);            
        cabIndices = lerCabecalhoIndices(fbIndices);
        cabIndices->posRaiz = posFilho;
        
        escreverCabecalhoIndices(fbIndices, cabIndices); free(cabIndices);
        removerArquivoBinIndicies(fbIndices, posRaiz);
    }
}

// Descrição: Função para encontrar a chave máxima (última chave) em um nó da árvore B.
// Entrada: Ponteiro para o arquivo de índices e posição do nó na árvore B.
// Retorno: A chave máxima do nó. Retorna -1 se a posição do nó for inválida.
// Pré-condição: O arquivo de índices deve estar aberto e válido. O nó atual deve estar corretamente estruturado.
// Pós-condição: Retorna a chave máxima do nó.
int chaveMaxima(FILE* fbIndices, int posNo){
    if(posNo == -1)
        return -1;
    
    ArvoreB* no = lerArvoreB(fbIndices, posNo);

    if(no->filhos[no->nChaves] == -1) {
        int chave = no->chaves[no->nChaves - 1]; free(no);
        
        return chave;
    }
    else{
        int posFilho=no->filhos[no->nChaves]; free(no);
        
        return chaveMaxima (fbIndices, posFilho);
    }
}

int ptDadosMaximo(FILE* fbIndices, int posNo){
    if(posNo == -1)
        return -1;
    
    ArvoreB* no = lerArvoreB(fbIndices, posNo);

    if(no->filhos[no->nChaves] == -1) {
        int ptDado = no->ptDados[no->nChaves - 1]; free(no);

        return ptDado;
    }
    else{
        int posFilho = no->filhos[no->nChaves]; free(no);

        return ptDadosMaximo(fbIndices, posFilho);
    }
}

// Descrição: Função para encontrar o ponteiro de dados máximo (último ponteiro de dados) em um nó da árvore B.
// Entrada: Ponteiro para o arquivo de índices e posição do nó na árvore B.
// Retorno: O ponteiro de dados máximo do nó. Retorna -1 se a posição do nó for inválida.
// Pré-condição: O arquivo de índices deve estar aberto e válido. O nó atual deve estar corretamente estruturado.
// Pós-condição: Retorna o ponteiro de dados máximo do nó.
int chavesSuficientes (FILE* fbIndices, int posNo) {
    if(posNo != -1){
        ArvoreB* noAux = lerArvoreB(fbIndices, posNo);
        
        if(noAux->nChaves > (int)ORDEM/2){
            free(noAux);
            return TRUE;
        }
        else{
            free(noAux);
            return FALSE;
        }
    }
    else
        return FALSE;
}

// Descrição: Função para reajustar a árvore B após um underflow em um nó filho.
// Entrada: Ponteiro para o arquivo de índices, posição do nó pai na árvore B e índice do filho com underflow.
// Retorno: void
// Pré-condição: O arquivo de índices deve estar aberto e válido. O nó pai e seus filhos devem estar corretamente estruturados.
// Pós-condição: A árvore B é reajustada para corrigir o underflow no filho indicado.
void reajustarUnderflow (FILE* fbIndicies, int posPai, int indiceFilho) {
    ArvoreB* noPai = lerArvoreB(fbIndicies, posPai);

    if(underflow_pos(fbIndicies, noPai->filhos[indiceFilho])) {
        int indicePai;

        if(indiceFilho == 0) {
            if (chavesSuficientes (fbIndicies, noPai->filhos[indiceFilho + 1])) {
                indicePai = indiceFilho;
                emprestarParaEsquerda (fbIndicies, posPai, indicePai, indiceFilho, indiceFilho + 1);
            }
            else {
                indicePai = indiceFilho;
                concatenar (fbIndicies, posPai, indicePai, indiceFilho, indiceFilho + 1);
            }
        }
        else {
            if (indiceFilho == noPai->nChaves) {
                if (chavesSuficientes(fbIndicies, noPai->filhos[indiceFilho - 1])) {
                    indicePai = indiceFilho - 1;
                    emprestarParaDireita(fbIndicies, posPai, indicePai, indiceFilho - 1, indiceFilho);
                }
                else {
                    indicePai = indiceFilho - 1;
                    concatenar(fbIndicies, posPai, indicePai, indiceFilho - 1, indiceFilho);
                }
            }
            else {
                if (chavesSuficientes(fbIndicies, noPai->filhos[indiceFilho + 1])) {
                    indicePai = indiceFilho;
                    emprestarParaEsquerda (fbIndicies, posPai, indicePai, indiceFilho, indiceFilho + 1);
                }
                else if (chavesSuficientes(fbIndicies, noPai->filhos[indiceFilho - 1])) {
                    indicePai = indiceFilho - 1;
                    emprestarParaDireita(fbIndicies, posPai, indicePai, indiceFilho - 1, indiceFilho);
                }
                else {
                    indicePai = indiceFilho - 1;
                    concatenar(fbIndicies, posPai, indicePai, indiceFilho - 1, indiceFilho);
                }    
            }
        }
    }

    free(noPai);
}

// Descrição: Função para anular um nó da árvore B, ou seja, limpar suas chaves, ponteiros de dados e filhos.
// Entrada: Ponteiro para o nó a ser anulado.
// Retorno: O nó anulado.
// Pré-condição: O nó deve estar corretamente estruturado.
// Pós-condição: Todas as chaves, ponteiros de dados e filhos do nó são definidos como -1 e o número de chaves é resetado para 0.
ArvoreB* anularNo (ArvoreB* no) {
    int i;
    for (i = 0; i < no->nChaves; i++) {
        no->chaves[i] = -1;
        no->ptDados[i] = -1;
        no->filhos[i] = -1;
    }
    no->filhos[i] = -1;
    no->nChaves = 0;

    return no;
}

// Descrição: Função para concatenar dois nós irmãos em um nó pai da árvore B.
// Entrada: Ponteiro para o arquivo de índices, posição do nó pai na árvore B, índice do pai, índice do filho esquerdo e índice do filho direito.
// Retorno: void
// Pré-condição: O arquivo de índices deve estar aberto e válido. Os nós pai, filho esquerdo e filho direito devem estar corretamente estruturados.
// Pós-condição: Os nós são concatenados e a árvore B é reajustada para manter suas propriedades.
void concatenar (FILE* fbIndices, int posPai, int indicePai, int indiceFilhoEsquerdo, int indiceFilhoDireito) {
    ArvoreB* noPai = lerArvoreB(fbIndices, posPai);
    ArvoreB* noIrmaoEsquerdo = lerArvoreB(fbIndices, noPai->filhos[indiceFilhoEsquerdo]);
    ArvoreB* noIrmaoDireito = lerArvoreB(fbIndices, noPai->filhos[indiceFilhoDireito]);
    int posFilhoEsquerdo = noPai->filhos[indiceFilhoEsquerdo], posFilhoDireito = noPai->filhos[indiceFilhoDireito];

    //Desce a chave e ponteiro mediadores do pai
    noIrmaoEsquerdo->chaves[noIrmaoEsquerdo->nChaves] = noPai->chaves[indicePai];
    noIrmaoEsquerdo->ptDados[noIrmaoEsquerdo->nChaves] = noPai->ptDados[indicePai]; 
    noIrmaoEsquerdo->nChaves++;

    //Passa as chaves, ponteiro e filhos do irmao direito para o irmao esquerdo
    int i, j;
    for (i = noIrmaoEsquerdo->nChaves, j = 0; j < noIrmaoDireito->nChaves; i++, j++) {
        noIrmaoEsquerdo->chaves[i] = noIrmaoDireito->chaves[j];
        noIrmaoEsquerdo->ptDados[i] = noIrmaoDireito->ptDados[j];
        noIrmaoEsquerdo->filhos[i] = noIrmaoDireito->filhos[j];
    }
    noIrmaoEsquerdo->filhos[i] = noIrmaoDireito->filhos[j];
    noIrmaoEsquerdo->nChaves = i;
    escreverArvoreB(fbIndices, noIrmaoEsquerdo, posFilhoEsquerdo); free(noIrmaoEsquerdo);

    //Ajustar pai:
    for (i = indicePai; i < noPai->nChaves; i++) {
        noPai->chaves[i] = noPai->chaves[i + 1];
        noPai->ptDados[i] = noPai->ptDados[i + 1];
        noPai->filhos[i + 1] = noPai->filhos[i + 2];
    }
    noPai->nChaves--;
    escreverArvoreB(fbIndices, noPai, posPai); free(noPai);

    //Finalizar o irmão direito:
    noIrmaoDireito = anularNo(noIrmaoDireito);
    escreverArvoreB(fbIndices, noIrmaoDireito, posFilhoDireito); free(noIrmaoDireito);
    removerArquivoBinIndicies(fbIndices, posFilhoDireito);
}

//Descricao: Realiza a operação de empréstimo de chave e ponteiro para a direita entre um nó e seu irmão direito na árvore B.
//Entrada: Arquivo de índices, posição do nó pai, índice do pai, índice do filho esquerdo, índice do filho direito.
//Retorno: void
//Pre-condicao: O nó pai, o nó filho esquerdo e o nó filho direito devem existir e ser válidos.
//Pos-condicao: Uma chave e seu ponteiro são movidos do nó pai para o nó filho direito, e uma chave e seu ponteiro são movidos do nó filho esquerdo para o nó pai.
void emprestarParaDireita (FILE* fbIndices, int posPai, int indicePai, int indiceFilhoEsquerdo, int indiceFilhoDireito) {
    ArvoreB* noPai = lerArvoreB(fbIndices, posPai);
    ArvoreB* noFilhoEsquerdo = lerArvoreB(fbIndices, noPai->filhos[indiceFilhoEsquerdo]);
    ArvoreB* noFilhoDireito = lerArvoreB(fbIndices, noPai->filhos[indiceFilhoDireito]);
    int posFilhoEsquerdo = noPai->filhos[indiceFilhoEsquerdo], posFilhoDireito = noPai->filhos[indiceFilhoDireito];

    //Ajusta irmao direito para depois receber mais uma chave e um filho:
    int i;
    for(i = noFilhoDireito->nChaves; i > 0 ; i--) {
        noFilhoDireito->chaves[i] = noFilhoDireito->chaves[i - 1];
        noFilhoDireito->ptDados[i] = noFilhoDireito->ptDados[i - 1];
    }
    //Irmao direito recebe uma chave ponteiro de seu pai:
    noFilhoDireito->chaves[i] = noPai->chaves[indicePai];
    noFilhoDireito->ptDados[i] = noPai->ptDados[indicePai];
    //Irmao direito recebe o ultimo filho do irmao direito:
    noFilhoDireito->filhos[0] = noFilhoEsquerdo->filhos[noFilhoEsquerdo->nChaves];
    //Incrementa as chaves:
    noFilhoDireito->nChaves++;
    escreverArvoreB(fbIndices, noFilhoDireito, posFilhoDireito); free(noFilhoDireito);

    //Pai troca de no e de chave:
    noPai->chaves[indicePai] = noFilhoEsquerdo->chaves[noFilhoEsquerdo->nChaves - 1];
    noPai->ptDados[indicePai] = noFilhoEsquerdo->ptDados[noFilhoEsquerdo->nChaves - 1];
    escreverArvoreB(fbIndices, noPai, posPai); free(noPai);

    //Irmão esquerdo perde chave, ponteiro e filho:
    noFilhoEsquerdo->chaves[noFilhoEsquerdo->nChaves - 1] = -1;
    noFilhoEsquerdo->ptDados[noFilhoEsquerdo->nChaves - 1] = -1;
    noFilhoEsquerdo->filhos[noFilhoEsquerdo->nChaves] = -1;
    noFilhoEsquerdo->nChaves--;
    escreverArvoreB(fbIndices, noFilhoEsquerdo, posFilhoEsquerdo); free(noFilhoEsquerdo);
}

//Descricao: Realiza a operação de empréstimo de chave e ponteiro para a esquerda entre um nó e seu irmão esquerdo na árvore B.
//Entrada: Arquivo de índices, posição do nó pai, índice do pai, índice do filho esquerdo, índice do filho direito.
//Retorno: void
//Pre-condicao: O nó pai, o nó filho esquerdo e o nó filho direito devem existir e ser válidos.
//Pos-condicao: Uma chave e seu ponteiro são movidos do nó pai para o nó filho esquerdo, e uma chave e seu ponteiro são movidos do nó filho direito para o nó pai.
void emprestarParaEsquerda (FILE* fbIndices, int posPai, int indicePai, int indiceFilhoEsquerdo, int indiceFilhoDireito) {
    ArvoreB* noPai = lerArvoreB(fbIndices, posPai);
    ArvoreB* noFilhoEsquerdo = lerArvoreB(fbIndices, noPai->filhos[indiceFilhoEsquerdo]);
    ArvoreB* noFilhoDireito = lerArvoreB(fbIndices, noPai->filhos[indiceFilhoDireito]);
    int posFilhoEsquerdo = noPai->filhos[indiceFilhoEsquerdo], posFilhoDireito = noPai->filhos[indiceFilhoDireito];

    //O irmão esquerdo recebe a chave e ponteiro da chave mediadora do pai:
    noFilhoEsquerdo->chaves[noFilhoEsquerdo->nChaves] = noPai->chaves[indicePai];
    noFilhoEsquerdo->ptDados[noFilhoEsquerdo->nChaves] = noPai->ptDados[indicePai];
    noFilhoEsquerdo->nChaves++;
    //O irmão esquerdo recebe o primeiro filho do irmão da direita
    noFilhoEsquerdo->filhos[noFilhoEsquerdo->nChaves] = noFilhoDireito->filhos[0];
    escreverArvoreB(fbIndices, noFilhoEsquerdo, posFilhoEsquerdo); free(noFilhoEsquerdo);

    //O pai recebe a primeira chave e ponteiro do filho da direita
    noPai->chaves[indicePai] = noFilhoDireito->chaves[0];
    noPai->ptDados[indicePai] = noFilhoDireito->ptDados[0];
    escreverArvoreB(fbIndices, noPai, posPai); free(noPai);

    //Ajuse do filho da direita que perdeu a primeira chave, ponteiro e filho
    int i;
    for(i=0; i < noFilhoDireito->nChaves; i++) {
        noFilhoDireito->chaves[i] = noFilhoDireito->chaves[i + 1];
        noFilhoDireito->ptDados[i] = noFilhoDireito->ptDados[i + 1];
        noFilhoDireito->filhos[i] = noFilhoDireito->filhos[i + 1];
    }
    noFilhoDireito->filhos[i] = noFilhoDireito->filhos[i + 1];
    noFilhoDireito->nChaves--;
    escreverArvoreB(fbIndices, noFilhoDireito, posFilhoDireito); free(noFilhoDireito);
}

//Descricao: Atualiza o preço de um produto no sistema
//Entrada: Ponteiros para os arquivos de índices e dados
//Retorno: void
//Pre-condicao: Os arquivos de índices e dados devem existir e estar abertos
//Pos-condicao: O preço do produto é atualizado no arquivo de dados
void atualizarPreco(FILE* fbIndices, FILE* fbDados){
    Cabecalho_Indices* cabIndices = lerCabecalhoIndices(fbIndices);
    int posRaiz = cabIndices->posRaiz; free(cabIndices);
    int codigo; float preco = 0.0;

    printf("Atualizar Preco\n");

    imprimir_inOrdem(fbIndices, fbDados);

    printf("Digite o codigo do produto que deseja atualizar: "); 
    scanf("%d%*c", &codigo);

    int posChave;
    if(buscarNo(fbIndices, posRaiz, &posChave, codigo) != -1) {
        imprimirProduto_aux(fbIndices, fbDados,codigo);

        printf("Digite o novo valor (00,00): R$ ");
        preco = lerValorProduto();
    }

    atualizarPreco_aux(fbIndices, fbDados, codigo, preco);
}

//Descricao: Atualiza o preço de um produto no sistema
//Entrada: Ponteiros para os arquivos de índices e dados
//Retorno: void
//Pre-condicao: Os arquivos de índices e dados devem existir e estar abertos
//Pos-condicao: O preço do produto é atualizado no arquivo de dados
void atualizarPreco_aux(FILE* fbIndices, FILE* fbDados, int codigo, float preco){
    Cabecalho_Indices* cabIndices = lerCabecalhoIndices(fbIndices);
    int posRaiz = cabIndices->posRaiz; free(cabIndices);
    int posChave, posNo = buscarNo(fbIndices, posRaiz, &posChave, codigo);

    if(posNo != -1){
        ArvoreB* no = lerArvoreB(fbIndices,posNo);
        int pos_ptDados = no->ptDados[posChave]; free(no);
        
        Produto* p = lerDados(fbDados, pos_ptDados);
        p->preco = preco;
        escreverDados(fbDados, p, pos_ptDados);

        printf("Produto atualizado com sucesso\n");
        imprimirProduto_aux(fbIndices, fbDados, codigo);

        free(p);
    }
    else
        printf("O codigo digitado nao existe. Nao foi possivel atualizar o produto\n");
}

//Descricao: Atualiza o estoque de um produto no sistema
//Entrada: Ponteiros para os arquivos de índices e dados
//Retorno: void
//Pre-condicao: Os arquivos de índices e dados devem existir e estar abertos
//Pos-condicao: O estoque do produto é atualizado no arquivo de dados
void atualizarEstoque(FILE* fbIndices, FILE* fbDados){
    Cabecalho_Indices* cabIndices = lerCabecalhoIndices(fbIndices);
    int posRaiz = cabIndices->posRaiz; free(cabIndices);
    int codigo, estoque = 0;

    printf("Atualizar Estoque*\n");

    imprimir_inOrdem(fbIndices, fbDados);

    printf("Digite o codigo do produto que deseja alterar: "); 
    scanf("%d%*c", &codigo);

    int posChave;
    if(buscarNo(fbIndices, posRaiz, &posChave, codigo) != -1) {
        imprimirProduto_aux(fbIndices, fbDados,codigo);

        printf("Digite o novo valor de estoque: "); 
        scanf("%d%*c", &estoque);
    }

    atualizarEstoque_aux(fbIndices, fbDados, codigo, estoque);
}

//Descricao: Atualiza o estoque de um produto no arquivo de dados
//Entrada: Ponteiros para os arquivos de índices e dados, código do produto e novo estoque
//Retorno: void
//Pre-condicao: Os arquivos de índices e dados devem existir e estar abertos, o código do produto deve ser válido
//Pos-condicao: O estoque do produto é atualizado no arquivo de dados
void atualizarEstoque_aux(FILE* fbIndices, FILE* fbDados, int codigo, int estoque){
    Cabecalho_Indices* cabIndices = lerCabecalhoIndices(fbIndices);
    int posRaiz = cabIndices->posRaiz; free(cabIndices);
    int posChave, posNo = buscarNo(fbIndices, posRaiz, &posChave, codigo);

    if(posNo != -1){
        ArvoreB* no = lerArvoreB(fbIndices,posNo);
        int pos_ptDados = no->ptDados[posChave]; free(no);
        
        Produto* p = lerDados(fbDados, pos_ptDados);
        p->estoque = estoque;
        escreverDados(fbDados, p, pos_ptDados);

        printf("Produto atualizado com sucesso\n");
        imprimirProduto_aux(fbIndices, fbDados, codigo);

        free(p);
    }
    else
        printf("Codigo inxistente. Nao foi possivel atualizar o estoque.\n");
}