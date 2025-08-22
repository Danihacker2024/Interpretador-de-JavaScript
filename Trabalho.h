#include <stdio.h>
#include <stdlib.h>

struct tokens{
	char token[100];
	struct tokens *prox;
};typedef struct tokens Tokens

struct linha{
	struct linha *ant,*prox;
	Tokens *pTokens;
}; typedef struct linha Linha;

void NovaLinha(Linha **Linha){
	*Linha=(Linha*)malloc(sizeof(Linha));
	*Linha->pTokens=NULL;
	*Linha->ant=NULL;
	*Linha->prox=NULL;
}

void NovoToken(Tokens **novo, char token[]){
	*novo=(Tokens*)malloc(sizeof(Tokens))
	*novo->prox=NULL;
	strcpy(*novo->token,token);
}

void adicionarLinha(Linha **inicio){
	Linha *nova;
	Linha *aux;
	NovaLinha(&nova);
	if(*inicio=NULL)
		*inicio=nova;
	else{
		aux=*inicio;
		while(aux->prox!=NULL)
			aux=aux->prox;
		aux->prox=nova;
	}
}

void adicionarToken(Linha **Linha, char token[]){
	Tokens *novo, *aux;
	NovoToken(&novo,token);
	if((*Linha)->pTokens=NULL)
		(*Linha)->pTokens=novo;
	else{
		aux=(*Linha)->pTokens;
		while(aux->prox!=NULL)
			aux=aux->prox;
		aux->prox=novo;
	}
}
