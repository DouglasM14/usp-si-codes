#define FALSE 0
#define TRUE 1

typedef int Boolean;
typedef int Elemento;

typedef struct {

	Elemento * a;
	int livre;
	int capacidade;

} ListaSequencial;

ListaSequencial * cria_lista(int n);
void destroi_lista(ListaSequencial * lista);
int tamanho(ListaSequencial * lista);
void imprime(ListaSequencial * lista);
int busca(ListaSequencial * lista, Elemento e);
Boolean insere(ListaSequencial * lista, Elemento e, int indice);
Boolean remove_elemento(ListaSequencial * lista, Elemento e);
int valor_indice(ListaSequencial * lista, int indice);