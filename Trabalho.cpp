#include <stdio.h>
#include <stdlib.h>

#include "Trabalho.h"
#include "StrDin.h"
//ainda tem [] em branco com nada dentro resolver depois 
Linha *leArq(){
	Linha *inicio=NULL;
	StrDin *str=NULL;
	FILE *arq = fopen("exemplo.js","r");
	char caracter;
	fscanf(arq,"%c",&caracter);
	adicionarLinha(&inicio);
	while(!feof(arq)){
		switch(caracter){
			case '*':
				juntaString(&str,inicio);
				insereCaracter(&str,caracter,inicio);
				fscanf(arq,"%c",&caracter);
				//se for * � elevado
				if(caracter=='*'){
					insereCaracter(&str,caracter,inicio);
					juntaString(&str,inicio);
				//sen�o � um * normal
				}else{
					juntaString(&str,inicio);
					insereCaracter(&str,caracter,inicio);
				}
				break;
			case '!':
			case '>':
			case '<':
			case '=':
				juntaString(&str,inicio);
				insereCaracter(&str,caracter,inicio);
				fscanf(arq,"%c",&caracter);
				//se for igual � compara��o
				if(caracter=='='){
					insereCaracter(&str,caracter,inicio);
					juntaString(&str,inicio);
				//sen�o � somente um caracter
				}else{
					juntaString(&str,inicio);
					insereCaracter(&str,caracter,inicio);
				}
				break;
			case '|':
			case '&':
				juntaString(&str,inicio);
				insereCaracter(&str,caracter,inicio);
				fscanf(arq,"%c",&caracter);
				insereCaracter(&str,caracter,inicio);
				juntaString(&str,inicio);
				break;
			case '\n':
				adicionarLinha(&inicio);
				break;
			case ',':
			case ';':
			case ' ':
				juntaString(&str,inicio);
				break;
			case '+':
			case '-':
			case '/':
			case '%':
			case '(':
			case ')':
			case '[':
			case ']':
			case '{':
			case '}':
				juntaString(&str,inicio);
				insereCaracter(&str,caracter,inicio);
				juntaString(&str,inicio);
				break;
			default:
				insereCaracter(&str, caracter, inicio);
				break;
		}	
		fscanf(arq,"%c",&caracter);
	}
	fclose(arq);
	return inicio;
}


int main(void){
	Linha *codigo = leArq();

    if (codigo != NULL) {
        printf("Tokens lidos do arquivo:\n");
        imprimeLinhas(codigo);
    } else {
        printf("Nenhum token lido.\n");
    }

}
