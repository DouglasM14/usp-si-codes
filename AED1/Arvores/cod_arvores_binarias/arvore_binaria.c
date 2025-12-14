#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "arvore_binaria.h"

///////////////////////////////////////////////////////////////////////////////////////////
// Funções auxiliares. Não fazem parte do conjunto de operações elementares da estrutura //
///////////////////////////////////////////////////////////////////////////////////////////

Boolean __debug__ = FALSE;
void debug_on() { __debug__ = TRUE; }
void debug_off() { __debug__ = FALSE; }

#define ROWS 20
#define COLS 80

int display_rec(char ** buffer, No * no, int level, double h_position){

	char * ptr;
	int i, col, a, b;
	double offset;

	if(no){
		col = (int)(h_position * COLS);
		offset = 1.0 / pow(2, level + 2);

		ptr = buffer[1 + level * 3] + col;
		sprintf(ptr, "%03d", no->valor);
		*(ptr + strlen(ptr)) = ' ';

		if(no->esq || no->dir) *(buffer[2 + level * 3] + col + 1) = '|';

		if(no->esq){
		
			i = (int)((h_position - offset) * COLS);
			*(buffer[3 + level * 3] + 1 + i) = '|';
			i++;
			for(; i <= col; i++) *(buffer[3 + level * 3] + 1 + i) = '-';
		}
		
		if(no->dir){

			for(i = col; i < (int)((h_position + offset) * COLS); i++) *(buffer[3 + level * 3] + 1 + i) = '-';
			*(buffer[3 + level * 3] + 1 + i) = '|';
		}

		a = display_rec(buffer, no->esq, level + 1, h_position - offset);
		b = display_rec(buffer, no->dir, level + 1, h_position + offset);

		if(a > b) return a;
		return b;
	}

	return level;
}

void display_no(No * no){

	int i, j, r;

	char ** buffer = (char **) malloc(ROWS * sizeof(char *));

	for(i = 0; i < ROWS; i++) {

		buffer[i] = (char *) malloc((COLS + 1) * sizeof(char));

		for(j = 0; j < COLS; j++) buffer[i][j] = ' ';
		buffer[i][j] = '\0';
	}

	r = display_rec(buffer, no, 0, 0.5);

	for(i = 0; i < 3 * r; i++) printf("%s\n", buffer[i]);
	printf("-----------------------------------------------------------------------------------------------\n");

	if(__debug__) getchar();
}

void display(Arvore * arvore){

	display_no(arvore->raiz);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementações comuns tanto para a árvore binária de "propósito geral", quanto para a árvore binária de busca //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Arvore * cria_arvore(){

	Arvore * arvore = (Arvore *) malloc (sizeof(Arvore));
	arvore->raiz = NULL;	
	return arvore;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void imprime_rec(No * no){

	// percurso in-ordem para a impressão dos elementos

	if(no){
		imprime_rec(no->esq);
		printf(" %d", no->valor);
		imprime_rec(no->dir);
	}
}

void imprime(Arvore * arvore){

	printf("Elementos na arvore:");
	imprime_rec(arvore->raiz);
	printf("\n");
}

//////////////////////////////////////////////////////////////////////////////////////////
// Implementações específicas para a árvore binária de "propósito geral" (não ordenada) //
//////////////////////////////////////////////////////////////////////////////////////////

No * busca_rec(No * no, Elemento e){

	No * aux;

	if(no){

		if(__debug__) display_no(no);

		if(no->valor == e) return no;

		aux = busca_rec(no->esq, e);
		if(aux) return aux;

		return busca_rec(no->dir, e);
	}

	return NULL;
}

No * busca(Arvore * arvore, Elemento e){
	
	return busca_rec(arvore->raiz, e);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Boolean insere(Arvore * arvore, No * pai, Elemento e, int lado){

	No * novo = (No *) malloc(sizeof(No));
	
	novo->valor = e;
	novo->esq = novo->dir = NULL;

	if(!busca(arvore, e)){

		if(pai){

			if(lado == ESQUERDO){

				novo->esq = pai->esq;
				pai->esq = novo;
			}
			else{

				novo->esq = pai->dir;
				pai->dir = novo;
			}
		}
		else{
			novo->esq = arvore->raiz;
			arvore->raiz = novo;
		}

		return TRUE;
	}

	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Boolean remove_no_rec(Arvore * arvore, No * pai, No * no){

	No * a_remover;

	if(no){

		if(no->esq || no->dir){

			a_remover = no->esq ? no->esq : no->dir;
			no->valor = a_remover->valor;
			return remove_no_rec(arvore, no, a_remover);
		}
		else{

			if(pai) {

				if(pai->esq == no) pai->esq = NULL;
				if(pai->dir == no) pai->dir = NULL;
			}
			else{
				arvore->raiz = NULL;	
			}
				
			free(no);
			return TRUE;
		}
	}

	return FALSE;
}

No * encontra_pai(No * raiz, No * no){

	No * aux;

	if(raiz){

		if(raiz->esq == no) return raiz;
		if(raiz->dir == no) return raiz;

		aux = encontra_pai(raiz->esq, no);
		if(aux) return aux;

		return encontra_pai(raiz->dir, no);
	}

	return NULL;
}

Boolean remove_no(Arvore * arvore, No * no){

	return remove_no_rec(arvore, encontra_pai(arvore->raiz, no), no);
}

///////////////////////////////////////////////////////////////
// Implementações específicas para a árvore binária de busca //
///////////////////////////////////////////////////////////////

No * busca_bin_rec(No * no, Elemento e){

	if(no){

		if(__debug__) display_no(no);

		if(no->valor == e) return no;
		if(e < no->valor) return busca_bin_rec(no->esq, e);
		return busca_bin_rec(no->dir, e);
	}

	return NULL;
}

No * busca_bin(Arvore * arvore, Elemento e){
	
	return busca_bin_rec(arvore->raiz, e);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Boolean insere_ord_rec(No * raiz, No * novo){

	if(novo->valor != raiz->valor){

		if(novo->valor < raiz->valor){

			if(raiz->esq) return insere_ord_rec(raiz->esq, novo);
			else raiz->esq = novo;
		}
		else{
			if(raiz->dir) return insere_ord_rec(raiz->dir, novo);
			else raiz->dir = novo;
		}
	
		return TRUE;
	}
	
	free(novo);
	return FALSE;
}

Boolean insere_ord(Arvore * arvore, Elemento e){

	No * novo = (No *) malloc(sizeof(No));
	
	novo->valor = e;
	novo->esq = novo->dir = NULL;

	if(arvore->raiz) return insere_ord_rec(arvore->raiz, novo);
		
	arvore->raiz = novo;
	return TRUE;
}

// versão alternativa da inserção que possui um código um pouco mais limpo...

No * insere_ord_rec_ALT(No * raiz, No * novo){

	// esta versão retorna o endereço da raiz da subárvore que recebeu o elemento novo.

	if(raiz){

		if(novo->valor != raiz->valor){

			if(novo->valor < raiz->valor) raiz->esq = insere_ord_rec_ALT(raiz->esq, novo);
			else raiz->dir = insere_ord_rec_ALT(raiz->dir, novo);
		}

		return raiz;
	}

	return novo;
}

Boolean insere_ord_ALT(Arvore * arvore, Elemento e){

	No * novo = (No *) malloc(sizeof(No));
	
	novo->valor = e;
	novo->esq = novo->dir = NULL;

	arvore->raiz = insere_ord_rec_ALT(arvore->raiz, novo);
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

No * encontra_menor(No * raiz){

	if(raiz->esq) return encontra_menor(raiz->esq);
	
	return raiz;
}

No * encontra_maior(No * raiz){

	if(raiz->dir) return encontra_maior(raiz->dir);
	
	return raiz;
}

No * encontra_pai_ord(No * raiz, No * no){

	if(raiz){

		if(raiz->esq == no) return raiz;
		if(raiz->dir == no) return raiz;
		if(no->valor < raiz->valor) return encontra_pai_ord(raiz->esq, no);
		if(no->valor > raiz->valor) return encontra_pai_ord(raiz->dir, no);
	}
		
	return NULL;
}

Boolean remove_ord(Arvore * arvore, No * no){

	Boolean retorno;
	Elemento valor_promovido;

	No * a_remover;
	No * pai;

	if(no){

		if(no->dir || no->esq){

			// Obs: só podemos efetuar a "promoção" do valor contido em "a_remover" 
			// após o termino da chamada recursiva. Caso contrário, a chamada à função
			// "encontra_pai_ord" no caso base da recursão irá retornar resultado 
			// inconsistente (devido a existência de valores duplicados na árvore). 

			a_remover = no->dir ? encontra_menor(no->dir) : encontra_maior(no->esq);
			valor_promovido = a_remover->valor;
			retorno = remove_ord(arvore, a_remover);
			no->valor = valor_promovido;
			return retorno;
		}
		else{
			pai = encontra_pai_ord(arvore->raiz, no);
			
			if(pai){
				if(pai->esq == no) pai->esq = NULL;
				if(pai->dir == no) pai->dir = NULL;
			}
			else{
				arvore->raiz = NULL;
			}

			free(no);
			return TRUE;
		}
	}

	return FALSE;
}

