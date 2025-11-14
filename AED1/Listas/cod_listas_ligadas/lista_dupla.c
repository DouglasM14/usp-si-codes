#include <stdio.h>
#include <stdlib.h>

#include "lista_dupla.h"

ListaLigada * cria_lista(){

	No * cabeca =  (No *) malloc (sizeof(No));
	cabeca->proximo = cabeca;
	cabeca->anterior = cabeca;

	ListaLigada * lista =  (ListaLigada *) malloc (sizeof(ListaLigada));
	lista->cabeca = cabeca;
	lista->tamanho = 0;
	
	return lista;
}

void destroi_lista(ListaLigada * lista){

	No * p = lista->cabeca->proximo;
	No * tmp;

	while(p != lista->cabeca){
		
		tmp = p;
		p = p->proximo;
		free(tmp);
	}

	free(lista->cabeca);
	free(lista);
}

int tamanho(ListaLigada * lista){

	return lista->tamanho;
}

void imprime(ListaLigada * lista){

	No * p;

	printf("Lista:");

	for(p = lista->cabeca->proximo; p != lista->cabeca; p = p->proximo){

		printf(" %d", p->valor);
	}

	printf(" [ ");

	for(p = lista->cabeca->anterior; p != lista->cabeca; p = p->anterior){

		printf("%d ", p->valor);
	}

	printf("]\n");
}

No * busca_no(ListaLigada * lista, Elemento e, int * indice){

	No * p = lista->cabeca->proximo;
	*indice = 0;

	while(p != lista->cabeca && p->valor < e){

		p = p->proximo;
		(*indice)++;
	}

	return p != lista->cabeca ? (p->valor == e ? p : NULL) : NULL;
}


int busca(ListaLigada * lista, Elemento e){

	int indice;
	No * no = busca_no(lista, e, &indice);

	return no ? indice : -1;
}

Boolean insere(ListaLigada * lista, Elemento e){

	No * p;
	No * novo = (No *) malloc(sizeof(No));

	novo->valor = e;
	novo->proximo = novo->anterior = NULL;

	p = lista->cabeca->proximo;

	while(p != lista->cabeca){

		if(e < p->valor) break;
 			
		p = p->proximo;
	}
	
	novo->proximo = p;
	novo->anterior = p->anterior;
	p->anterior->proximo = novo;
	p->anterior = novo;

	lista->tamanho++;
	return TRUE;
}

Boolean remove_elemento(ListaLigada * lista, Elemento e){


	int indice;
	No * a_remover = busca_no(lista, e, &indice);

	if(a_remover) {

		a_remover->anterior->proximo = a_remover->proximo;
		a_remover->proximo->anterior = a_remover->anterior;

		free(a_remover);

		lista->tamanho--;
		return TRUE;
	}

	return FALSE;
}
