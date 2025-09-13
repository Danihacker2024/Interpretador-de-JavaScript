#ifndef PILHA_H   
#define PILHA_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct variavel{
	char nome[50];
	int valorInt;
	float valorFloat;
	char valorString[100];
	int terminal;
};typedef struct variavel var;


struct pilha{
	struct variavel info;
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
	aux.valorInt=-1;
	return aux;
}

void pop(Pilha **p,var *x){
	Pilha *aux;
	if(!isEmpty(*p)){	
		aux=*p;
		*x=(*p)->info;
		*p=aux->prox;
		free(aux);
	}else{
		x->valorInt=-1;
	}
}

#endif
