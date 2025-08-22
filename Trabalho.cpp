#include <stdio.h>
#include <stdlib.h>

#include "Trabalho.h"
#include "StrDin.h"

void leArq(){
	Linha *inicio=NULL;
	
	FILE *arq = fopen("exemplo.js","r");
	char linha[300];
	while(fscanf(arq,"%[^\n]",linha)){
		
		fgetc(arq);
	}
}


int main(void){
	leArq();
}
