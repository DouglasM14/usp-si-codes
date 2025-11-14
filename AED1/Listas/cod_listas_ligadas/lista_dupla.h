#define FALSE 0
#define TRUE 1

#define LISTA_ORDENADA

typedef int Boolean;
typedef int Elemento;

typedef struct _no_ {

	Elemento valor;
	struct _no_ * proximo;
	struct _no_ * anterior;

} No;

typedef struct {

	int tamanho;	
	No * cabeca;

} ListaLigada;

ListaLigada * cria_lista();
void destroi_lista(ListaLigada * lista);
int tamanho(ListaLigada * lista);
void imprime(ListaLigada * lista);
int busca(ListaLigada * lista, Elemento e);
Boolean insere(ListaLigada * lista, Elemento e);
Boolean remove_elemento(ListaLigada * lista, Elemento e);
