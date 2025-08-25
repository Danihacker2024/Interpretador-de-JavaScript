#include <stdio.h>
#include <stdlib.h>

#include "Trabalho.h"

struct stringdin{
	char letra;
	struct stringdin *prox;
};typedef strut stringdin StrDin;

//implementar juntaString
void juntaString(StrDin *str, char string, Linha *inicio){
	Linha *linha;
	linha = buscaLinha(inicio);
	adicionarToken(linha,string);
}

void insereCaracter(StrDin **str, char c, Linha *inicio){
	char stringJunta[50];
	//checagem de casos
	if(c=="."){
		juntaString(*str,stringJunta,*inicio);
	}
	StrDin *aux;
	StrDin *nova = (StrDin*)malloc(sizeof(StrDin));
	nova->letra=c;
	nova->prox=NULL;
	if(*str==NULL)
		*str=nova;
	else{
		aux=*str;
		while(aux->prox!=NULL)
			aux=aux->prox;
		aux->prox=nome;
	}
}




