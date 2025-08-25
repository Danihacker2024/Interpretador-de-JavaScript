#include <stdio.h>
#include <stdlib.h>

#include "Trabalho.h"

struct stringdin{
	char letra;
	struct stringdin *prox;
};typedef struct stringdin StrDin;

//função pra juntar stringdinamica em uma normal
void juntaString(StrDin **str, Linha *inicio){
	char string[50];
	int pos=0;
	string[0]='\0';
	Linha *linha;
	while(*str!=NULL){
		string[pos++]=(*str)->letra;
		*str=(*str)->prox;
	}
	linha = buscaLinha(inicio);
	adicionarToken(linha,string);
	//implementar
	reiniciaString(**str);
}

void insereCaracter(StrDin **str, char c, Linha *inicio){
	//checagem de casos - melhor usar switch
	if(c=="."){
		juntaString(&str,*inicio);
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




