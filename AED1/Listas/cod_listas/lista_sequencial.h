#define FALSE 0
#define TRUE 1
#define TAMANHO_MAXIMO 100000

typedef int Boolean;
typedef int Elemento;

typedef struct {

	Elemento a[TAMANHO_MAXIMO];
	int livre;

} ListaSequencial;

ListaSequencial * cria_lista();
void destroi_lista(ListaSequencial * lista);
int tamanho(ListaSequencial * lista);
void imprime(ListaSequencial * lista);
int busca(ListaSequencial * lista, Elemento e);
Boolean insere(ListaSequencial * lista, Elemento e, int indice);
Boolean remove_elemento(ListaSequencial * lista, Elemento e);

