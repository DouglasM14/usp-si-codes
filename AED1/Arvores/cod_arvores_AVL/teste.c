#include <stdio.h>

#include "AVL.h"

int teste_AVL(){

	int i, x;
	
	int valores[] = { 40, 20, 70, 10, 30, 50, 90, 15, 29, 28, 27, 89, 88, 87};
	//int valores[] = { 6, 5, 4, 3, 2, 1 };

	//int valores[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }; 
	//int valores[] = { 15, 1, 2, 3, 4, 5, 6, 13, 8, 9, 10, 11, 12, 7, 14 }; 
	//int valores[] = { 3, 4, 5, 1, 2, 6, 13, 14, 15, 9, 10, 11, 12, 7, 8 }; 

	Arvore_AVL * arvore = cria_arvore();

	for(i = 0; i < sizeof(valores)/sizeof(int); i++){

		printf("Inserindo %d...\n", valores[i]);
		getchar();

		insere_AVL(arvore, valores[i]);
		imprime(arvore);
		display(arvore);
		getchar();
	}

	//debug_on();

	x = 50;
	printf("\nProcurando pelo valor %d...\n", x);
	printf("valor %d armazenado na árvore? %s\n\n", x, busca_AVL(arvore, x) ? "SIM" : "NÃO");
	
	x = 90;
	printf("Procurando pelo valor %d...\n", x);
	printf("valor %d armazenado na árvore? %s\n\n", x, busca_AVL(arvore, x) ? "SIM" : "NÃO");

	x = 30;
	printf("Procurando pelo valor %d...\n", x);
	printf("valor %d armazenado na árvore? %s\n\n", x, busca_AVL(arvore, x) ? "SIM" : "NÃO");

	debug_off();

	imprime(arvore);
	display(arvore);

	x = 40;
	printf("removendo valor %d...\n", x);
	getchar();
	remove_AVL(arvore, x);
	imprime(arvore);
	display(arvore);
	getchar();

	x = 30;
	printf("removendo valor %d...\n", x);
	getchar();
	remove_AVL(arvore, x);
	imprime(arvore);
	display(arvore);
	getchar();

	x = 50;
	printf("removendo valor %d...\n", x);
	getchar();
	remove_AVL(arvore, x);
	imprime(arvore);
	display(arvore);
	getchar();

	x = 88;
	printf("removendo valor %d...\n", x);
	getchar();
	remove_AVL(arvore, x);
	imprime(arvore);
	display(arvore);
	getchar();

	x = 89;
	printf("removendo valor %d...\n", x);
	getchar();
	remove_AVL(arvore, x);
	imprime(arvore);
	display(arvore);
	getchar();

	return 0;
}

int main(){

	return teste_AVL();
}

