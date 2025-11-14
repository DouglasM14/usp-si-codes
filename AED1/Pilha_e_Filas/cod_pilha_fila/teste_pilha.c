#include <stdio.h>

//#include "pilha_vetor.h"
#include "pilha_lista_ligada.h"

int main(){

	int i;
	Elemento e;

#ifdef LISTA_LIGADA
	Pilha * pilha = cria_pilha();
#else 
	Pilha * pilha = cria_pilha(100);
#endif

	imprime(pilha);

	for(i = 0; i < 10; i++) {

		e = i * 10;

		push(pilha, e);
		imprime(pilha);
	}

	printf("-------------------------------------------------------------------------------------\n");

	while(pop(pilha, &e)){

		printf("Elemento removido: %2d\t\t\t", e);
		imprime(pilha);
	}

	return 0;
}
