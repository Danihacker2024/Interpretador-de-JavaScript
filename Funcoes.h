#include <stdio.h>
#include <string.h>
#include "Trabalho.h"

struct variavel{
	char nome[50];
	int valorInt;
	float valorFloat;
	char valorString[100];
};typedef struct variavel var;

/*
float stringToFloat(char str[]) {
    float resultado = 0.0f;
    float divisor = 10.0f;
    int parteDecimal = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (c == '.' && parteDecimal == 0) {
            parteDecimal = 1;
        } 
        else if (c >= '0' && c <= '9') {
            if (!parteDecimal) {
                resultado = resultado * 10 + (c - '0');
            } else {
                resultado = resultado + (c - '0') / divisor;
                divisor *= 10.0f;
            }
        }
    }
    return resultado;
}

int stringToInt(char str[]) {
    int resultado = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' || str[i] =< '9') 
        	resultado = resultado * 10 + (str[i] - '0');
    }
    return resultado;
}

void calculaDoisNumeros(Tokens **aux){
	float xf,yf,zf;
	char operacao;
	int xi,yi,zi;
	int pos=0;
	while((*aux)->token[pos]!='.')
		pos++;
	if((*aux)->token[pos]=='.' || (*aux)->prox->token[0]=='/'){
		xf=stringToFloat((*aux)->token);
		*aux=(*aux)->prox;
		operacao=(*aux)->token[0];
		*aux=(*aux)->prox;
		yf=stringToFloat((*aux)->token);
		if(operacao=='+')
			zf=xf+yf;
	}
}
*/

int Digito(char c) {
	if (c >= '0' && c <= '9')
    	return 1;
    return 0;
}


int Inteiro(char str[]) {
	int flag=1;
	int i=0;
    while(str[i] != '\0') {
        if (!Digito(str[i])) {
            flag=0;
        }
        i++;
    }
    return flag; 
}

int Float(char str[]) {
    int ponto = 0; 
	int flag=1;
	int i=0;
    while(str[i] != '\0') {
        if (str[i] == '.') {
        	if(ponto==1)
        		flag=0;
            ponto=1;
        } else if (!Digito(str[i])) {
            flag=0; 
        }
        i++;
    }
    return flag; 
}

int converteInt(char str[]){
	int num=0;
	int i=0;
	while(str[i] != '\0'){
		num=num*10+(str[i] - '0');
		i++;
	}
	return num;
}

float converteFloat(char str[]) {
    float num = 0;
    float divisor = 1;
    int i = 0;
    int parteDecimal = 0;

    while (str[i] != '\0') {
        if (str[i] == '.') {
            parteDecimal = 1;
        } else {
            num = num * 10 + (str[i] - '0');
            if (parteDecimal) {
                divisor *= 10.0;
            }
        }
        i++;
    }
    return num / divisor;
}


var declaracao(Tokens **aux){
	var variavel;
	strcpy(variavel.valorString, "");
	int flag=1;
	*aux=(*aux)->prox;
	if(*aux!=NULL){
		strcpy(variavel.nome,(*aux)->token);
		*aux=(*aux)->prox;
		if(*aux!=NULL){
			if((*aux)->token[0]=='='){
				*aux=(*aux)->prox;
				//tem que verificar se é negativo
				if(*aux!=NULL){
					if((*aux)->token[0]=='-'){
						*aux=(*aux)->prox;
						if(*aux!=NULL){
							if(Inteiro((*aux)->token))
								variavel.valorInt=-converteInt((*aux)->token);
							else if(Float((*aux)->token))
								variavel.valorFloat=-converteFloat((*aux)->token);
						}
					}else{
						
						if(Inteiro((*aux)->token))
							variavel.valorInt=converteInt((*aux)->token);
						else if(Float((*aux)->token))
							variavel.valorFloat=converteFloat((*aux)->token);
						else if((*aux)->token[0]==39 || (*aux)->token[0]=='"'){
							*aux=(*aux)->prox;
							while((*aux)->token[0]!='"' && flag){
								if(*aux!=NULL){
									strcat(variavel.valorString,(*aux)->token);
									strcat(variavel.valorString," ");
									*aux=(*aux)->prox;
								} else
									flag=0;
							}
						}	
					}
				}
			}
		}
	}
	return variavel;
}





void consoleLog(Tokens **aux,int y){
	//[console.log]->[(]->["]->[conteudo]
	*aux=(*aux)->prox->prox->prox;
	int x=28;
	if(*aux!=NULL){
		while((*aux)->token[0]!='"' && (*aux)->token[0]!=39){
			gotoxy(x,y);
			printf("%s ",(*aux)->token);
			*aux=(*aux)->prox;
		}
	}else{
		gotoxy(x,y);
		printf("Erro no console.log");
	}
	getch();
	
	//["]->[)] || ["]->[,]
	//*aux=(*aux)->prox;
	/*
	if((*aux)->token[0]==',' || (*aux)->token[0]=='+'){
		*aux=(*aux)->prox;
		calculaDoisNumeros(*aux);
	}*/
}
