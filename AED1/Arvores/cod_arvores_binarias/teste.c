#include <stdio.h>

#include "arvore_binaria.h"

int teste1(){

	int x;

	Arvore * arvore = cria_arvore();
	insere(arvore, NULL, 40, INDEFINIDO);
	insere(arvore, busca(arvore, 40), 20, ESQUERDO);
	insere(arvore, busca(arvore, 40), 70, DIREITO);
	insere(arvore, busca(arvore, 20), 10, ESQUERDO);
	insere(arvore, busca(arvore, 20), 30, DIREITO);
	insere(arvore, busca(arvore, 70), 50, ESQUERDO);
	insere(arvore, busca(arvore, 70), 80, DIREITO);
	insere(arvore, NULL, 15, INDEFINIDO);
	insere(arvore, busca(arvore, 15), 200, DIREITO);

	imprime(arvore);
	display(arvore);

	debug_on();

	x = 50;
	printf("\nProcurando pelo valor %d...\n", x);
	printf("valor %d armazenado na árvore? %s\n\n", x, busca(arvore, x) ? "SIM" : "NÃO");

	getchar();
	
	x = 60;
	printf("Procurando pelo valor %d...\n", x);
	printf("valor %d armazenado na árvore? %s\n\n", x, busca(arvore, x) ? "SIM" : "NÃO");

	getchar();

	x = 200;
	printf("Procurando pelo valor %d...\n", x);
	printf("valor %d armazenado na árvore? %s\n\n", x, busca(arvore, x) ? "SIM" : "NÃO");
	
	debug_off();
	
	imprime(arvore);
	display(arvore);

	x = 15;
	printf("removendo %d...\n", x); getchar();
	remove_no(arvore, busca(arvore, x));
	imprime(arvore);
	display(arvore);

	x = 30;
	printf("removendo %d...\n", x); getchar();
	remove_no(arvore, busca(arvore, x));
	imprime(arvore);
	display(arvore);

	x = 40;
	printf("removendo %d...\n", x); getchar();
	remove_no(arvore, busca(arvore, x));
	imprime(arvore);
	display(arvore);

	x = 200;
	printf("removendo %d...\n", x); getchar();
	remove_no(arvore, busca(arvore, x));
	imprime(arvore);
	display(arvore);
	
	return 0;
}

int teste2(){

	int i, x;
	
	int valores[] = { 40, 20, 70, 10, 30, 50, 80, 15, 200};

	Arvore * arvore = cria_arvore();

	for(i = 0; i < sizeof(valores)/sizeof(int); i++){

		insere_ord(arvore, valores[i]);
		imprime(arvore);
	}

	display(arvore);

	debug_on();

	x = 50;
	printf("\nProcurando pelo valor %d...\n", x);
	printf("valor %d armazenado na árvore? %s\n\n", x, busca_bin(arvore, x) ? "SIM" : "NÃO");
	
	x = 90;
	printf("Procurando pelo valor %d...\n", x);
	printf("valor %d armazenado na árvore? %s\n\n", x, busca_bin(arvore, x) ? "SIM" : "NÃO");

	x = 30;
	printf("Procurando pelo valor %d...\n", x);
	printf("valor %d armazenado na árvore? %s\n\n", x, busca_bin(arvore, x) ? "SIM" : "NÃO");

	debug_off();

	imprime(arvore);
	display(arvore);

	for(i = 0; i < sizeof(valores)/sizeof(int); i++){

		x = valores[i];
		printf("removendo %d...\n", x); getchar();

		remove_ord(arvore, busca_bin(arvore, x));
		imprime(arvore);
		display(arvore);
	}
	
	return 0;
}

int main(){

	//return teste1();
	return teste2();
}

