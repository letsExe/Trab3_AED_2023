#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "imprimir.h"
#include "crud.h"


//Descrição: Função para imprimir as informações de um produto a partir de seu código
//Entrada: Ponteiros para os arquivos de índices e dados
//Saida: void
//Pré-condição: Os arquivos de índices e dados devem existir e estar abertos
//Pós-condição: As informações do produto são impressas na tela
void imprimirProduto(FILE* fbIndices, FILE* fbDados){
    int codigo;

    printf("Imprimir Produto\n");
    
    imprimir_inOrdem(fbIndices, fbDados);
    
    printf("Digite o codigo do produto: "); scanf("%d%*c", &codigo);

    imprimirProduto_aux(fbIndices, fbDados, codigo);
}

//Descrição: Função auxiliar para imprimir as informações de um produto a partir de seu código
//Entrada: Ponteiros para os arquivos de índices e dados, e o código do produto
//Saida: void
//Pré-condição: Os arquivos de índices e dados devem existir e estar abertos, o código do produto deve ser válido
//Pós-condição: As informações do produto são impressas na tela
void imprimirProduto_aux (FILE* fbIndices, FILE* fbDados, int chave){
    Cabecalho_Indices* cabIndices = lerCabecalhoIndices(fbIndices);
    int posChave;
    int posNo = buscarNo(fbIndices, cabIndices->posRaiz, &posChave, chave); free(cabIndices);

    if(posNo != -1){//se árvore não for vazia e posicao não for inexistente
        ArvoreB* no = lerArvoreB(fbIndices, posNo);
        Produto* p = lerDados(fbDados, no->ptDados[posChave]); free(no);

        printf("\n%-12s%.3d\n", "Codigo: ", p->codigo);
        printf("%-12s%s\n", "Nome: ", p->nome);
        printf("%-12s%s\n", "Marca: ", p->marca);
        printf("%-12s%s\n", "Categoria: ", p->categoria);
        printf("%-12s%s%.2f\n", "Preco: ", "R$ ", p->preco);
        printf("%-12s%d\n", "Estoque: ", p->estoque);

        free(p);
    }
    else
        printf("O codigo digitado nao existe\n");

}

//Descrição: Função para imprimir os produtos em ordem de código
//Entrada: Ponteiros para os arquivos de índices e dados
//Saida: void
//Pré-condição: Os arquivos de índices e dados devem existir e estar abertos
//Pós-condição: Os produtos são impressos em ordem de código na tela
void imprimir_inOrdem(FILE* fbIndices, FILE* fbDados){
    Cabecalho_Indices* cab = lerCabecalhoIndices(fbIndices);

    printf("Lista de produtod (In-ordem)\n");
    
    if(cab->posRaiz == -1)
        printf("Nao ha produtos\n");
    else
        printf("\n%-11s%-55s\n", "Codigo", "Nome");

    imprimir_inOrder_rec(fbIndices, fbDados, cab->posRaiz);

    free(cab);
}

//Descrição: Função recursiva para imprimir os produtos em ordem de código
//Entrada: Ponteiros para os arquivos de índices e dados, e a posição atual na árvore
//Saida: void
//Pré-condição: Os arquivos de índices e dados devem existir e estar abertos
//Pós-condição: Os produtos são impressos em ordem de código na tela
void imprimir_inOrder_rec(FILE* fbIndices, FILE* fbDados, int pos){
    if(pos != -1){
        ArvoreB* no = lerArvoreB(fbIndices, pos);
        int i;

        for(i = 0; i < no->nChaves; i++){                
            imprimir_inOrder_rec(fbIndices, fbDados, no->filhos[i]);

            Produto* p = lerDados(fbDados, no->ptDados[i]);

            printf("%-10.3d %-55s\n", p->codigo, p->nome); free(p);
        }
        imprimir_inOrder_rec(fbIndices, fbDados, no->filhos[i]);

        free(no);
    }
}

//Descrição: Função para imprimir a árvore B representando a estrutura de índices
//Entrada: Ponteiro para o arquivo de índices
//Saida: void
//Pré-condição: O arquivo de índices deve existir e estar aberto
//Pós-condição: A árvore B é impressa na tela
void imprimirArvoreB(FILE* fbIndices){
    Cabecalho_Indices* cabIndices = lerCabecalhoIndices(fbIndices);
    Lista* l = NULL;//inicialização padrão de lista
    int alturaNo = 0, indiceNo = 0;

    printf("Arvore B\n");

    //verificação feita apenas para a estética da interface do programa
    if(cabIndices->posRaiz == -1)
        printf("Nao ha produtos\n");

    l = percorrerArvore(fbIndices, l, cabIndices->posRaiz, alturaNo, indiceNo);//passa a arvore para uma lista encadeada, ordenada pela altura do nó
    imprimirArvore_aux(l);//imprime no formato de árvore binária

    free(cabIndices);
    liberarLista(l);
}

//Descrição: Função recursiva para percorrer a árvore B e montar uma lista ordenada pela altura do nó
//Entrada: Ponteiros para os arquivos de índices e dados, uma lista encadeada, a posição atual na árvore, a altura do nó atual e o índice do nó atual
//Saida: Lista encadeada ordenada pela altura do nó
//Pré-condição: O arquivo de índices deve existir e estar aberto
//Pós-condição: A lista encadeada é montada ordenadamente
Lista* percorrerArvore(FILE* fbIndices, Lista* l, int pos, int alturaNo, int indiceNo){
    if(pos != -1){
        ArvoreB* no = lerArvoreB(fbIndices,pos);
        
        int i;
        for(i = 0; i < no->nChaves; i++){
            l = inserirOrdenado(l, no->chaves[i], alturaNo, indiceNo);

            percorrerArvore(fbIndices, l, no->filhos[i], alturaNo+1, i);
        }
        percorrerArvore(fbIndices, l, no->filhos[i], alturaNo+1, i);

        free(no);
    }
    return l;
}

//Descrição: Função para inserir um código na lista encadeada de forma ordenada pela altura do nó
//Entrada: Uma lista encadeada, o código do produto, a altura do nó e o índice do nó
//Saida: Lista encadeada com o código inserido
//Pré-condição: -
//Pós-condição: O código é inserido na lista ordenadamente
Lista* inserirOrdenado(Lista* l, int codigo, int alturaNo, int indiceNo){
    if(l==NULL || l->alturaNo > alturaNo){
        Lista* aux = (Lista*)malloc(sizeof(Lista));
        
        aux->codigo = codigo;
        aux->alturaNo = alturaNo;
        aux->indiceNo = indiceNo;
        aux->prox = l;
        
        return aux;
    }
    else{
        l->prox = inserirOrdenado(l->prox, codigo, alturaNo, indiceNo);
        
        return l;
    }
}

//Descrição: Função para imprimir a lista encadeada de forma a representar a árvore B de índices
//Entrada: Ponteiro para a lista encadeada
//Saida: void
//Pré-condição: -
//Pós-condição: A árvore B é impressa na tela
void imprimirArvore_aux(Lista *l){
    if(l != NULL){
        Lista* aux = l;
        int indiceAtual = l->indiceNo, alturaAtual = l->alturaNo;

        printf("[");
        while(aux != NULL){
            if(aux->prox != NULL){
                if (aux->prox->alturaNo != alturaAtual){//ao mudar de nivel, se pula uma linha
                    printf("%d]\n\n[", aux->codigo);

                    aux = aux->prox;
                    alturaAtual = aux->alturaNo;
                    indiceAtual = aux->indiceNo;
                }
                if (aux->prox->indiceNo != indiceAtual){//ao mudar o indexador do filho, é aberto um novo nó
                    printf("%d] [",aux->codigo);

                    aux = aux->prox;
                    indiceAtual = aux->indiceNo;
                }
            }
            if (aux->prox  == NULL) //ultimo
                printf("%d]\n", aux->codigo);
            else //imprime normalmente
                printf("%d,", aux->codigo);
            
            aux = aux->prox;
        }
    }
}

//Descrição: Função para liberar a memória alocada pela lista encadeada
//Entrada: Ponteiro para a lista encadeada
//Saida: void
//Pré-condição: -
//Pós-condição: A memória alocada pela lista é liberada
void liberarLista(Lista *l){
    if(l != NULL){
        liberarLista(l->prox); free(l);
    }
}

//Descrição: Função para imprimir a lista encadeada de nós livres no arquivo de índices
//Entrada: Ponteiro para o arquivo de índices
//Saida: void
//Pré-condição: O arquivo de índices deve existir e estar aberto
//Pós-condição: A lista de nós livres é impressa na tela
void imprimirListaLivre_arqIndices(FILE* fbIndices){
    Cabecalho_Indices* cabIndices = lerCabecalhoIndices(fbIndices);
    int posLivre = cabIndices->posLivre; free(cabIndices);

    printf("Lista de nos livres(Index)\n");

    if(posLivre == -1)
    printf("Nao ha nos livres no arquivo de indices\n");

    imprimirListaLivre_arqIndices_aux(fbIndices, posLivre);
}

//Descrição: Função recursiva para imprimir a lista encadeada de nós livres no arquivo de índices
//Entrada: Ponteiro para o arquivo de índices e a posição atual
//Saida: void
//Pré-condição: O arquivo de índices deve existir e estar aberto
//Pós-condição: A lista de nós livres é impressa na tela
void imprimirListaLivre_arqIndices_aux(FILE* fbIndices, int pos){
    if(pos != -1){
        ArvoreB* no = lerArvoreB(fbIndices, pos);
        int prox = no->filhos[0]; free(no);
        
        printf("-> [%.3d]\n", pos);
        
        imprimirListaLivre_arqIndices_aux(fbIndices, prox);
    }
}

//Descrição: Função para imprimir a lista encadeada de nós livres no arquivo de dados
//Entrada: Ponteiro para o arquivo de dados
//Saida: void
//Pré-condição: O arquivo de dados deve existir e estar aberto
//Pós-condição: A lista de nós livres é impressa na tela
void imprimirListaLivre_arqDados(FILE* fbDados){
    Cabecalho_Dados* cabDados = lerCabecalhoDados(fbDados);
    int posLivre = cabDados->posLivre; free(cabDados);

    printf("Lista de nos livres (Dados)\n");

    if(posLivre == -1)
        printf("Nao ha nos livres no arquivo de dados\n");

    imprimirListaLivre_arqDados_aux(fbDados, posLivre);
}

//Descrição: Função recursiva para imprimir a lista encadeada de nós livres no arquivo de dados
//Entrada: Ponteiro para o arquivo de dados e a posição atual
//Saida: void
//Pré-condição: O arquivo de dados deve existir e estar aberto
//Pós-condição: A lista de nós livres é impressa na tela
void imprimirListaLivre_arqDados_aux(FILE* fbDados, int pos){
    if(pos  != -1){
        Produto* p = lerDados(fbDados, pos);
        int prox = p->codigo;
        
        printf("[%.3d]\n",pos);
        
        imprimirListaLivre_arqDados_aux(fbDados, prox);
    }
}