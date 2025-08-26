#include <stdio.h>
#include "Trabalho.h"

void consoleLog(Tokens **aux){
	//[console.log]->[(]->["]->[conteudo]
	*aux=(*aux)->prox->prox->prox;
	while((*aux)->token[1]!='"'){
		printf("%s ",(*aux)->token);
		*aux=(*aux)->prox;
	}
	//["]->[)]
	*aux=(*aux)->prox;
	
}
