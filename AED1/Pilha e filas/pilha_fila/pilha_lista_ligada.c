#include <stdio.h>
#include <stdlib.h>

//#include "pilha_vetor.h"
#include "pilha_lista_ligada.h"

Pilha * cria_pilha(){

	Pilha * pilha =  (Pilha *) malloc (sizeof(Pilha));
	pilha->primeiro = NULL;
	pilha->tamanho = 0;
	
	return pilha;
}

void destroi(Pilha * pilha){

	No * p = pilha->primeiro;
	No * tmp;

	while(p){
		
		tmp = p;
		p = p->proximo;
		free(tmp);
	}

	free(pilha);
}

int tamanho(Pilha * pilha){

	return pilha->tamanho;
}

void imprime(Pilha * pilha){

	No * p = pilha->primeiro;

	printf("Pilha:");

	while(p){

		printf(" %d", p->valor);
		p = p->proximo;
	}

	printf("\n");
}


Boolean push(Pilha * pilha, Elemento e){

	No * novo = (No *) malloc(sizeof(No));

	novo->valor = e;
	novo->proximo = pilha->primeiro;
	pilha->primeiro = novo;
	pilha->tamanho++;

	return TRUE;

}

Boolean pop(Pilha * pilha, Elemento * e){

	No * topo = pilha->primeiro;

	if(topo) {

		*e = topo->valor;
		pilha->primeiro = topo->proximo;
		pilha->tamanho--;
		free(topo);

		return TRUE;
	}

	return FALSE;
}
