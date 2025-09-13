#ifndef PILHAFUNCOES_H   
#define PILHAFUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pilhaf{
	char info[20];
	struct pilha *prox;
};typedef struct pilha PilhaF;

void initF(PilhaF **p){
	*p=NULL;
}

void pushF(PilhaF **p, char x[]){
	PilhaF *nova = (PilhaF *)malloc(sizeof(PilhaF));
	strcpy(nova->info,x);
	nova->prox = *p;
	*p=nova;	
}

char isEmptyF(PilhaF *p){
	return p==NULL;
}

void topF(PilhaF *p, char *str){
	if(!isEmpty(p))
		strcpy(*str,p->info);
	strcpy(*str,"");
}

void popF(PilhaF **p,char *x){
	PilhaF *aux;
	if(!isEmpty(*p)){	
		aux=*p;
		strcpy(*x,(*p)->info);
		*p=aux->prox;
		free(aux);
	}else
		strcpy(*x,"");
}

#endif
