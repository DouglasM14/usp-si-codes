#include <stdio.h>
#include <stdlib.h>

#include "pilha_vetor.h"

Pilha * cria_pilha(int capacidade){

	Pilha * pilha =  (Pilha *) malloc (sizeof(Pilha));
	pilha->a = (Elemento *) malloc (capacidade * sizeof(Elemento));
	pilha->capacidade = capacidade;
	pilha->topo = 0;

	return pilha;
}

void destroi(Pilha * pilha){

	free(pilha->a);
	free(pilha);
}

void imprime(Pilha * pilha){

	int i;

	printf("Pilha:");

	for(i = 0; i < pilha->topo; i++){

		printf(" %p", &pilha->a[i]);
	}

	printf("\n");
}

int tamanho(Pilha * pilha){

	return pilha->topo;
}

Boolean push(Pilha * pilha, Elemento e){

	if(pilha->topo < pilha->capacidade){

		pilha->a[pilha->topo] = e;
		pilha->topo++;

		return TRUE;
	}

	return FALSE;
}

Boolean pop(Pilha * pilha, Elemento * e){

	if(pilha->topo > 0){

		pilha->topo--;
		*e = pilha->a[pilha->topo];

		return TRUE;
	}

	return FALSE;

}
