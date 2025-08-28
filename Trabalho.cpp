#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Trabalho.h"
#include "StrDin.h"
#include "Funcoes.h"
#include "Interface.h"

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
				//se for * é elevado
				if(caracter=='*'){
					insereCaracter(&str,caracter,inicio);
					juntaString(&str,inicio);
				//senão é um * normal
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
				//se for igual é comparação
				if(caracter=='='){
					insereCaracter(&str,caracter,inicio);
					juntaString(&str,inicio);
				//senão é somente um caracter
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
			case '"':
			case 39:
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

void ExecutaSequencial(Linha *linha){
	Tokens *aux;
	while(linha!=NULL){
		aux = linha->pTokens;
		while(aux!=NULL){
			//chamadas da função aqui
			if(strcmp(aux->token,"console.log")==0){
				consoleLog(&aux);
			}
			aux=aux->prox;	
		}
		linha=linha->prox;
	}
}


int main(void){
    Linha *codigo = leArq();
    exibirParticipantes();

    char opcao;
    do {
        system("cls");
        FormPrincipal();   
        Menu();    
        if (codigo != NULL) {
            exibirTokens(codigo); 
        } else {
            gotoxy(50, 19);
            printf("Nenhum token lido.");
        }
        gotoxy(21,21);
		opcao = toupper(getch());
		
        switch(opcao){
            case 13: // ENTER
                ExecutaSequencial(codigo);
                break;
            case 27: // ESC
                break;
            default:
                gotoxy(10, 13);
                printf("Opcao invalida...");
                getch();
                break;
        }
    } while(opcao != 27);

    return 0;
}

