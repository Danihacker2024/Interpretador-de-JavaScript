#ifndef LISTADELISTASFUNC_H   
#define LISTADELISTASFUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <conio2.h>

struct tokensF{
	struct variavel var; 
	struct tokensF *prox;
}; typedef struct tokensF TokensF;

struct linhaF{
	struct linhaF *ant,*prox;
	char nomeFunc[100];
	TokensF *pTokens;
}; typedef struct linhaF LinhaF;

void NovaLinhaF(LinhaF **linha,char *nomeF){
	*linha=(LinhaF*)malloc(sizeof(LinhaF));
	(*linha)->pTokens=NULL;
	(*linha)->ant=NULL;
	(*linha)->prox=NULL;
	strcpy((*linha)->nomeFunc,nomeF);
}

void NovoTokenF(TokensF **novo, var var){
	*novo=(TokensF*)malloc(sizeof(TokensF));
	(*novo)->prox=NULL;
	(*nove)->var=var;
}

void adicionarLinhaF(LinhaF **inicio,char *nomeF){
	LinhaF *nova;
	LinhaF *aux;
	NovaLinhaF(&nova,nomeF);
	if(*inicio==NULL)
		*inicio=nova;
	else{
		aux=*inicio;
		while(aux->prox!=NULL)
			aux=aux->prox;
		aux->prox=nova;
		nova->ant = aux;
	}
}

//busca a ultima linha adicionada
LinhaF *buscaUltimaLinhaF(LinhaF *inicio){
	LinhaF *aux=inicio;
	while(aux->prox!=NULL)
		aux=aux->prox;
	return aux;
}

void buscaFuncao(LinhaF **linha, char *nomeFunc){
	while(strcmp(*linha->nomeFunc,nomeFunc)!=0 && *linha!=NULL)
		*linha=(*linha)->ant;
}


void adicionarTokenF(LinhaF *linha, var var){
	TokensF *novo, *aux;
	NovoTokenF(&novo,var);
	if(linha->pTokens==NULL)
		linha->pTokens=novo;
	else{
		aux=linha->pTokens;
		while(aux->prox!=NULL)
			aux=aux->prox;
		aux->prox=novo;
	}
}
/*
void exibirTokens(Linha *inicio) {
    Linha *aux = inicio;
    int y = 6;  
    int x   = 28;
	int linha=1; 
    Tokens *comando;

    textcolor(15);
    textbackground(0);

    while (aux != NULL && y < 29) {
        gotoxy(x, y);

        comando = aux->pTokens;
        printf("Linha %d: ", linha);

        while (comando != NULL) {
            printf("[%s] ", comando->token);
            comando = comando->prox;
        }
		linha++;
        y++;
        aux = aux->prox;
    }
}*/

#endif
