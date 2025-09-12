#ifndef FUNCOES_H   
#define FUNCOES_H

#include <stdio.h>
#include <string.h>
#include "Pilha.h"
#include "Trabalho.h"

struct flag{
	char erro;
	char If;
};typedef struct flag Flag;


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

char Digito(char c) {
	if (c >= '0' && c <= '9')
    	return 1;
    return 0;
}

char Inteiro(char str[]) {
	char flag=1;
	int i=0;
    while(str[i] != '\0') {
        if (!Digito(str[i])) {
            flag=0;
        }
        i++;
    }
    return flag; 
}

char Float(char str[]) {
    int ponto = 0; 
	char flag=1;
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

void converteStringInt(char str[], int num){
	int i = 0;
    int sinal = 0;
    if (num < 0) {
        sinal = 1;
        num = -num;
    }
    do {
        str[i++] = (num % 10) + '0';
        num /= 10;
    } while (num > 0);
    if (sinal) {
        str[i++] = '-';
    }
    str[i] = '\0';
    int inicio = 0, fim = i - 1;
    char temp;
    while (inicio < fim) {
        temp = str[inicio];
        str[inicio] = str[fim];
        str[fim] = temp;
        inicio++;
        fim--;
    }
}

void converteStringFloat(float num, char str[]) {
    int i = 0;
    if (num < 0) {
        str[i++] = '-';
        num = -num;
    }
    int parteInteira = (int)num;
    float parteFracionaria = num - parteInteira;
    char buffer[20];
    int j = 0;
    do {
        buffer[j++] = (parteInteira % 10) + '0';
        parteInteira /= 10;
    } while (parteInteira > 0);
    for (int k = j - 1; k >= 0; k--) {
        str[i++] = buffer[k];
    }
    str[i++] = '.';
    for (int k = 0; k < 2; k++) {
        parteFracionaria *= 10;
        int digito = (int)parteFracionaria;
        str[i++] = digito + '0';
        parteFracionaria -= digito;
    }
    str[i] = '\0';
}

var buscaVariavel(Pilha **p1,Tokens **aux){
	var x,y;
	Pilha *p2;
	char flag=0;
	while(!isEmpty(*p1) && !flag){
		pop(&*p1,&x);
		if(strcmp(x.nome,(*aux)->token)==0){
			flag=1;
		}
		push(&p2,x);
	}
	while(!isEmpty(p2)){
		pop(&p2,&y);
		push(&*p1,y);
	}
	if(flag)
		return x;
	x.terminal=-1;
	return x;
}

char compara(var var1, var var2,char comparador[]){
	if(strcmp(comparador,"==")==0){
	    if (var1.terminal == var2.terminal) {
	    	if(var1.terminal==1)
	        	return(var1.valorInt == var2.valorInt);
	        return (var1.valorFloat == var2.valorFloat);
	    } else 
	        if(var1.terminal==1)
	         	return (var1.valorInt == var2.valorFloat);
	    return (var1.valorFloat == var2.valorInt);
	} else if(strcmp(comparador,"!=")==0){
		if (var1.terminal == var2.terminal) {
	    	if(var1.terminal==1)
	        	return(var1.valorInt != var2.valorInt);
	        return (var1.valorFloat != var2.valorFloat);
	    } else 
	        if(var1.terminal==1)
	         	return (var1.valorInt != var2.valorFloat);
	    return (var1.valorFloat != var2.valorInt);	
	} else if(strcmp(comparador,">")==0){
		if (var1.terminal == var2.terminal) {
	    	if(var1.terminal==1)
	        	return(var1.valorInt > var2.valorInt);
	        return (var1.valorFloat > var2.valorFloat);
	    } else 
	        if(var1.terminal==1)
	         	return (var1.valorInt > var2.valorFloat);
	    return (var1.valorFloat > var2.valorInt);	
	}else if(strcmp(comparador,">=")==0){
		if (var1.terminal == var2.terminal) {
	    	if(var1.terminal==1)
	        	return(var1.valorInt >= var2.valorInt);
	        return (var1.valorFloat >= var2.valorFloat);
	    } else 
	        if(var1.terminal==1)
	         	return (var1.valorInt >= var2.valorFloat);
	    return (var1.valorFloat >= var2.valorInt);
	}else if(strcmp(comparador,"<")==0){
		if (var1.terminal == var2.terminal) {
	    	if(var1.terminal==1)
	        	return(var1.valorInt < var2.valorInt);
	        return (var1.valorFloat < var2.valorFloat);
	    } else 
	        if(var1.terminal==1)
	         	return (var1.valorInt < var2.valorFloat);
	    return (var1.valorFloat < var2.valorInt);	
	} else if(strcmp(comparador,"<=")==0){
		if (var1.terminal == var2.terminal) {
	    	if(var1.terminal==1)
	        	return(var1.valorInt <= var2.valorInt);
	        return (var1.valorFloat <= var2.valorFloat);
	    } else 
	        if(var1.terminal==1)
	         	return (var1.valorInt <= var2.valorFloat);
	    return (var1.valorFloat <= var2.valorInt);
	}
	
	
}

void atribui(var *var, int sinal, Tokens **aux){
    if (var->terminal == -1) {
		if(Inteiro((*aux)->token)){
			var->valorInt=converteInt((*aux)->token)*(sinal);
			var->terminal=1;
		} if(Float((*aux)->token)){
			var->valorFloat=converteFloat((*aux)->token)*(sinal);
			var->terminal=2;
		}
	}
	else
		if(var->terminal==1)
        	var->valorInt= var->valorInt * sinal;
        else
        	var->valorFloat=var->valorFloat*sinal;
}

char If(Pilha **p, Tokens **aux, char *flag) {
    var var1, var2;
    int num;
    float numf;
    char condicao1, condicao2;
	char logico[5];
	char comparador[5];
    *aux = (*aux)->prox;
    // NULL representa o fim da linha
    if (*aux != NULL) {
        if (strcmp((*aux)->token, "(") == 0) {
            *aux = (*aux)->prox;
            if (*aux != NULL) {
                if (strcmp((*aux)->token, "!") == 0) {
                    *aux = (*aux)->prox;
                    if (*aux != NULL) {
                    	var1 = buscaVariavel(&*p, &*aux);
                        atribui(&var1, -1, &*aux );
                        *aux = (*aux)->prox;
                        if (*aux != NULL) {
                            strcpy(comparador,(*aux)->token);
                            *aux = (*aux)->prox;
                            if (*aux != NULL) {
                            	if (strcmp((*aux)->token, "!") == 0) {
                            		*aux = (*aux)->prox;
                            		if (*aux != NULL) {
                            			var2 = buscaVariavel(&*p, &*aux);
		                                atribui(&var2, -1, &*aux );
			                        }else
			                        	*flag=-1;
								}else{
									var2 = buscaVariavel(&*p, &*aux);
                            		atribui(&var2, 1, &*aux );
                            	}
                			}else
                				*flag=-1;
                		}else
							*flag=-1;
					}else 
						*flag=-1;
				}else{
					var1 = buscaVariavel(&*p, &*aux);
                    atribui(&var1, 1, &*aux );
                    *aux = (*aux)->prox;
                    if (*aux != NULL) {
                        strcpy(comparador,(*aux)->token);
                        *aux = (*aux)->prox;
                        if (*aux != NULL) {
                        	if (strcmp((*aux)->token, "!") == 0) {
                        		*aux = (*aux)->prox;
                        		if (*aux != NULL) {
                        			var2 = buscaVariavel(&*p, &*aux);
	                                atribui(&var2, -1, &*aux );
		                        }else
		                        	*flag=-1;
							}else{
								var2 = buscaVariavel(&*p, &*aux);
                        		atribui(&var2, 1, &*aux );
							}
            			}else
            				*flag=-1;
            		}else
						*flag=-1;			
				}
				condicao1 = compara(var1,var2,comparador);
				//aqui comeca a condicao 2
				*aux = (*aux)->prox;
				if (*aux != NULL) {
					if (strcmp((*aux)->token, "&&") == 0 || strcmp((*aux)->token, "||") == 0) {
						strcpy(logico, (*aux)->token);
						*aux = (*aux)->prox;
						if (*aux != NULL) {
							if (strcmp((*aux)->token, "!") == 0) {
			                    *aux = (*aux)->prox;
			                    if (*aux != NULL) {
			                    	var1 = buscaVariavel(&*p, &*aux);
			                        atribui(&var1, -1, &*aux );
			                        *aux = (*aux)->prox;
			                        if (*aux != NULL) {
			                            strcpy(comparador,(*aux)->token);
			                            *aux = (*aux)->prox;
			                            if (*aux != NULL) {
			                            	if (strcmp((*aux)->token, "!") == 0) {
			                            		*aux = (*aux)->prox;
			                            		if (*aux != NULL) {
			                            			var2 = buscaVariavel(&*p, &*aux);
					                                atribui(&var2, -1, &*aux );
						                        }else
						                        	*flag=-1;
											}else{
												var2 = buscaVariavel(&*p, &*aux);
			                            		atribui(&var2, 1, &*aux );
			                            	}
			                			}else
			                				*flag=-1;
			                		}else
										*flag=-1;
								}else 
									*flag=-1;
							}else{
								var1 = buscaVariavel(&*p, &*aux);
			                    atribui(&var1, 1, &*aux );
			                    *aux = (*aux)->prox;
			                    if (*aux != NULL) {
			                        strcpy(comparador,(*aux)->token);
			                        *aux = (*aux)->prox;
			                        if (*aux != NULL) {
			                        	if (strcmp((*aux)->token, "!") == 0) {
			                        		*aux = (*aux)->prox;
			                        		if (*aux != NULL) {
			                        			var1 = buscaVariavel(&*p, &*aux);
				                                atribui(&var2, -1, &*aux );
					                        }else
					                        	*flag=-1;
										}else{
											var2 = buscaVariavel(&*p, &*aux);
			                        		atribui(&var2, 1,&*aux );
										}
			            			}else
			            				*flag=-1;
			            		}else
									*flag=-1;			
							}	
							condicao2 = compara(var1,var2,comparador);
							if(strcmp(logico,"&&")==0)
								return (condicao1 && condicao2);
							else if(strcmp(logico,"||")==0)
								return (condicao1 || condicao2);
							else
								*flag=1;
						}else 
							*flag=1;
					}else if(strcmp((*aux)->token,")"))
							return condicao1;
					else
						*flag=1;
				}else
					*flag=1;
			}else
				*flag=1;
    	}else 
			*flag=1;
	}else
		*flag=1;
    return 0; 
}


var declaracao(Tokens **aux,char *flag){
	var variavel;
	//mudar verificacao de int ou float ou string 
	variavel.terminal=0;
	strcpy(variavel.valorString, "");
	strcpy(variavel.nome, "");
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
							if(Inteiro((*aux)->token)){
								variavel.valorInt=-converteInt((*aux)->token);
								variavel.terminal=1;
							}
							/*
							if((*aux)->token->terminal = 1){
								converteInt((*aux)->token)
							}
							else if ((*aux)->token->terminal = 2){
								converteFloat((*aux)->token)
							}
							*/
							else if(Float((*aux)->token)){
								variavel.valorFloat=-converteFloat((*aux)->token);
								variavel.terminal=2;
							}
						}else
							*flag=1;
					}else{
						if(Inteiro((*aux)->token)){
							variavel.valorInt=converteInt((*aux)->token);
							variavel.terminal=1;
						}
						else if(Float((*aux)->token)){
							variavel.valorFloat=converteFloat((*aux)->token);
							variavel.terminal=2;
						}
						else if((*aux)->token[0]==39 || (*aux)->token[0]=='"'){
							*aux=(*aux)->prox;
							variavel.terminal=3;
							while((*aux)->token[0]!='"' && flag && (*aux)->token[0]!=39){
								if(*aux!=NULL){
									strcat(variavel.valorString,(*aux)->token);
									*aux=(*aux)->prox;
									if((*aux)->token[0]!=39 || (*aux)->token[0]!='"' || *aux!=NULL)
										strcat(variavel.valorString," ");
								} else
									flag=0;
							}
						}	
					}
				}else
					*flag=1;
			}else
				*flag=1;
		}
	}else 
		*flag=1;
	return variavel;
}



void consoleLog(Tokens **aux,Linha **linha, char *flag, Pilha **p){
	var variavel;
	float valor;
	char str[];
	adicionarLinha(&*linha);
	//[console.log]->[(]->["]->[conteudo] console.log("7",a) console.log(a,"7")
	//Se encontrou a variavel sozinha -> mostrar
	//Se econtrou calculo -> calcular -> mostrar
	*aux=(*aux)->prox->prox;
	while(*aux != NULL){
		if(strcmp((*aux)->token,'"')==0) || strcmp((*aux)->token,"'")==0) {
			while((*aux)->token[0]!='"' && (*aux)->token[0]!=39){
				adicionarToken(*linha,(*aux)->token);
				*aux=(*aux)->prox;
			}
		}else{
			if(strcmp((*aux)->token,'"')!=0) && strcmp((*aux)->token,"'")!=0){
				while(strcmp((*aux)->token,',')!=0)){
					//converte string para int
					valor = converteString((*aux)->token);
					//efetua o calculo e salva na variavel valor;
					
					
					//String -> int/float -> calcula -> String
					if(Float()){
						converteStringFloat()
						strcpy(str,converteString(valor))
					}
					
					else if(Int(valor))
						strcpy(str,converteString(valor))
					adicionarToken(*linha,str);
				}	
			}		
		}
	}
	//["]->[)] || ["]->[,]
	*aux=(*aux)->prox;
	if(*aux!=NULL){
		if(strcmp((*aux)->token,",")==0 || strcmp((*aux)->token,"+")==0){
			adicionarToken(*linha,(*aux)->token);
			*aux=(*aux)->prox;
			if(*aux!=NULL){
				variavel = buscaVariavel(&*p,&*aux);
				if(variavel.terminal!=-1){
					adicionarToken(*linha,(*aux)->token);
				}else
					*flag=1;
			}else 
				*flag=1;
		}
	}else 
		*flag=1;
}

#endif
