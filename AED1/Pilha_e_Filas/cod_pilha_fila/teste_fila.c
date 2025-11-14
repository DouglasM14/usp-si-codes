#include <stdio.h>

//#include "fila_vetor.h"
#include "fila_lista_ligada.h"

int main(){

	int i;
	Elemento e;

#ifdef LISTA_LIGADA
	Fila * fila = cria_fila();
#else 
	Fila * fila = cria_fila(10);
#endif

	imprime(fila);

	for(i = 0; i < 10; i++) {

		e = i * 10;

		adiciona_final(fila, e);
		imprime(fila);
	}

	/*
	printf("-------------------------------------------------------------------------------------\n");

	while(remove_inicio(fila, &e)){

		printf("Elemento removido: %2d\t\t\t", e);
		imprime(fila);
	}
	*/

	printf("-------------------------------------------------------------------------------------\n");

	for(i = 0; i < 20; i++) {

		remove_inicio(fila, &e);
		adiciona_final(fila, e + 1);
		
		printf("Elemento removido: %2d\t\t\t", e);
		imprime(fila);
	}

	return 0;
}
