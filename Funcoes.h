#ifndef FUNCOES_H   
#define FUNCOES_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "PilhaVar.h"
#include "ListaDeListasToken.h"
#include "ListaDeListasFunc.h"
#include "ListaGen.h"

struct flag{
	char erro;
	char executa;
	char If;
	char funcao;
};typedef struct flag Flag;

void iniciaFlag(Flag *flag){
	flag->erro=0;
	flag->executa=1;
	flag->If=1;
	flag->funcao=0;
}

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

var inicializaVar(int terminal){
    var v;
    v.nome[0] = '\0';         
    v.valorInt = 0;           
    v.valorFloat = 0.0f;     
	v.valorString[0] = '\0';  
    v.terminal = terminal;    
    return v;
}


var buscaVariavel(Pilha **p1,Tokens **aux){
	var x = inicializaVar(-1);
	var y = inicializaVar(-1);
	Pilha *p2;
	init(&p2);
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
	return inicializaVar(-1);
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
    var var1 = inicializaVar(-1);
	var var2 = inicializaVar(-1);
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
			                        	*flag=1;
								}else{
									var2 = buscaVariavel(&*p, &*aux);
                            		atribui(&var2, 1, &*aux );
                            	}
                			}else
                				*flag=1;
                		}else
							*flag=1;
					}else 
						*flag=1;
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
		                        	*flag=1;
							}else{
								var2 = buscaVariavel(&*p, &*aux);
                        		atribui(&var2, 1, &*aux );
							}
            			}else
            				*flag=1;
            		}else
						*flag=1;			
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
						                        	*flag=1;
											}else{
												var2 = buscaVariavel(&*p, &*aux);
			                            		atribui(&var2, 1, &*aux );
			                            	}
			                			}else
			                				*flag=1;
			                		}else
										*flag=1;
								}else 
									*flag=1;
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
					                        	*flag=1;
										}else{
											var2 = buscaVariavel(&*p, &*aux);
			                        		atribui(&var2, 1,&*aux );
										}
			            			}else
			            				*flag=1;
			            		}else
									*flag=1;			
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
					}else if(strcmp((*aux)->token,")")==0)
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


var declaracao(Tokens **aux,char *flag,Pilha *p){
	var variavel = inicializaVar(0);
	var teste = inicializaVar(-1);
	//mudar verificacao de int ou float ou string 
	teste = buscaVariavel(&p,&*aux);
	if(strcmp(teste.nome,(*aux)->token)!=0){
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
							while((*aux)->token[0]!='"' && *flag && (*aux)->token[0]!=39){
								if(*aux!=NULL){
									strcat(variavel.valorString,(*aux)->token);
									*aux=(*aux)->prox;
									if((*aux)->token[0]!=39 && (*aux)->token[0]!='"' && *aux!=NULL)
										strcat(variavel.valorString," ");
								} else
									*flag=1;
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

void function(Pilha **p,Tokens **aux,char *flag, LinhaF **linha){
	*aux=(*aux)->prox;
	if(*aux!=NULL){
		adicionarLinhaF(&*linha,(*aux)->token);
		*aux=(*aux)->prox;
		if(*aux!=NULL){
			if(strcmp((*aux)->token,"(")==0){
				*aux=(*aux)->prox;
				if(*aux!=NULL){
					while(*aux!=NULL && strcmp((*aux)->token,")")!=0){
						var teste = inicializaVar(-1);
						strcpy(teste.nome, (*aux)->token);
						push(&*p, teste); 
						adicionarTokenF(&*linha,teste);
						*aux=(*aux)->prox;
					    if (*aux != NULL && strcmp((*aux)->token, ",") == 0) {
					        *aux = (*aux)->prox; 
					    }		
					}	
				}else
					*flag=1;
			}else
				*flag=1;
		}else
			*flag=1;
	}else 
		*flag=1;
}

void atualizaVariavel(Pilha **p, var variavel){
	Pilha *p2;
	var compara;
	init(&p2); 
	while(!isEmpty(*p)){
		pop(&*p,&compara);
		if(strcmp(variavel.nome,compara.nome)==0){
			push(&p2,variavel);
		}else 
			push(&p2,compara);
	}
	while(!isEmpty(p2)){
		pop(&p2,&compara);
		push(&*p,compara);
	}
}

void chamaFuncao(LinhaF *linha, Tokens **aux, char *flag, Pilha **p){
	TokensF *auxf = linha->pTokens;
	var variavel; 
	while(*aux != NULL && strcmp((*aux)->token,")")!=0){
		var temp = inicializaVar(-1);
		strcpy(temp.nome,auxf->var.nome);
		if(*aux!=NULL){
			*aux=(*aux)->prox;
			if((*aux)->token[0]=='"' || (*aux)->token[0]==39){
				if(*aux!=NULL){
					*aux=(*aux)->prox;
				}else 
					*flag=1;
			}
			variavel = buscaVariavel(&*p,&*aux);
			if(variavel.terminal==1){
				temp.valorInt=variavel.valorInt;
				temp.terminal=1;
			}
			else if(variavel.terminal==2){
				temp.valorFloat=variavel.valorFloat;
				temp.terminal=2;
			}
			else if(variavel.terminal==3){
				strcpy(temp.valorString,variavel.valorString);
				temp.terminal=3;
			} else{
				if(Inteiro((*aux)->token)){
					temp.valorInt = converteInt((*aux)->token);
					temp.terminal=1;
				} else if(Float((*aux)->token)){
					temp.valorFloat = converteFloat((*aux)->token);
					temp.terminal=2;
				} else {
					temp.terminal=3;
				    while(*aux!=NULL && (*aux)->token[0]!='"' && (*aux)->token[0]!=39) {
				        strcat(temp.valorString, (*aux)->token); 
				        *aux = (*aux)->prox;                     
				        if ((*aux)->token[0]!=39 && (*aux)->token[0]!='"' && *aux!=NULL) {
				            strcat(temp.valorString, " ");
				        }
				    }
				}
			}
			atualizaVariavel(&*p, temp); 
			    auxf = auxf->prox;
			if(*aux != NULL && strcmp((*aux)->token, ",") == 0)
				*aux = (*aux)->prox;
			if (*aux != NULL)
	    		*aux = (*aux)->prox;
    	}else 
    		*flag=1;
	}
}


ListaGen *criaLista(Tokens **aux, Pilha **p, char *flag){
	var x = inicializaVar(-1);
	ListaGen *L = NULL;
	if (*aux == NULL) 
        *flag = 1;
	x = buscaVariavel(&*p,&*aux);
	if(x.terminal!=-1){
		L = Cons(x,NULL,criaLista(&(*aux)->prox,&*p,&*flag));		
	} else {
		if(Inteiro((*aux)->token)){
			x.terminal=1;
			x.valorInt=converteInt((*aux)->token);
			L = Cons(x,NULL,criaLista(&(*aux)->prox,&*p,&*flag));
		} else if(Float((*aux)->token)){
			x.terminal=2;
			x.valorFloat=converteFloat((*aux)->token);
			L = Cons(x,NULL,criaLista(&(*aux)->prox,&*p,&*flag));
		} else if(strcmp((*aux)->token,"(")==0){
 			*aux = (*aux)->prox; 
        	L = Cons(inicializaVar(-1), criaLista(aux, &*p, &*flag), criaLista(&(*aux)->prox, &*p, &*flag));
		} else if(strcmp((*aux)->token,")")==0){
				return NULL;
		} else {
			x.terminal=3;
			strcpy(x.valorString,(*aux)->token);
			L = Cons(x,NULL,criaLista(&(*aux)->prox,&*p,&*flag));
		}
	}
	return L;
}

void profundidade(ListaGen **aux){
    if(!Nula(*aux)){
        while(Nula(Head(*aux)))
            *aux = Tail(*aux);

        if(!Nula(*aux)){
            profundidade(&(*aux)->no.lista.cabeca);
            profundidade(&(*aux)->no.lista.cauda);
        }
    }
}


var calcula(ListaGen **L, char *flag){
	ListaGen *aux,*auxInicio,*auxOperador;
	var x = inicializaVar(-1);
	char oper[3];
	var y = inicializaVar(-1);
	var res = inicializaVar(-1);
	aux=*L;
	profundidade(&aux);
	while(!Nula(Tail(aux)) && !*flag){
		x = aux->info;
		auxInicio = aux;
		aux = Tail(aux);
		strcpy(oper,aux->info.valorString);
		auxOperador = aux;
		aux = Tail(aux);
		if(!Nula(aux)){
			y = aux->info;
			if(strcmp(oper,"+")==0){
				if(x.terminal==1 && y.terminal==1){
					res.terminal=1;
					res.valorInt=x.valorInt+y.valorInt;
				} else if(x.terminal==2 || y.terminal==2){
					res.terminal=2;
					if(x.terminal=1){
						res.valorFloat=x.valorInt+y.valorFloat;
					}else if(y.terminal=1){
						res.valorFloat=x.valorFloat+y.valorInt;
					}else{
						res.valorFloat=x.valorFloat+y.valorFloat;
					}
				}
			}else if(strcmp(oper,"-")==0){
				if(x.terminal==1 && y.terminal==1){
					res.terminal=1;
					res.valorInt=x.valorInt-y.valorInt;
				} else if(x.terminal==2 || y.terminal==2){
					res.terminal=2;
					if(x.terminal=1){
						res.valorFloat=x.valorInt-y.valorFloat;
					}else if(y.terminal=1){
						res.valorFloat=x.valorFloat-y.valorInt;
					}else{
						res.valorFloat=x.valorFloat-y.valorFloat;
					}
				}
			} else if(strcmp(oper,"*")==0){
				if(x.terminal==1 && y.terminal==1){
					res.terminal=1;
					res.valorInt=x.valorInt*y.valorInt;
				} else if(x.terminal==2 || y.terminal==2){
					res.terminal=2;
					if(x.terminal=1){
						res.valorFloat=x.valorInt*y.valorFloat;
					}else if(y.terminal=1){
						res.valorFloat=x.valorFloat*y.valorInt;
					}else{
						res.valorFloat=x.valorFloat*y.valorFloat;
					}
				}
			} else if(strcmp(oper,"/")==0){
				if(x.terminal==1 && y.terminal==1){
					res.terminal=1;
					res.valorInt=x.valorInt/y.valorInt;
				} else if(x.terminal==2 || y.terminal==2){
					res.terminal=2;
					if(x.terminal=1){
						res.valorFloat=x.valorInt/y.valorFloat;
					}else if(y.terminal=1){
						res.valorFloat=x.valorFloat/y.valorInt;
					}else{
						res.valorFloat=x.valorFloat/y.valorFloat;
					}
				}
			} else if(strcmp(oper,"**")==0){
				if(x.terminal==1 && y.terminal==1){
					res.terminal=1;
					res.valorInt=pow(x.valorInt,y.valorInt);
				} else if(x.terminal==2 || y.terminal==2){
					res.terminal=2;
					if(x.terminal=1){
						res.valorFloat=pow(x.valorInt,y.valorFloat);
					}else if(y.terminal=1){
						res.valorFloat=pow(x.valorFloat,y.valorInt);
					}else{
						res.valorFloat=pow(x.valorFloat,y.valorFloat);
					}
				}
			}
		} else 
			*flag=1;
	}
	return res;
}




void consoleLog(Tokens **aux,Linha **linha, char *flag, Pilha **p){
	var variavel;
	adicionarLinha(&*linha);
	//[console.log]->[(]->["]->[conteudo]
	*aux=(*aux)->prox->prox->prox;	
	if(*aux!=NULL){
		while((*aux)->token[0]!='"' && *flag && (*aux)->token[0]!=39){
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
