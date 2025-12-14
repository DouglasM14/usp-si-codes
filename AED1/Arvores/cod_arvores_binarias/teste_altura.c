#include <stdio.h>
#include <stdlib.h>

#include "arvore_binaria.h"

int max(int a, int b) { return a > b ? a : b; } 

int altura(No * no){

	if(no) {

		return max(altura(no->esq), altura(no->dir)) + 1;
	}

	return -1;
}

int tamanho(No * no){

	if(no){

		return tamanho(no->esq) + tamanho(no->dir) + 1;
	}
	
	return 0;
}

int teste_altura(int n){

	int i, x;
	Arvore * arvore = cria_arvore();

	debug_off();

	for(i = 0; i < n; i++){

		insere_ord(arvore, rand() % n);
	}

	printf("tamanho = %d, altura = %d\n", tamanho(arvore->raiz), altura(arvore->raiz));

	if(altura(arvore->raiz) <= 5) {

		imprime(arvore);
		display(arvore);
		getchar();
	}

	for(i = 0; i < 4; i++){

		x = rand() % n;
		printf("\nProcurando pelo valor %d...\n", x);
		printf("valor %d armazenado na árvore? %s\n\n", x, busca_bin(arvore, x) ? "SIM" : "NÃO");
	}

	return 0;
}

int main(int argc, char ** argv){

	srand(argc >= 3 ? atoi(argv[2]) : 0);

	return teste_altura(argc >= 2 ? atoi(argv[1]) : 8);
}

