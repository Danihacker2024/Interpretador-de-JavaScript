#include <stdio.h>
#include <string.h>
#include "Trabalho.h"

void calculaDoisNumeros(Tokens **aux){
	float xf,yf;
	int xi,yi;
	if((*aux)->token)
}

void consoleLog(Tokens **aux){
	//[console.log]->[(]->["]->[conteudo]
	*aux=(*aux)->prox->prox->prox;
	while((*aux)->token[0]!='"' && (*aux)->token[0]!=39){
		printf("%s ",(*aux)->token);
		*aux=(*aux)->prox;
	}
	//["]->[)] || ["]->[,]
	*aux=(*aux)->prox;
	if((*aux)->token[0]==',' || (*aux)->token[0]=='+'){
		*aux=(*aux)->prox;
		calculaDoisNumeros(*aux);
	}
}
