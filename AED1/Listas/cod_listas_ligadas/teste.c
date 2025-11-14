#include <stdio.h>

//#include "lista_ligada.h"
//#include "lista_ligada_circular.h"
#include "lista_dupla.h"

int main(){

	int x;
	ListaLigada * lista = cria_lista();	

	imprime(lista);
	printf("------------------------------------------------------------------------------------\n");

#ifdef LISTA_ORDENADA
	insere(lista, 3);
	insere(lista, 1);
	insere(lista, 5);
	insere(lista, 4);
	insere(lista, 2);
#else
	insere(lista, 3, 0);
	insere(lista, 1, 1);
	insere(lista, 5, 2);
	insere(lista, 4, 3);
	insere(lista, 2, 4);
#endif

	imprime(lista);
	printf("tamanho da lista: %d\n", tamanho(lista));

	x = 1;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));
	
	x = 5;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 6;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	printf("------------------------------------------------------------------------------------\n");

#ifdef LISTA_ORDENADA
	insere(lista, 6);
#else
	insere(lista, 6, 2);
#endif

	imprime(lista);
	printf("tamanho da lista: %d\n", tamanho(lista));

	x = 1;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 5;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 6;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	printf("------------------------------------------------------------------------------------\n");

	remove_elemento(lista, 4);
	remove_elemento(lista, 5);
	imprime(lista);
	printf("tamanho da lista: %d\n", tamanho(lista));

	x = 1;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 5;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 6;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	printf("------------------------------------------------------------------------------------\n");

	for(x = 1; x <= 6; x++) {

		remove_elemento(lista, x);
		imprime(lista);
	}


	for(x = 9; x <= 14; x++) {

		insere(lista, (x % 6) + 1);
		imprime(lista);
	}
	
	printf("------------------------------------------------------------------------------------\n");

	destroi_lista(lista);
	return 0;
}

