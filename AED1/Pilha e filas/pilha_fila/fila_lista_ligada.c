#include <stdio.h>
#include <stdlib.h>

#include "fila_lista_ligada.h"

Fila * cria_fila(){

	Fila * fila =  (Fila *) malloc (sizeof(Fila));
	fila->primeiro = NULL;
	fila->ultimo = NULL;
	fila->tamanho = 0;
	
	return fila;
}

void destroi(Fila * fila){

	No * p = fila->primeiro;
	No * tmp;

	while(p){
		
		tmp = p;
		p = p->proximo;
		free(tmp);
	}

	free(fila);
}

int tamanho(Fila * fila){

	return fila->tamanho;
}

void imprime(Fila * fila){

	No * p = fila->primeiro;

	printf("Fila:");

	while(p){

		printf(" %d", p->valor);
		p = p->proximo;
	}

	printf("\n");
}


Boolean adiciona_final(Fila * fila, Elemento e){

	No * novo = (No *) malloc(sizeof(No));

	novo->valor = e;
	novo->proximo = NULL;

	if(fila->primeiro){

		fila->ultimo->proximo = novo;
		fila->ultimo = novo;
	}
	else{
		fila->primeiro = fila->ultimo = novo;
	}	

	fila->tamanho++;
	return TRUE;

}

Boolean remove_inicio(Fila * fila, Elemento * e){

	No * primeiro = fila->primeiro;

	if(primeiro) {

		*e = primeiro->valor;
		fila->primeiro = primeiro->proximo;
		fila->ultimo = fila->primeiro ? fila->ultimo : NULL;
		fila->tamanho--;
		free(primeiro);

		return TRUE;
	}

	return FALSE;
}
