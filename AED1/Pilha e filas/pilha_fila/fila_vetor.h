#define FALSE 0
#define TRUE 1

#define FILA

typedef int Boolean;
typedef int Elemento;

typedef struct {

	Elemento * a;
	int ini;
	int fim;
	int capacidade;

} Fila;

Fila * cria_fila(int capacidade);
void destroi(Fila * fila);
void imprime(Fila * fila);
int tamanho(Fila * fila);
Boolean adiciona_final(Fila * fila, Elemento e);
Boolean remove_inicio(Fila * fila, Elemento * e);
