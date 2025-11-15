#include <stdio.h>
#include <stdlib.h>

// variaveis globais para evitar criar uma copia toda vez que funcao recursiva rodar
int resolvido = 0;
int **matriz;
int **visitado;
int pContainer;
int linhas;
int colunas;

// Funcao que vai descobrir tudo que pertence a uma ilha
int explorar(int i, int j);

// funcao que encontra a combinacao de profundidades que preencham o conteiner
void encontrarCombinacao(int alvo, int profundidades[], int qtdIlhas, int indice, int solucao[], int tamanhoSolucao); 

// printa as ilhas de lixo que preenchem o container completamente
void imprimirSolucao(int solucao[], int tamanho);

int main(int argc, char *argv[])
{
    if (argc < 5) {
        return 1;
    }

    pContainer = atoi(argv[1]);
    linhas = atoi(argv[2]);
    colunas = atoi(argv[3]);
	
	FILE *arquivo;
    arquivo = fopen("arquivo.txt", "r");

    if (arquivo == NULL) {
        return 1;
    }

    // Alocar dinamicamente as matrizes
    matriz = (int **)malloc(linhas * sizeof(int *));
    visitado = (int **)malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *)malloc(colunas * sizeof(int));
        visitado[i] = (int *)malloc(colunas * sizeof(int));

        // Ler a matriz do arquivo
        for (int j = 0; j < colunas; j++) {
            fscanf(arquivo, "%d", &matriz[i][j]);
            visitado[i][j] = 0;
        }
    }

    fclose(arquivo);

    int qtdIlhas = 0;
    int *profundidades = (int *)malloc((((linhas * colunas)/2)+1) * sizeof(int)); // tamanho máximo possível

    // Econtra as ilhas e marca onde ja foi visitado
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] && !visitado[i][j] ) {
                int soma = (explorar(i, j)/6);
                profundidades[qtdIlhas] = soma < 1? 1: soma;
                qtdIlhas++;
            }
        }
    }
    
    printf("%d\n", qtdIlhas);
    
    for (int k = 0; k < qtdIlhas; k++) {
        printf("%d ", profundidades[k]);
    }
    
    printf("\n");

    int *ilhasSolucao = (int *)malloc(qtdIlhas* sizeof(int));
    encontrarCombinacao(pContainer, profundidades, qtdIlhas, 0, ilhasSolucao, 0);

    if (!resolvido) {
        perror("Nao ha resposta valida!\n");
    }
    
    // Liberar memória
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
        free(visitado[i]);
    }
    free(matriz);
    free(visitado);
    free(profundidades);
    free(ilhasSolucao);
    resolvido = 0;
    return 0;
}

int explorar(int i, int j) 
{
    // Retorna caso a posicao a ser vetificada estiver fora da matriz
    if (i < 0 || i >= linhas || j < 0 || j >= colunas) return 0;

    // Retorna se for mar ou ja foi visitado
    if (!matriz[i][j] || visitado[i][j]) return 0;

    visitado[i][j] = 1;
    int profundidade = matriz[i][j];

    profundidade += explorar(i + 1, j); // baixo
    profundidade += explorar(i - 1, j); // cima
    profundidade += explorar(i, j + 1); // esquerda
    profundidade += explorar(i, j - 1); // direita

    return profundidade;
}

void encontrarCombinacao(int alvo, int profundidades[], int qtdIlhas, int indice, int solucao[], int tamanhoSolucao)
{
    // Retorna imediatamente caso ja exista uma solucao
    if (resolvido) return;

    if (!alvo) {
        resolvido = 1;
        imprimirSolucao(solucao, tamanhoSolucao);
        return;
    }

    // Retorna se nao tiver mais ilhas para testar ou ultrapassou o espaco do container
    if (indice == qtdIlhas || alvo < 0) return;

    // Testa colocando a ilha na solucao
    solucao[tamanhoSolucao] = profundidades[indice];
    encontrarCombinacao(alvo - profundidades[indice], profundidades, qtdIlhas, indice + 1, solucao, tamanhoSolucao + 1);

    if (resolvido) return;

    // Testa sem colocar a ilha na solucao
    encontrarCombinacao(alvo, profundidades, qtdIlhas, indice + 1, solucao, tamanhoSolucao);
}

void imprimirSolucao(int solucao[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d", solucao[i]);
        if (i < tamanho - 1) {
            printf(" ");
        }
    }
}