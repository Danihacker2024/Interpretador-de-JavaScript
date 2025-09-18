#ifndef PILHALISTAGEN_H   
#define PILHALISTAGEN_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaGen.h"


struct pilhaGen{
	ListaGen *info;
	struct pilhaGen *prox;
};typedef struct pilha PilhaGen;

void initGen(PilhaGen **p){
	*p=NULL;
}

void pushGen(PilhaGen **p, ListaGen *aux){
	PilhaGen *nova = (PilhaGen*)malloc(sizeof(PilhaGen));
	nova->info = aux;
	nova->prox = *p;
	*p=nova;	
}

char isEmptyGen(PilhaGen *p){
	return p==NULL;
}

ListaGen *topGen(PilhaGen *p){
	if(!isEmpty(p))
		return p->info;
	return NULL;
}

void popGen(PilhaGen **p,ListaGen **info){
	PilhaGen *aux;
	if(!isEmpty(*p)){	
		aux=*p;
		*info=(*p)->info;
		*p=aux->prox;
		free(aux);
	}else{
		*info=NULL;
	}
}

#endif
