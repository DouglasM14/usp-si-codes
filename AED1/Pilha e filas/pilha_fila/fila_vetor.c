#include <stdio.h>
#include <stdlib.h>

#include "fila_vetor.h"

Fila * cria_fila(int capacidade){

	Fila * fila =  (Fila *) malloc (sizeof(Fila));
	fila->a = (Elemento *) malloc (capacidade * sizeof(Elemento));
	fila->capacidade = capacidade;
	fila->ini = 0;
	fila->fim = 0;

	return fila;
}

void destroi(Fila * fila){

	free(fila->a);
	free(fila);
}

void imprime(Fila * fila){

	int i;

	printf("Fila:");
	
	for(i = fila->ini; i < fila->fim; i++){

		printf(" %p", &fila->a[i % fila->capacidade]);
	}

	printf("\n");
}

int tamanho(Fila * fila){

	return fila->fim - fila->ini;
}

Boolean adiciona_final(Fila * fila, Elemento e){

	if(tamanho(fila) < fila->capacidade){

		fila->a[fila->fim % fila->capacidade] = e;
		fila->fim++;

		return TRUE;
	}

	return FALSE;
}

Boolean remove_inicio(Fila * fila, Elemento * e){

	if(tamanho(fila) > 0){

		*e = fila->a[fila->ini % fila->capacidade];
		fila->ini++;

		return TRUE;
	}

	return FALSE;

}
