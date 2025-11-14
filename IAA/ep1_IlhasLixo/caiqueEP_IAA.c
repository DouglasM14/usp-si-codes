#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define AREA 6 // base do container = 2x3 = 6 (m^2)
#define MOVES 4

// armazena um valor (qtd. de lixo) e a qual ilha esse lixo pertence
typedef struct {
  int value;
  int island;
} Cell;

// armazena a matriz, suas dimensoes, qtd. de ilhas e a soma do lixo em cada ilha
typedef struct {
  Cell **matrix;
  int rows;
  int cols;
  int *islands;
  int countIslands;
  int *container;
  int containerSize;
  int capacidade;
} Contexto;

// armazena um par ordenado (x, y) e tambem um iterador k
typedef struct {
  int x, y;
} Coords;

Coords moves[] = {
  {-1, 0},
  {0, 1},
  {1, 0},
  {0, 1},
};

void calc_deepth(Contexto *ctx) {
  for (int i = 0; i < ctx->countIslands; i++) {
    float deepth = ctx->islands[i]/6.0;

    if (deepth < 0) ctx->islands[i] = -1;
    else if (deepth > 0 && deepth < 1) ctx->islands[i] = 1; // entre 0 e 1, arredonda para cima (nesse caso, para 1)
    else ctx->islands[i] = (int) deepth; // qualquer valor acima de 1, deixa somente a parte inteira
  }
}

void explora(Contexto *ctx, Coords coords, int k) {
  int x = coords.x, y = coords.y;

  ctx->islands[k-1] += ctx->matrix[y][x].value; // e necessario k-1 pois, ao chamar explora, incremetamos k
  ctx->matrix[y][x].island = k;

  for (int i = 0; i < MOVES; i++) {
    int newX = x + moves[i].x;
    int newY = y + moves[i].y;

    if (newX >= 0 && newX < ctx->cols && newY >= 0 && newY < ctx->rows) {
      if (ctx->matrix[newY][newX].value != 0 && ctx->matrix[newY][newX].island == 0) explora(ctx, (Coords){newX, newY}, k);
    }
  }
}

void percorre(Contexto *ctx) {
  int k = 0; // representa o numero da ilha que estamos

  for (int i = 0; i < ctx->rows; i++) {
    for (int j = 0; j < ctx->cols; j++) {
      // se .value != 0 (nao for mar) e .island == 0 (ainda nao foi explorado):
      if (ctx->matrix[i][j].value != 0 && ctx->matrix[i][j].island == 0) {
        explora(ctx, (Coords){j, i}, ++k); // iremos explorar essa celula, incrementando k (indo pra proxima ilha)
      }
    }
  }

  ctx->countIslands = k;
}

int tenta(Contexto *ctx, int start, int indice, int cap) {
  if (cap == 0) return TRUE; // se chegou na capacidade 0, é porque coube tudo

  // começa a iteracao, desde start ate o fim do vetor islands
  for (int i = start; i < ctx->countIslands; i++) {
    // se o elemento atual couber no container:
    if (ctx->islands[i] <= cap) {
      ctx->container[indice] = ctx->islands[i]; // coloca o elemento no container, no indice atual
      ctx->containerSize = indice+1; // aumenta o tamanho do container

      if (tenta(ctx, i+1, indice+1, cap-ctx->islands[i])) return TRUE; // tenta colocar o PROXIMO elemento

      ctx->container[indice] = 0; // se nao consegue, da um passo atras e apaga o elemento que acabou de tentar por
      ctx->containerSize = indice; // volta o tamanho do container para o que estava antes
    }

  }

  return FALSE;
}

void start_matrix(Contexto *ctx) {
  // para cada par [i][j], salva na matriz
  for (int i = 0; i < ctx->rows; i++) {
    for (int j = 0; j < ctx->cols; j++) {
      scanf("%d", &ctx->matrix[i][j].value);
      ctx->matrix[i][j].island = 0;
    }
  }
}
void free_ctx(Contexto *ctx) {
  // libera cada linha da matriz
  for (int i = 0; i < ctx->rows; i++) {
      free(ctx->matrix[i]);
  }

  free(ctx->matrix); // depois libera a matriz
  free(ctx); // e por ultimo libera o ponteiro que armazenava tudo
}

// FUNCOES PARA PRINTAR
void print_vec(int * vec, int size, int hasSpace) {
  for (int i = 0; i < size; i++) {
    printf("%d", vec[i]);
    if (i != size-1) printf(" ");
  }
  if (hasSpace) printf("\n");
}
void print_value(Cell cell) { printf("%d ", cell.value); }
void print_island(Cell cell) { printf("%d ", cell.island); }
void print_ctx(Contexto *ctx, void (*printer)(Cell)) {
  for (int i = 0; i < ctx->rows; i++) {
    for (int j = 0; j < ctx->cols; j++) {
      printer(ctx->matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  // 'argc' representa o numero de elemento que estao em 'argv'
  // 'argv' é um vetor com todos os "parametros" enviados junto ao rodar o arquivo pelo terminal
  // se há menos de 5 (cinco) argumentos passados (o primeiro e sempre o caminho para o arquivo atual), manda um erro
  if (argc < 5) {
    printf("Nao ha argumento suficientes, tente novamente seguindo o seguinte padrao:\n");
    printf("./ARQUIVO.exe <profundidade_container> <linhas_da_matrix> <colunas_da_matrix> exemplo.txt\n");
    return 1;
  }

  FILE *f = freopen(argv[4], "r", stdin); // redireciona o que deveria ter vindo do stdin para um arquivo, cujo nome e extensao estao em argv[4]
  // freopen("saida.out", "w", stdout);

  if (f == NULL) {
    printf("Erro ao abrir arquivo de entrada. Verifique se o caminho e a extensao do arquivo foram escritos corretamente.");
    return 1;
  }
  
  Contexto *ctx = (Contexto*) malloc(sizeof(Contexto));  // armazena a matrix, dimensoes da matrix e uma outra matrix de referencia
  ctx->capacidade = atoi(argv[1]); // capacidade total do container, onde devera caber com exatidao uma determinada combinacao de lixo das islands

  // funcao atoi() converte um tipo string para um tipo int
  ctx->rows = atoi(argv[2]); // linhas da matrix
  ctx->cols = atoi(argv[3]); // colunas da matrix
  
  // cria dinamicamente a matrix que armazenara o que esta vindo do ARQUIVO
  ctx->matrix = (Cell**) malloc(ctx->rows*sizeof(Cell*));
  for (int i = 0; i < ctx->rows; i++) ctx->matrix[i] = (Cell*) malloc(ctx->cols*sizeof(Cell));

  ctx->islands = (int*) calloc((ctx->rows * ctx->cols), sizeof(int)); // aloca dinamicamente espaço onde sera armazenado a qtd. de lixo de cada linha
  ctx->countIslands = 0; // comeca com 0 (zero) ilhas

  start_matrix(ctx); // inicia a matriz, recebendo os devidos inputs (scanf's) nas respectivas celulas
  percorre(ctx); // comeca a percorrer a matriz, descobre quantas ilhas tem e ja coloca a soma do lixo de cada i-esima ilha dentro de ctx->islands[i]
  calc_deepth(ctx); // faz o calculo da profundidade de cada container, dividindo o valor de ctx->islands[i] por AREA

  // print_ctx(ctx, print_island);
  
  ctx->container = (int*) calloc(ctx->countIslands, sizeof(int)); // aloca dinamicamente espaco para o container com o mesmo tamanho alocado para caber as ilhas
  ctx->containerSize = 0; // inicializa o tamanho do vetor
  
  printf("%d\n", ctx->countIslands);
  print_vec(ctx->islands, ctx->countIslands, 1);
  if (tenta(ctx, 0, 0, ctx->capacidade)) print_vec(ctx->container, ctx->containerSize, 0);
  else printf("Nao ha resposta valida!");

  free_ctx(ctx);
  fclose(stdin);

  return 0;
}