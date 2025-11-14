#define FALSE 0
#define TRUE 1

#define FILA
#define LISTA_LIGADA

typedef int Boolean;
typedef int Elemento;

typedef struct _no_ {

	Elemento valor;
	struct _no_ * proximo;

} No;

typedef struct {
	
	No * primeiro;
	No * ultimo;
	int tamanho;

} Fila;

Fila * cria_fila();
void destroi(Fila * fila);
void imprime(Fila * fila);
int tamanho(Fila * fila);
Boolean adiciona_final(Fila * fila, Elemento e);
Boolean remove_inicio(Fila * fila, Elemento * e);
