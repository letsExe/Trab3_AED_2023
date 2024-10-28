#include <stdio.h>
#include <string.h>
#include <stdlib.h>  

#include "lote.h"
#include "crud.h"

//Descricao: faz a leitura do caminho do arquivo texto e chama a função ler_arq_texto que faz a leitura do conteúdo do arquivo texto
//Entrada:  ponteiro não nulo para o arquivo binário
//Saida:    -
//Pre-condicao: ponteiro não nulo para o arquivo binário
//Pos-condicao: arquivo binario modificado, caso os códigos lidos do arq. texto sejam válidas
void operacaoLote(FILE* fbIndices, FILE* fbDados) {
    FILE* fr; char filepath[100];

    //não permite sair da iteração até um caminho válido de arquivo texto ser digitado
    do {
        printf("Digite o caminho do arquivo: "); 
        scanf("%[^\n]%*c", filepath);
        
        fr = fopen(filepath, "r");
    } while(fr == NULL);

    lerArquivoTexto(fbIndices, fbDados, fr); fclose(fr);

    printf("Arquivo lido com sucesso\n");
}

//Descricao: faz a leitura do conteúdo do arquivo texto, e chama as funções (inserir, remover e/ou alterar) de  acordo com a operação lida ('I','R','A')
//Entrada:  ponteiros não nulos para arq. binário e arq. texto
//Saida:    -
//Pre-condicao: ponteiros não nulos para arq. binário e arq. texto
//Pos-condicao: arquivo binario modificado, caso os códigos lidos do arq. texto sejam válidas
void lerArquivoTexto(FILE* fbIndices, FILE* fbDados, FILE *fr){
    char op;

    while(fscanf(fr, "%c;", &op) != EOF){
        if(op == 'I'){//inserção em lote
            inserirLote(fbIndices, fbDados, fr);
        }
        if(op == 'A'){//alterar valor e/ou estoque
            alterarLote(fbIndices, fbDados, fr);
        }
        if(op == 'R'){//remover produto
            removerLote(fbIndices, fbDados, fr);
        }
    }
}

//Descricao: caso a operação lida seja 'I', é chamada essa função. ela faz a leitura do conteúdo do arquivo texto para uma estrutura árvore auxiliar, e então chama a função inserirProduto que é responsável pos inserir essa estrutura auxiliar dentro do arquivo binário
//Entrada:  ponteiro não nulo para o arquivo binário e para o arquivo texto
//Saida:    -
//Pre-condicao: ponteiro não nulo para o arquivo binário e para o arquivo texto. função de inserir já criada.
//Pos-condicao: arquivo binário modificado caso o código do produto ainda não exista na árvore
void inserirLote(FILE* fbIndices, FILE* fbDados, FILE* fr){
    Produto* p=(Produto*)malloc(sizeof(Produto));
    Cabecalho_Indices* cabIndices = lerCabecalhoIndices(fbIndices);
    Chave_Auxiliar chaveAuxiliar;
    char preco[100] = ""; float v1, v2;

    fscanf(fr, "%d;", &chaveAuxiliar.codigo); p->codigo=chaveAuxiliar.codigo;
    fscanf(fr, "%[^;]%*c", p->nome);
    fscanf(fr, "%[^;]%*c", p->marca);
    fscanf(fr, "%[^;]%*c", p->categoria);
    fscanf(fr, "%d;", &p->estoque);
    fscanf(fr, "%[^\n]%*c", preco);
    
    v1 = atoi(preco);
    v2 = (strpbrk(preco, ",") == NULL) ? 0 : atoi(strpbrk(preco, ",") + 1);
    p->preco = v1+(v2/100.0);
    chaveAuxiliar.ptDados = inserirArquivoBinDados(fbDados, p);
    
    int posChave;
    if (buscarNo(fbIndices, cabIndices->posRaiz, &posChave, chaveAuxiliar.codigo) == -1)
        inserirNo(fbIndices, fbDados, chaveAuxiliar);

    free(p);
    free(cabIndices);
}

//Descricao: caso a operação lida seja 'R', é chamada essa função. ela faz a leitura do conteúdo do arquivo texto: o código do produto a ser removido, e então chama a função removerNo que é responsável pos remover essa nó do arquivo binário, caso esse código exista.     
//Entrada:  ponteiro não nulo para o arquivo binário e para o arquivo texto
//Saida:    -
//Pre-condicao: ponteiro não nulo para o arquivo binário e para o arquivo texto
//Pos-condicao: arquivo binário modificado caso o código do produto exista na árvore
void removerLote(FILE* fbIndices, FILE* fbDados, FILE *fr){
    Cabecalho_Indices* cabIndices = lerCabecalhoIndices(fbIndices);
    Chave_Auxiliar chaveAux; int posRaiz = cabIndices->posRaiz;

    fscanf(fr, "%d\n", &chaveAux.codigo);

    int posChave;
    int posNo = buscarNo(fbIndices, cabIndices->posRaiz, &posChave, chaveAux.codigo);
    if (posNo != -1) {
        ArvoreB* no = lerArvoreB(fbIndices, posNo);
        chaveAux.ptDados = no->ptDados[posChave]; free(no);
        removerProduto_aux(fbIndices, fbDados, posRaiz, chaveAux);
    }

    free(cabIndices);
}

//Descricao: caso a operação lida seja 'A', é chamada essa função. ela é responsável por alterar a valor de um protudo já existente, caso o formato da linha no arq. texto seja "A;cod;;valor,valor", ou alterar
//              o estoque, caso o formato seja "A;cod;estoque;", ou ambos, caso o formato seja "A;cod;estoque;valor,valor"
//              a função lê todo conteúdo da linha a partir de "cod;" no formato de uma string token, para sua melhor
//              manipulação, então pode chamar as funções ler_preco e/ou ler_estoque que fazem a conversão da string
//              para seus devídos formatos e então chama as funções responsáveis por alterar os valores no arquivo binario
//Entrada:  ponteiro não nulo para o arquivo binário e para o arquivo texto
//Saida:    -
//Pre-condicao: ponteiro não nulo para o arquivo binário e para o arquivo texto
//Pos-condicao: arquivo binário alterado, caso os códigos lidos sejam válidos
void alterarLote(FILE *fbIndice, FILE* fbDados, FILE *fr){
    char token[50]; int codigo;
    int i = 0;

    fscanf(fr, "%d;", &codigo);
    //a partir de "cod;", o restante do texto é transformado em string 'token' para sua melhor manipulação
    while(fscanf(fr, "%c", &token[i]) != EOF) {
        if(token[i] == '\n')
            break;
        
        i++;
    }
    token[i] = '\0';

    if(token[0] == ';'){ //não há estoque a ser lido, apenas valor
        float preco = lerPreco(token, 1);//começa a ler a partir de token[1]
        atualizarPreco_aux(fbIndice, fbDados, codigo, preco);
    }
    else{
        int n;//guarda até onde foi percorrida a string 'token[n]'
        int estoque = lerEstoque(token, &n);//-n- é alterado conforme se percorre por token para encontrar o valor de estoque
        atualizarEstoque_aux(fbIndice, fbDados, codigo, estoque);

        if(strlen(token) != n){//se token não é apenas "estoque;"
            float preco = lerPreco(token, n);//começa a ler a partir de ';' -> token[n]
            atualizarPreco_aux(fbIndice, fbDados, codigo, preco);
        }
    }
}

//Descricao: função responsável por ler o novo valor no formato 00,00 de dentro da string token, que contem a linha do arq. texto a partir de "A;cod;". a leitura começa a partir de token[n] 
//Entrada:  token, que contem a linha do arq. texto a partir de "A;cod;", e n, o inteiro de onde começa a leitura de token
//Saida:    novo valor do produto, obtido a partir de token
//Pre-condicao: chamada pela função alterar_em_lote
//Pos-condicao: -
int lerEstoque(char* token, int* n){
    char estoque[6];

    for(*n = 0; token[*n-1] != ';'; estoque[*n] = token[*n], *n = *n + 1);//leitura do novo estoque
    estoque[*n-1] = '\0';
    
    return atoi(estoque);//transforma a string em inteiro
}

//Descricao: função responsável por ler o valor int de estoque a partir da string token. ele passa pela string incrementando a variável n, que depois servirá para a leitura do float valor, caso ele exista
//Entrada:  token, que contem a linha do arq. texto a partir de "A;cod;".
//Saida:    valor do novo estoque do produto, obtivo a partir de token.
//Pre-condicao: chamada pela função alterar_em_lote
//Pos-condicao: n incrementada, tendo lido o valor do estoque do produto
float lerPreco(char* token, int n){
    int j, k; float f1, f2; char v1[6], v2[3];

    //leitura do valor antes da vírgula:
    for(j = 0; token[n] != ','; v1[j] = token[n], n++, j++);
    v1[j] = '\0';
    f1 = atof(v1);//transforma a string em float

    //leitura do valor apos a virgula:
    for(k = 0; n < strlen(token); v2[k] = token[n+1], n++, k++);
    v2[k] = '\0';
    f2 = atof(v2);//transforma a string em float

    return f1+(f2/100);
}