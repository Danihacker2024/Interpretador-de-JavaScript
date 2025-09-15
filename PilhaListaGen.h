#ifndef PILHALISTAGEN_H   
#define PILHALISTAGEN_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaGen.h"


struct pilha{
	ListaGen *info;
	struct pilha *prox;
};typedef struct pilha Pilha;

void init(Pilha **p){
	*p=NULL;
}

void push(Pilha **p, LintaGen *info){
	Pilha *nova = (Pilha *)malloc(sizeof(Pilha));
	nova->info = info;
	nova->prox = *p;
	*p=nova;	
}

char isEmpty(Pilha *p){
	return p==NULL;
}

ListaGen *top(Pilha *p){
	if(!isEmpty(p))
		return p->info;
	return NULL;
}

void pop(Pilha **p,ListaGen **info){
	Pilha *aux;
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
