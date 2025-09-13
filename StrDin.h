#ifndef STRDIN_H   
#define STRDIN_H

#include <stdio.h>
#include <stdlib.h>

#include "ListaDeListasToken.h"

struct stringdin{
	char letra;
	struct stringdin *prox;
};typedef struct stringdin StrDin;

void reiniciaString(StrDin **str){
	StrDin *aux;
	while(*str!=NULL){
		aux=*str;
		*str=aux->prox;
		free(aux);
	}
}
//função pra juntar stringdinamica em uma normal
void juntaString(StrDin **str, Linha *inicio){
	if(*str!=NULL){
		char string[100];
		int pos=0;
		string[0]='\0';
		Linha *linha;
		while(*str!=NULL){
			string[pos++]=(*str)->letra;
			*str=(*str)->prox;
		}
		string[pos] = '\0';
		linha = buscaLinha(inicio);
		adicionarToken(linha,string);
		//implementar
		reiniciaString(str);
	}
}

void novaLetra(char c, StrDin **nova){
	*nova = (StrDin*)malloc(sizeof(StrDin));
	(*nova)->letra=c;
	(*nova)->prox=NULL;
}

void insereCaracter(StrDin **str, char c, Linha *inicio){
	StrDin *aux,*nova;
	if(c!=' '){
		novaLetra(c,&nova);
		if(*str==NULL)
			*str=nova;
		else{
			aux=*str;
			while(aux->prox!=NULL)
				aux=aux->prox;
			aux->prox=nova;
		}
	}
}



#endif
