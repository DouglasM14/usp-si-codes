#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int linhas, colunas;
    char nome_arquivo[100] = "arquivo.txt";
    FILE *arquivo;

    // Inicializa o gerador de números aleatórios com uma semente baseada no tempo atual
    // para garantir que os números sejam diferentes a cada execução.
    srand(time(NULL));

    // Solicita os dados ao usuário
    printf("Digite o numero de linhas da matriz: ");
    scanf("%d", &linhas);

    printf("Digite o numero de colunas da matriz: ");
    scanf("%d", &colunas);

    // printf("Digite o nome do arquivo de saida (ex: meu_teste.txt): ");
    // scanf("%s", nome_arquivo);

    // Tenta abrir o arquivo em modo de escrita ("w" - write)
    arquivo = fopen(nome_arquivo, "w");

    // Verifica se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return 1; // Encerra o programa com um código de erro
    }

    // Loop para percorrer cada linha da matriz
    // int lixo;
    for (int i = 0; i < linhas; i++) {
        // Loop para percorrer cada coluna da matriz
        for (int j = 0; j < colunas; j++) {
            int valor_celula;
            // if (lixo) {
            //     valor_celula = (rand() % 99) + 1;
            //     valor_celula = 1;
            //     lixo = 0;
            // } else {
            //     valor_celula = 0;
            //     lixo = 1;
            // }
            
            // Define a probabilidade de uma célula ser "lixo"
            // rand() % 3 == 0 significa aproximadamente 1/3 de chance
            if (rand() % 6 == 0) {
                // Se for "lixo", gera um valor entre 1 e 99
                valor_celula = (rand() % 99) + 1;
            } else {
                valor_celula = 0;
            }

            // Escreve o valor no arquivo, seguido de um espaço
            fprintf(arquivo, "%d ", valor_celula);
        }
        // Ao final de cada linha, pula para a próxima linha no arquivo
        fprintf(arquivo, "\n");
    }

    // Fecha o arquivo para salvar as alterações
    fclose(arquivo);

    printf("\nArquivo '%s' gerado com sucesso com uma matriz %dx%d!\n", nome_arquivo, linhas, colunas);

    return 0; // Sucesso
}