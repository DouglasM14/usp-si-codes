#define FALSE 0
#define TRUE 1

#define PILHA

typedef int Boolean;
typedef int Elemento;

typedef struct {

	Elemento * a;
	int topo;
	int capacidade;

} Pilha;

Pilha * cria_pilha(int capacidade);
void destroi(Pilha * pilha);
void imprime(Pilha * pilha);
int tamanho(Pilha * pilha);
Boolean push(Pilha * pilha, Elemento e);
Boolean pop(Pilha * pilha, Elemento * e);

