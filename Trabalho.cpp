#include <stdio.h>
#include <stdlib.h>

#include "Trabalho.h"
#include "StrDin.h"

void leArq(){
	Linha *inicio=NULL;
	StrDin *str;
	FILE *arq = fopen("exemplo.js","r");
	char caracter;
	fscanf(arq,"%c",&caracter);
	adicionarLinha(&inicio);
	while(!feof(arq)){
		if(caracter=="\n"){
			adicionarLinha(&inicio);	
		}else{
			insereCaracter(&str, caracter, *inicio);
		}
		fscanf(arq,"%c",&caracter);
	}
}


int main(void){
	leArq();
}
