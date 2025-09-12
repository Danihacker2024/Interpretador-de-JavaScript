#ifndef TRABALHO_H   
#define TRABALHO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "meuconio.h"

struct tokens{
	char token[100];
	struct tokens *prox;
}; typedef struct tokens Tokens;

struct linha{
	struct linha *ant,*prox;
	Tokens *pTokens;
}; typedef struct linha Linha;

void NovaLinha(Linha **linha){
	*linha=(Linha*)malloc(sizeof(Linha));
	(*linha)->pTokens=NULL;
	(*linha)->ant=NULL;
	(*linha)->prox=NULL;
}

void NovoToken(Tokens **novo, char token[]){
	*novo=(Tokens*)malloc(sizeof(Tokens));
	(*novo)->prox=NULL;
	strcpy((*novo)->token,token);
}

void adicionarLinha(Linha **inicio){
	Linha *nova;
	Linha *aux;
	NovaLinha(&nova);
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
Linha *buscaLinha(Linha *inicio){
	Linha *aux=inicio;
	while(aux->prox!=NULL)
		aux=aux->prox;
	return aux;
}

void adicionarToken(Linha *linha, char token[]){
	Tokens *novo, *aux;
	NovoToken(&novo,token);
	if(linha->pTokens==NULL)
		linha->pTokens=novo;
	else{
		aux=linha->pTokens;
		while(aux->prox!=NULL)
			aux=aux->prox;
		aux->prox=novo;
	}
}

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
}

#endif
