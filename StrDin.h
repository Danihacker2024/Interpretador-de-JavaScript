#include <stdio.h>
#include <stdlib.h>

struct stringdin{
	char letra;
	struct stringdin *prox;
};typedef strut stringdin StrDin;

void insereCaracter(StrDin **str, char c){
	StrDin *aux;
	StrDin *nova = (StrDin*)malloc(sizeof(StrDin));
	nova->letra=c;
	nova->prox=NULL;
	if(c=="."){
		char string[50]=juntaString(str);
		adicionarToken(Linha,string);
	}
	if(*str==NULL)
		*str=nova;
	else{
		aux=*str;
		while(aux->prox!=NULL)
			aux=aux->prox;
		aux->prox=nome;
	}
}
