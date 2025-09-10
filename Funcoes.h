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
		
	}
	
	
}

void atribui(var *var, int sinal, Pilha **p, Tokens **aux ){
	var = buscaVariavel(&*p, &*aux);
    if (var.terminal == -1) {
		if(Inteiro((*aux)->token)){
			var.valorInt=converteInt((*aux)->token)*(sinal);
			var.terminal=1;
		} if(Float((*aux)->token)){
			var.valorFloat=converteFloat((*aux)->token)*(sinal);
			var.terminal=2;
		}
	}
	else
		if(var.terminal==1)
        	var.valorInt= var.valorInt * sinal;
        else
        	var.valorFloat=var.valorFloat*sinal;
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
                        atribui(&var1, -1, &*p, &*aux );
                        *aux = (*aux)->prox;
                        if (*aux != NULL) {
                            strcpy(comparador,(*aux)->token);
                            *aux = (*aux)->prox;
                            if (*aux != NULL) {
                            	if (strcmp((*aux)->token, "!") == 0) {
                            		*aux = (*aux)->prox;
                            		if (*aux != NULL) {
		                                atribui(&var2, -1, &*p, &*aux );
			                        }else
			                        	*flag=-1;
								}else
                            		atribui(&var2, 1, &*p, &*aux );
                			}else
                				*flag=-1;
                		}else
							*flag=-1;
					}else 
						*flag=-1;
				}else{
                    atribui(&var1, 1, &*p, &*aux );
                    *aux = (*aux)->prox;
                    if (*aux != NULL) {
                        strcpy(comparador,(*aux)->token);
                        *aux = (*aux)->prox;
                        if (*aux != NULL) {
                        	if (strcmp((*aux)->token, "!") == 0) {
                        		*aux = (*aux)->prox;
                        		if (*aux != NULL) {
	                                atribui(&var2, -1, &*p, &*aux );
		                        }else
		                        	*flag=-1;
							}else
                        		atribui(&var2, 1, &*p, &*aux );  
            			}else
            				*flag=-1;
            		}else
						*flag=-1;			
				}
				condicao1 = compara(var1,var2,comparador);
				
				
				
				
				
				
				
				
				
				
        	}
                                } else if (strcmp((*aux)->token, "!=") == 0) {
                                    *aux = (*aux)->prox;
                                    if (*aux != NULL) {
                                        var2 = buscaVariavel(&*p, &*aux);
                                        if (var2.terminal != -1) {
                                            if  (var1.terminal == 1 && var2.terminal==1){
                                                condicao1 = (var1.valorInt != !var2.valorInt);
                                            } else if (var1.terminal == 2 && var2.terminal==2) {
                                                condicao1 = (var1.valorFloat != !var2.valorFloat);
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Inteiro((*aux)->token)) {
                                            num = converteInt((*aux)->token);
                                            if  (var1.terminal == 1){
                                                condicao1 = (var1.valorInt != !num);
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Float((*aux)->token)) {
                                            numf = converteFloat((*aux)->token);
                                            if (var1.terminal==2) {
                                                condicao1 = (var1.valorFloat != !numf);
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else {
                                            *flag = 1;
                                        }
                                    } else {
                                        *flag = 1;
                                    }
                                } else if ((*aux)->token[0] == '<') {
                                    *aux = (*aux)->prox;
                                    if (*aux != NULL) {
                                        var2 = buscaVariavel(&*p, &*aux);
                                        if (var2.terminal != -1) {
                                            if  (var1.terminal == 1 && var2.terminal==1){
                                                condicao1 = (var1.valorInt < !var2.valorInt);
                                            } else if  (var1.terminal == 2 && var2.terminal==2){
                                                condicao1 = (var1.valorFloat < !var2.valorFloat);
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Inteiro((*aux)->token)) {
                                            num = converteInt((*aux)->token);
                                            if  (var1.terminal == 1){
                                                condicao1 = (var1.valorInt < !num);
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Float((*aux)->token)) {
                                            numf = converteFloat((*aux)->token);
                                            if (var1.terminal == 2)  {
                                                condicao1 = (var1.valorFloat < !numf);
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else {
                                            *flag = 1;
                                        }
                                    } else {
                                        *flag = 1;
                                    }
                                } else if ((*aux)->token[0] == '>') {
                                    *aux = (*aux)->prox;
                                    if (*aux != NULL) {
                                        var2 = buscaVariavel(&*p, &*aux);
                                        if (var2.terminal != -1) {
                                            if  (var1.terminal == 1 && var2.terminal==1){
                                                condicao1 = (var1.valorInt > !var2.valorInt);
                                            } else if  (var1.terminal == 2 && var2.terminal==2){
                                                condicao1 = (var1.valorFloat > !var2.valorFloat);
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Inteiro((*aux)->token)) {
                                            num = converteInt((*aux)->token);
                                            if  (var1.terminal == 1){
                                                condicao1 = (var1.valorInt > !num);
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Float((*aux)->token)) {
                                            numf = converteFloat((*aux)->token);
                                            if (var1.terminal == 2)  {
                                                condicao1 = (var1.valorFloat > !numf);
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else {
                                            *flag = 1;
                                        }
                                    } else {
                                        *flag = 1;
                                    }
                                } else if (strcmp((*aux)->token, ">=") == 0) {
                                    *aux = (*aux)->prox;
                                    if (*aux != NULL) {
                                        var2 = buscaVariavel(&*p, &*aux);
                                        if (var2.terminal != -1) {
                                            if  (var1.terminal == 1 && var2.terminal==1){
                                                condicao1 = (var1.valorInt >= !var2.valorInt);
                                            } else if  (var1.terminal == 2 && var2.terminal==2){
                                                condicao1 = (var1.valorFloat >= !var2.valorFloat);
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Inteiro((*aux)->token)) {
                                            num = converteInt((*aux)->token);
                                            if  (var1.terminal == 1){
                                                condicao1 = (var1.valorInt >= !num);
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Float((*aux)->token)) {
                                            numf = converteFloat((*aux)->token);
                                            if (var1.terminal == 2)  {
                                                condicao1 = (var1.valorFloat >= !numf);
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else {
                                            *flag = 1;
                                        }
                                    } else {
                                        *flag = 1;
                                    }
                                } else if (strcmp((*aux)->token, "<=") == 0) {
                                    *aux = (*aux)->prox;
                                    if (*aux != NULL) {
                                        var2 = buscaVariavel(&*p, &*aux);
                                        if (var2.terminal != -1) {
                                            if  (var1.terminal == 1 && var2.terminal==1){
                                                condicao1 = (var1.valorInt <= !var2.valorInt);
                                            } else if  (var1.terminal == 2 && var2.terminal==2){
                                                condicao1 = (var1.valorFloat <= !var2.valorFloat);
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Inteiro((*aux)->token)) {
                                            num = converteInt((*aux)->token);
                                            if  (var1.terminal == 1){
                                                condicao1 = (var1.valorInt <= !num);
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Float((*aux)->token)) {
                                            numf = converteFloat((*aux)->token);
                                            if (var1.terminal == 2) {
                                                condicao1 = (var1.valorFloat <= !numf);
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else {
                                            *flag = 1;
                                        }
                                    } else {
                                        *flag = 1;
                                    }
                                }
                            }
                        } else {
                            *flag = 1;
                        }
                    } else {
                        *flag = 1;
                    }
                } else {
                    var1 = buscaVariavel(&*p, &*aux);
                    if (var1.terminal != -1) {
                        *aux = (*aux)->prox;
                        if (*aux != NULL) {
                            if (strcmp((*aux)->token, "==") == 0) {
                                *aux = (*aux)->prox;
                                if (*aux != NULL) {
                                    var2 = buscaVariavel(&*p, &*aux);
                                    // onde parei
                                    if (var2.terminal != -1) {
                                        if  (var1.terminal == 1 && var2.terminal==1){
                                            condicao1 = (var1.valorInt == var2.valorInt);
                                        } else if  (var1.terminal == 2 && var2.terminal==2){
                                            condicao1 = (var1.valorFloat == var2.valorFloat);
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Inteiro((*aux)->token)) {
                                        num = converteInt((*aux)->token);
                                        if  (var1.terminal == 1){
                                            condicao1 = (var1.valorInt == num);
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Float((*aux)->token)) {
                                        numf = converteFloat((*aux)->token);
                                        if (var1.terminal == 2)  {
                                            condicao1 = (var1.valorFloat == numf);
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else {
                                        *flag = 1;
                                    }
                                } else {
                                    *flag = 1;
                                }
                            } else if (strcmp((*aux)->token, "!=") == 0) {
                                *aux = (*aux)->prox;
                                if (*aux != NULL) {
                                    var2 = buscaVariavel(&*p, &*aux);
                                    if (var2.terminal != -1) {
                                        if  (var1.terminal == 1 && var2.terminal==1){
                                            condicao1 = (var1.valorInt != var2.valorInt);
                                        } else if  (var1.terminal == 2 && var2.terminal==2){
                                            condicao1 = (var1.valorFloat != var2.valorFloat);
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Inteiro((*aux)->token)) {
                                        num = converteInt((*aux)->token);
                                        if  (var1.terminal == 1){
                                            condicao1 = (var1.valorInt != num);
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Float((*aux)->token)) {
                                        numf = converteFloat((*aux)->token);
                                        if (var1.terminal == 2) {
                                            condicao1 = (var1.valorFloat != numf);
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else {
                                        *flag = 1;
                                    }
                                } else {
                                    *flag = 1;
                                }
                            } else if ((*aux)->token[0] == '<') {
                                *aux = (*aux)->prox;
                                if (*aux != NULL) {
                                    var2 = buscaVariavel(&*p, &*aux);
                                    if (var2.terminal != -1) {
                                        if  (var1.terminal == 1 && var2.terminal==1){
                                            condicao1 = (var1.valorInt < var2.valorInt);
                                        } else if  (var1.terminal == 2 && var2.terminal==2){
                                            condicao1 = (var1.valorFloat < var2.valorFloat);
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Inteiro((*aux)->token)) {
                                        num = converteInt((*aux)->token);
                                        if  (var1.terminal == 1){
                                            condicao1 = (var1.valorInt < num);
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Float((*aux)->token)) {
                                        numf = converteFloat((*aux)->token);
                                        if (var1.terminal == 2) {
                                            condicao1 = (var1.valorFloat < numf);
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else {
                                        *flag = 1;
                                    }
                                } else {
                                    *flag = 1;
                                }
                            } else if ((*aux)->token[0] == '>') {
                                *aux = (*aux)->prox;
                                if (*aux != NULL) {
                                    var2 = buscaVariavel(&*p, &*aux);
                                    if (var2.terminal != -1) {
                                        if  (var1.terminal == 1 && var2.terminal==1){
                                            condicao1 = (var1.valorInt > var2.valorInt);
                                        } else if  (var1.terminal == 2 && var2.terminal==2){
                                            condicao1 = (var1.valorFloat > var2.valorFloat);
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Inteiro((*aux)->token)) {
                                        num = converteInt((*aux)->token);
                                        if  (var1.terminal == 1){
                                            condicao1 = (var1.valorInt > num);
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Float((*aux)->token)) {
                                        numf = converteFloat((*aux)->token);
                                        if (var1.terminal == 2)  {
                                            condicao1 = (var1.valorFloat > numf);
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else {
                                        *flag = 1;
                                    }
                                } else {
                                    *flag = 1;
                                }
                            } else if (strcmp((*aux)->token, ">=") == 0) {
                            	//parei aqui
                                *aux = (*aux)->prox;
                                if (*aux != NULL) {
                                    var2 = buscaVariavel(&*p, &*aux);
                                    if (var2.terminal != -1) {
                                        if  {
                                            condicao1 = (var1.valorInt >= var2.valorInt);
                                        } else if  {
                                            condicao1 = (var1.valorFloat >= var2.valorFloat);
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Inteiro((*aux)->token)) {
                                        num = converteInt((*aux)->token);
                                        if  {
                                            condicao1 = (var1.valorInt >= num);
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Float((*aux)->token)) {
                                        numf = converteFloat((*aux)->token);
                                        if (var1.valorInt >= numf ||  {
                                            condicao1 = (var1.valorFloat >= numf);
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else {
                                        *flag = 1;
                                    }
                                } else {
                                    *flag = 1;
                                }
                            } else if (strcmp((*aux)->token, "<=") == 0) {
                                *aux = (*aux)->prox;
                                if (*aux != NULL) {
                                    var2 = buscaVariavel(&*p, &*aux);
                                    if (var2.valorInt != -1) {
                                        if (var1.valorInt <= var2.valorInt) {
                                            condicao1 = 1;
                                        } else if (var1.valorFloat <= var2.valorFloat) {
                                            condicao1 = 1;
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Inteiro((*aux)->token)) {
                                        num = converteInt((*aux)->token);
                                        if (var1.valorInt <= num) {
                                            condicao1 = 1;
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Float((*aux)->token)) {
                                        numf = converteFloat((*aux)->token);
                                        if (var1.valorInt <= numf || var1.valorFloat <= numf) {
                                            condicao1 = 1;
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else {
                                        *flag = 1;
                                    }
                                } else {
                                    *flag = 1;
                                }
                            }
                            //aqui comeÃ§a a condiÃ§Ã£o 2
							*aux = (*aux)->prox;
							if (*aux != NULL) {
							    if (strcmp((*aux)->token, "&&") == 0 || strcmp((*aux)->token, "||") == 0) {
							        strcpy(logico, (*aux)->token);  // guarda o operador lógico
							        *aux = (*aux)->prox;
							        if (*aux != NULL) {
							            // --------------------------
							            // Condição 2 COM !
							            // --------------------------
							            if (strcmp((*aux)->token, "!") == 0) {
							                *aux = (*aux)->prox;
							                if (*aux != NULL) {
							                    var1 = buscaVariavel(&*p, &*aux);
							                    if (var1.terminal != -1) {
							                        *aux = (*aux)->prox;
							                        if (*aux != NULL) {
							                            if (strcmp((*aux)->token, "==") == 0) {
							                                *aux = (*aux)->prox;
							                                if (*aux != NULL) {
							                                    var2 = buscaVariavel(&*p, &*aux);
							                                    if (var2.terminal != -1) {
							                                        if (var1.terminal == 1 && var2.terminal == 1)
							                                            condicao2 = (var1.valorInt == !var2.valorInt);
							                                        else if (var1.terminal == 2 && var2.terminal == 2)
							                                            condicao2 = (var1.valorFloat == !var2.valorFloat);
							                                        else condicao2 = 0;
							                                    } else if (Inteiro((*aux)->token) && var1.terminal == 1) {
							                                        num = converteInt((*aux)->token);
							                                        condicao2 = (var1.valorInt == !num);
							                                    } else if (Float((*aux)->token) && var1.terminal == 2) {
							                                        numf = converteFloat((*aux)->token);
							                                        condicao2 = (var1.valorFloat == !numf);
							                                    } else *flag = 1;
							                                } else *flag = 1;
							                            }
							                            else if (strcmp((*aux)->token, "!=") == 0) {
							                                *aux = (*aux)->prox;
							                                if (*aux != NULL) {
							                                    var2 = buscaVariavel(&*p, &*aux);
							                                    if (var2.terminal != -1) {
							                                        if (var1.terminal == 1 && var2.terminal == 1)
							                                            condicao2 = (var1.valorInt != !var2.valorInt);
							                                        else if (var1.terminal == 2 && var2.terminal == 2)
							                                            condicao2 = (var1.valorFloat != !var2.valorFloat);
							                                        else condicao2 = 0;
							                                    } else if (Inteiro((*aux)->token) && var1.terminal == 1) {
							                                        num = converteInt((*aux)->token);
							                                        condicao2 = (var1.valorInt != !num);
							                                    } else if (Float((*aux)->token) && var1.terminal == 2) {
							                                        numf = converteFloat((*aux)->token);
							                                        condicao2 = (var1.valorFloat != !numf);
							                                    } else *flag = 1;
							                                } else *flag = 1;
							                            }
							                            else if (strcmp((*aux)->token, "<") == 0) {
							                                *aux = (*aux)->prox;
							                                if (*aux != NULL) {
							                                    var2 = buscaVariavel(&*p, &*aux);
							                                    if (var2.terminal != -1) {
							                                        if (var1.terminal == 1 && var2.terminal == 1)
							                                            condicao2 = (var1.valorInt < !var2.valorInt);
							                                        else if (var1.terminal == 2 && var2.terminal == 2)
							                                            condicao2 = (var1.valorFloat < !var2.valorFloat);
							                                        else condicao2 = 0;
							                                    } else if (Inteiro((*aux)->token) && var1.terminal == 1) {
							                                        num = converteInt((*aux)->token);
							                                        condicao2 = (var1.valorInt < !num);
							                                    } else if (Float((*aux)->token) && var1.terminal == 2) {
							                                        numf = converteFloat((*aux)->token);
							                                        condicao2 = (var1.valorFloat < !numf);
							                                    } else *flag = 1;
							                                } else *flag = 1;
							                            }
							                            else if (strcmp((*aux)->token, ">") == 0) {
							                                *aux = (*aux)->prox;
							                                if (*aux != NULL) {
							                                    var2 = buscaVariavel(&*p, &*aux);
							                                    if (var2.terminal != -1) {
							                                        if (var1.terminal == 1 && var2.terminal == 1)
							                                            condicao2 = (var1.valorInt > !var2.valorInt);
							                                        else if (var1.terminal == 2 && var2.terminal == 2)
							                                            condicao2 = (var1.valorFloat > !var2.valorFloat);
							                                        else condicao2 = 0;
							                                    } else if (Inteiro((*aux)->token) && var1.terminal == 1) {
							                                        num = converteInt((*aux)->token);
							                                        condicao2 = (var1.valorInt > !num);
							                                    } else if (Float((*aux)->token) && var1.terminal == 2) {
							                                        numf = converteFloat((*aux)->token);
							                                        condicao2 = (var1.valorFloat > !numf);
							                                    } else *flag = 1;
							                                } else *flag = 1;
							                            }
							                            else if (strcmp((*aux)->token, ">=") == 0) {
							                                *aux = (*aux)->prox;
							                                if (*aux != NULL) {
							                                    var2 = buscaVariavel(&*p, &*aux);
							                                    if (var2.terminal != -1) {
							                                        if (var1.terminal == 1 && var2.terminal == 1)
							                                            condicao2 = (var1.valorInt >= !var2.valorInt);
							                                        else if (var1.terminal == 2 && var2.terminal == 2)
							                                            condicao2 = (var1.valorFloat >= !var2.valorFloat);
							                                        else condicao2 = 0;
							                                    } else if (Inteiro((*aux)->token) && var1.terminal == 1) {
							                                        num = converteInt((*aux)->token);
							                                        condicao2 = (var1.valorInt >= !num);
							                                    } else if (Float((*aux)->token) && var1.terminal == 2) {
							                                        numf = converteFloat((*aux)->token);
							                                        condicao2 = (var1.valorFloat >= !numf);
							                                    } else *flag = 1;
							                                } else *flag = 1;
							                            }
							                            else if (strcmp((*aux)->token, "<=") == 0) {
							                                *aux = (*aux)->prox;
							                                if (*aux != NULL) {
							                                    var2 = buscaVariavel(&*p, &*aux);
							                                    if (var2.terminal != -1) {
							                                        if (var1.terminal == 1 && var2.terminal == 1)
							                                            condicao2 = (var1.valorInt <= !var2.valorInt);
							                                        else if (var1.terminal == 2 && var2.terminal == 2)
							                                            condicao2 = (var1.valorFloat <= !var2.valorFloat);
							                                        else condicao2 = 0;
							                                    } else if (Inteiro((*aux)->token) && var1.terminal == 1) {
							                                        num = converteInt((*aux)->token);
							                                        condicao2 = (var1.valorInt <= !num);
							                                    } else if (Float((*aux)->token) && var1.terminal == 2) {
							                                        numf = converteFloat((*aux)->token);
							                                        condicao2 = (var1.valorFloat <= !numf);
							                                    } else *flag = 1;
							                                } else *flag = 1;
							                            }
							                        }
							                    } else *flag = 1;
							                } else *flag = 1;
							            }
							            *aux=(*aux)->prox;
										if(strcmp(logico,"&&")==0)
											return (condicao1 && condicao2);
										else
											return (condicao1 || condicao2);
							        } else *flag = 1;
							    }
							    if((*aux)->token[0]==')')
							    	return condicao1;
							    else
							    	*flag=1;
							}else 
								*flag = 1;

                        }
                    } else {
                        *flag = 1;
                    }
                }
            } else {
                *flag = 1;
            }
        } else {
            *flag = 1;
        }
    } else {
        *flag = 1;
    }
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
				//tem que verificar se Ã© negativo
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
	adicionarLinha(&*linha);
	//[console.log]->[(]->["]->[conteudo]
	*aux=(*aux)->prox->prox->prox;	
	if(*aux!=NULL){
		while((*aux)->token[0]!='"' && (*aux)->token[0]!=39){
			adicionarToken(*linha,(*aux)->token);
			*aux=(*aux)->prox;
		}
	}else{
		*flag=1;
	}
	//["]->[)] || ["]->[,]
	*aux=(*aux)->prox;
	if(*aux!=NULL){
		if(strcmp((*aux)->token,",")==0 || strcmp((*aux)->token,"+")==0){
			adicionarToken(*linha,(*aux)->token);
			*aux=(*aux)->prox;
			if(*aux!=NULL){
				variavel = buscaVariavel(&*p,&*aux);
				if(variavel.valorInt!=-1){
					if(variavel.valorInt!=NULL){
						adicionarToken(*linha,(*aux)->token);
					}
				}else
					*flag=1;
			}else 
				*flag=1;
		}
	}else 
		*flag=1;
}

#endif
