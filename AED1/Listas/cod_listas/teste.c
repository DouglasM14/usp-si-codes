#include <stdio.h>

//#include "lista_sequencial.h"
//#include "lista_sequencial_dinamica.h"
#include "lista_sequencial_ordenada.h"

int main(){

	int x;

	ListaSequencial * lista = cria_lista(10000);

	imprime(lista);
	printf("------------------------------------------------------------------------------------\n");

	/*
	insere(lista, 3, 0);
	insere(lista, 1, 1);
	insere(lista, 5, 2);
	insere(lista, 4, 3);
	insere(lista, 2, 4);
	*/
	
	insere(lista, 3);
	insere(lista, 1);
	insere(lista, 5);
	insere(lista, 4);
	insere(lista, 2);

	imprime(lista);
	printf("tamanho da lista: %d\n", tamanho(lista));

	printf("------------------------------------------------------------------------------------\n");

	x = 1;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));
	
	x = 5;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 6;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	printf("------------------------------------------------------------------------------------\n");

	//insere(lista, 6, 2);
	insere(lista, 6);
	imprime(lista);
	printf("tamanho da lista: %d\n", tamanho(lista));

	printf("------------------------------------------------------------------------------------\n");

	x = 1;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 5;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 6;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	printf("------------------------------------------------------------------------------------\n");

	remove_elemento(lista, 6);
	remove_elemento(lista, 5);
	imprime(lista);
	printf("tamanho da lista: %d\n", tamanho(lista));

	printf("------------------------------------------------------------------------------------\n");

	x = 1;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 5;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 6;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	printf("------------------------------------------------------------------------------------\n");

	destroi_lista(lista);
	return 0;
}

