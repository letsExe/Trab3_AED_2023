#include <stdio.h>
#include <stdlib.h>

#include "crud.h"
#include "imprimir.h"
#include "interface.h"
#include "lote.h"

    FILE* inicilizarArqIndices(char* filename){
        FILE* fb = fopen(filename, "r+b");//tenta abrir o arquivo binário, caso ele exista
        //initializarArvore(fb);//se inicializa o cabeçalho

        if(fb == NULL){//caso ele não exista, é criado um novo
            fb = fopen(filename, "w+b");
            initializarArvore(fb);//se inicializa o cabeçalho
        }

        return fb;
    }

    FILE* inicilizarArqDados(char* filename){
        FILE* fb = fopen(filename, "r+b");//tenta abrir o arquivo binário, caso ele exista
        //inicilizarDados(fb);//se inicializa o cabeçalho

        if(fb == NULL){//caso ele não exista, é criado um novo
            fb = fopen(filename, "w+b");
            inicilizarDados(fb);//se inicializa o cabeçalho
        }

        return fb;
    }

    int main(){

        FILE* fbIndices = inicilizarArqIndices("indices.bin");
        FILE* fbDados = inicilizarArqDados("dados.bin");

        welcome();

        int op1 = 0;
        do{
            menuDeOpcoes(&op1);
            if(op1 == 1){//produtos
                int op2 = 0;
                do{    
                    menuCrud(&op2);
                    if(op2==1){//cadastrar novo produto
                        cadastrarProduto(fbIndices, fbDados);
                        
                    }
                    if(op2==2){//remover produto
                        removerProduto(fbIndices, fbDados);
                        
                    }
                    if(op2==3){//alterar valor de um prooduto
                        atualizarPreco(fbIndices, fbDados);
                        
                    }
                    if(op2==4){//alterar estoque de um prooduto
                        atualizarEstoque(fbIndices, fbDados);
                        
                    }
                }while(op2 != 0);
            }
            if(op1 == 2){//imprimir informacoes
                int op3 = 0;
                do{
                    menuImprimir(&op3);
                    if(op3==1){//imprimir informacoes sobre um produto
                        imprimirProduto(fbIndices, fbDados);
                        
                    }
                    if(op3==2){//imprimir lista de produtos inOrdem
                        imprimir_inOrdem(fbIndices, fbDados);
                        
                    }
                    if(op3==3){//imprimir produtos em formato de arvore binaria
                        imprimirArvoreB(fbIndices);
                        
                    }
                    if(op3==4){//imprimir lista de nos livres (index)
                        imprimirListaLivre_arqIndices(fbIndices);
                        
                    }
                    if(op3==5){//imprimir lista de nos livres (data)
                        imprimirListaLivre_arqDados(fbDados);
                        
                    }
                }while(op3 != 0);
            }
            if(op1 == 3){//realizar operacoes em lote
                operacaoLote(fbIndices, fbDados);
                
            }
            if(op1 == 4){//apagar arquivo binario
                fbIndices = fopen("indices.bin", "w+b");
                initializarArvore(fbIndices);
                
                fbDados = fopen("dados.bin", "w+b");
                inicilizarDados(fbDados);
            }
        }while(op1 != 0);

        fclose(fbIndices);
        fclose(fbDados); 

        return 0;
    }