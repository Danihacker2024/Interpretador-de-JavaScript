//Somente vamos mexer com a lista generalizada mais pra frente

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PilhaVar.h"

union tipo
{
	float valor;
	char operador[3];
	char funcao[20];
};

struct listagen
{
	char terminal;
	union tipo info;
	struct listagen *cabeca,*cauda;

};typedef struct listagen ListaGen;


char Nula(ListaGen *L)
{
	return L==NULL;
}


ListaGen *Cons(tipo tipo, ListaGen *H, ListaGen *T, char terminal)
{
	ListaGen *L = (ListaGen*)malloc(sizeof(ListaGen));
	L->terminal = terminal;
	L->tipo=tipo;
	L->cabeca = H;
	L->cauda = T;
	return L;

}

ListaGen *Head(ListaGen *L)
{
	if (Nula(L))
	{
		printf("Head: argumento deve ser lista n o vazia!");
		return NULL;
	}
	else
		return L->cabeca;
}

ListaGen *Tail(ListaGen *L)
{
	if (Nula(L))
	{
		printf("Tail: argumento deve ser lista n o vazia!");
		return NULL;
	}
	else
		return L->cauda;
}
