#include <stdio.h>
#include <stdlib.h>

#include "lista_ligada_circular.h"

ListaLigada * cria_lista(){

	No * cabeca =  (No *) malloc (sizeof(No));
	cabeca->proximo = cabeca;

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

		printf(" %ld", p->valor);
	}

	printf("\n");
}

#ifdef LISTA_ORDENADA
int busca(ListaLigada * lista, Elemento e){

	int i = 0;
	No * p = lista->cabeca->proximo;

	while(p != lista->cabeca && p->valor < e){

		p = p->proximo;
		i++;
	}

	return p != lista->cabeca ? (p->valor == e ? i : -1) : -1;
}
#else
int busca(ListaLigada * lista, Elemento e){

	int i;
	No * p;

	lista->cabeca->valor = e;

	for(i = 0, p = lista->cabeca->proximo; p->valor != e; p = p->proximo, i++);

	return p != lista->cabeca ? i : -1;
}
#endif

#ifdef LISTA_ORDENADA
Boolean insere(ListaLigada * lista, Elemento e){

	No * p;
	No * anterior;
	No * novo = (No *) malloc(sizeof(No));

	novo->valor = e;

	anterior = lista->cabeca;
	p = lista->cabeca->proximo;

	while(p != lista->cabeca){

		if(e < p->valor) break;
 			
		anterior = p;
		p = p->proximo;
	}
	
	novo->proximo = p;	
	anterior->proximo = novo;

	lista->tamanho++;
	return TRUE;
}
#else
Boolean insere(ListaLigada * lista, Elemento e, int indice){

	int i, antecessor;

	No * p;
	No * novo = (No *) malloc(sizeof(No));

	novo->valor = e;
	
	if(indice >= 0 && indice <= tamanho(lista)){

		i = -1;
		antecessor = indice - 1;
		p = lista->cabeca;

		while(i < antecessor){

			i++;
			p = p->proximo;
		}
		
		novo->proximo = p->proximo;
		p->proximo = novo;
		
		lista->tamanho++;
		return TRUE;
	}

	return FALSE;
}
#endif

Boolean remove_elemento(ListaLigada * lista, Elemento e){

	int i, antecessor;
	int indice = busca(lista, e);
	No * p;
	No * tmp;

	if(indice >= 0) {

		i = -1;
		antecessor = indice - 1;
		p = lista->cabeca;

		while(i < antecessor){

			i++;
			p = p->proximo;
		}
		
		tmp = p->proximo;
		p->proximo = tmp->proximo;
		free(tmp);

		lista->tamanho--;
		return TRUE;
	}

	return FALSE;
}
