#define FALSE 0
#define TRUE 1

#define INDEFINIDO -1
#define ESQUERDO 0
#define DIREITO 1

typedef int Elemento;
typedef int Boolean;

typedef struct _no_arvore_ {

	Elemento valor;
	struct _no_arvore_ * esq;
	struct _no_arvore_ * dir;

} No;

typedef struct {

	No * raiz;

} Arvore;

Arvore * cria_arvore();
void imprime(Arvore * arvore);

// Se a ideia é usar a árvore binária como uma árvore
// de "propsito geral", sem organizar os elementos
// pelos seus valores, use as funções abaixo:

No * busca(Arvore * arvore, Elemento e);
Boolean insere(Arvore * arvore, No * pai, Elemento e, int lado);
Boolean remove_no(Arvore * arvore, No * no);

// Já se o objetivo é usar a árvore binária como uma
// árvore binária de busca (ABB), em que os elementos
// são organizados por ordem de valor, use as seguintes
// funções:

No * busca_bin(Arvore * arvore, Elemento e);
Boolean insere_ord(Arvore * arvore, Elemento e);
Boolean remove_ord(Arvore * arvore, No * no);

////////////////////////////////////////////////////////////////////////////////

// funções auxiliares para exibição da árvore, fora
// do conjunto de operações elementares da estrutura.

void display(Arvore * arvore);
void debug_on();
void debug_off();


