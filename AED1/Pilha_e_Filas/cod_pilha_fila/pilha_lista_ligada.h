#define FALSE 0
#define TRUE 1

#define PILHA
#define LISTA_LIGADA

typedef int Boolean;
typedef int Elemento;

typedef struct _no_ {

	Elemento valor;
	struct _no_ * proximo;

} No;

typedef struct {
	
	No * primeiro;
	int tamanho;

} Pilha;

Pilha * cria_pilha();
void destroi(Pilha * pilha);
void imprime(Pilha * pilha);
int tamanho(Pilha * pilha);
Boolean push(Pilha * pilha, Elemento e);
Boolean pop(Pilha * pilha, Elemento * e);
