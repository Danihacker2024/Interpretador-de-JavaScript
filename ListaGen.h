//Somente vamos mexer com a lista generalizada mais pra frente

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PilhaVar.h"

struct reg_lista
{
	struct listagen *cabeca;
	struct listagen *cauda;
};
union info_lista
{
	struct reg_lista lista;
};

struct listagen
{
	var info;
	//char terminal;
	union info_lista no;
};typedef struct listagen ListaGen;
/*
ListaGen *CriaT(var info)
{
	ListaGen *L = (ListaGen*)malloc(sizeof(ListaGen));
	L->terminal = 1;
	L->no.info=info;
	return L;
}*/

char Nula(ListaGen *L)
{
	return L==NULL;
}
/*
char Atomo(ListaGen *L)
{
	return !Nula(L) && L->terminal;
}*/

ListaGen *Cons(var var, ListaGen *H, ListaGen *T)
{
	if (Atomo(T))
	{
		printf("Cons: Segundo arqumento nao pode ser Atomo!");
		return NULL;
	}
	else
	{
		ListaGen *L = (ListaGen*)malloc(sizeof(ListaGen));
		//L->terminal = 0;
		L->info=var;
		L->no.lista.cabeca = H;
		L->no.lista.cauda = T;
		return L;
	}
}

ListaGen *Head(ListaGen *L)
{
	if (Nula(L) || Atomo(L))
	{
		printf("Head: argumento deve ser lista n o vazia!");
		return NULL;
	}
	else
		return L->no.lista.cabeca;
}

ListaGen *Tail(ListaGen *L)
{
	if (Nula(L) || Atomo(L))
	{
		printf("Tail: argumento deve ser lista n o vazia!");
		return NULL;
	}
	else
		return L->no.lista.cauda;
}
