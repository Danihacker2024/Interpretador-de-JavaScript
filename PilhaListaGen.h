#ifndef PILHALISTAGEN_H   
#define PILHALISTAGEN_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaGen.h"


struct pilhaGen{
	ListaGen *lista;
	struct pilhaGen *prox;
};typedef struct pilhaGen PilhaGen;

void initGen(PilhaGen **p){
	*p=NULL;
}

void pushGen(PilhaGen **p, ListaGen *aux){
	PilhaGen *nova = (PilhaGen*)malloc(sizeof(PilhaGen));
	nova->lista = aux;
	nova->prox = *p;
	*p=nova;	
}

char isEmptyGen(PilhaGen *p){
	return p==NULL;
}

ListaGen *topGen(PilhaGen *p){
	if(!isEmptyGen(p))
		return p->lista;
	return NULL;
}

void popGen(PilhaGen **p,ListaGen **aux2){
	PilhaGen *aux;
	if(!isEmptyGen(*p)){	
		aux=*p;
		*aux2=(*p)->lista;
		*p=aux->prox;
		free(aux);
	}else{
		*aux2=NULL;
	}
}

#endif
