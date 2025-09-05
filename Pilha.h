#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Funcoes.h"

struct pilha{
	var info;
	struct pilha *prox;
};typedef struct pilha Pilha;

void init(Pilha **p){
	*p=NULL;
}

void push(Pilha **p, var x){
	Pilha *nova = (Pilha *)malloc(sizeof(Pilha));
	nova->info = x;
	nova->prox = *p;
	*p=nova;
}

char isEmpty(Pilha *p){
	return p==NULL;
}

var top(Pilha *p){
	var aux;
	if(!isEmpty(p))
		return p->info;
	return aux.valorInt=-1;
}

void pop(Pilha **p,var *x){
	Pilha *aux;
	if(isEmpty(*p)){
		*x=(*p)->info;
		aux=*p;
		*p=aux->prox;
		free(aux);
	}else
		*x.valorInt=-1;
}