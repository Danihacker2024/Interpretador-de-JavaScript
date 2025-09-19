#ifndef FUNCOES_H   
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "PilhaVar.h"
#include "ListaDeListasToken.h"
#include "ListaDeListasFunc.h"
#include "ListaGen.h"
#include "PilhaListaGen.h"

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


ListaGen *criaNo(Tokens **aux,Pilha **p, char *flag){
	var x = inicializaVar(-1);
	union tipo Tipo = inicializaTipo();
	ListaGen *L;
	if(*aux==NULL)
		*flag=1;
	else{
		x = buscaVariavel(&*p,&*aux);
		if(x.terminal!=-1){
			if(x.terminal==1){
				Tipo.valor=x.valorInt;	
			} else if(x.terminal==2){
				Tipo.valor=x.valorFloat;
			} else 
				*flag=1;
			L = Cons(Tipo,NULL,NULL,'V');
		} else {
			if(Inteiro((*aux)->token)){
				Tipo.valor = converteInt((*aux)->token);
				L = Cons(Tipo,NULL,NULL,'V');		
			} else if(Float((*aux)->token)){
				Tipo.valor = converteFloat((*aux)->token);
				L = Cons(Tipo,NULL,NULL,'V');
			}else{
				if(strcmp((*aux)->token,"Math.sqrt")==0 || strcmp((*aux)->token,"Math.abs")==0){
					strcpy(Tipo.funcao,(*aux)->token);
					*aux=(*aux)->prox;
					if(*aux!=NULL){
						*aux=(*aux)->prox;
						if(*aux!=NULL){
							L = Cons(Tipo,NULL,criaNo(&*aux,&*p,&*flag),'F');
							L=L->cauda;
							*aux=(*aux)->prox;
						}else
							*flag=1;
					}else 
						*flag=1;
				} else {
					strcpy(Tipo.operador,(*aux)->token);
					L = Cons(Tipo,NULL,NULL,'O');
				}
			}
		}
	}
	return L;
}


int calculaSqrt(ListaGen **ant,ListaGen **aux,int x){
	x=(*aux)->info.valor;
	x=sqrt(x);
	if(!Nula((*aux)->cauda)){
		(*ant)->cauda=(*aux)->cauda;
		free(*aux);
		*aux=*ant;
		(*aux)->info.valor=x;
		return x;
	}
	return -1;	
}

int calculaAbs(ListaGen **ant,ListaGen **aux,int x){
	x=(*aux)->info.valor;
	x=abs(x);
	if(!Nula((*aux)->cauda)){
		(*ant)->cauda=(*aux)->cauda;
		free(*aux);
		*aux=*ant;
		(*aux)->info.valor=x;
		return x;
	}
	return -1;
}


float calcula(ListaGen **L,char *flag){
	ListaGen *aux,*ant,*ant2;
	float x=0,y;
	aux=*L;
	while(!Nula(*L)){
		//colocar como funcao
		if(strcmp(aux->info.funcao,"Math.sqrt")==0){
			ant=aux;
			aux=Tail(aux);
			if(aux!=NULL)
				x+=calculaSqrt(&ant, &aux, x);
			else
				*flag=1;
		}
		else if(strcmp(aux->info.funcao,"Math.abs")==0){
			ant=aux;
			aux=Tail(aux);
			if(aux!=NULL)
				x+=calculaAbs(&ant, &aux, x);
			else
				*flag=1;	
		}
		else{
			x=(*L)->info.valor;
			aux=Tail(aux);
			if(aux!=NULL){
				ant=aux;
				aux=Tail(aux);
				if(aux!=NULL){
					if(strcmp(ant->info.operador,"+")==0){
						if(aux->terminal=='V'){
							y=aux->info.valor;
							x+=y;
							(*L)->info.valor=x;
							(*L)->cauda=aux->cauda;
							free(aux);
							free(ant);
						}
						else{
							if(strcmp(aux->info.funcao,"Math.sqrt")==0){
								ant2=aux;
								y=calculaSqrt(&ant2, &aux, x);
							}
							else if(strcmp(aux->info.funcao,"Math.abs")==0){
								ant2=aux;
								y=calculaAbs(&ant2, &aux, x);
							}
							if(y!=-1){
								x+=y;
								(*L)->info.valor=x;
								(*L)->cauda=aux->cauda;
								free(aux);
								free(ant);
							}else
								*flag=1;
						}
					}else if(strcmp(ant->info.operador,"-")==0){ 
						if(aux->terminal=='V'){
							y=aux->info.valor;
							x-=y;
							(*L)->info.valor=x;
							(*L)->cauda=aux->cauda;
							free(aux);
							free(ant);
						}
						else{
							if(strcmp(aux->info.funcao,"Math.sqrt")==0){
								ant2=aux;
								y=calculaSqrt(&ant2, &aux, x);
							}
							else if(strcmp(aux->info.funcao,"Math.abs")==0){
								ant2=aux;
								y=calculaAbs(&ant2, &aux, x);
							}
							if(y!=-1){
							x-=y;
							(*L)->info.valor=x;
							(*L)->cauda=aux->cauda;
							free(aux);
							free(ant);
							}else
								*flag=1;
						}
					} else if(strcmp(ant->info.operador,"*")==0){
						if(aux->terminal=='V'){
							y=aux->info.valor;
							x*=y;
							(*L)->info.valor=x;
							(*L)->cauda=aux->cauda;
							free(aux);
							free(ant);
						}
						else{
							if(strcmp(aux->info.funcao,"Math.sqrt")==0){
								ant2=aux;
								y=calculaSqrt(&ant2, &aux, x);
							}
							else if(strcmp(aux->info.funcao,"Math.abs")==0){
								ant2=aux;
								y=calculaAbs(&ant2, &aux, x);
							}
							if(y!=-1){
							x*=y;
							(*L)->info.valor=x;
							(*L)->cauda=aux->cauda;
							free(aux);
							free(ant);
							}else 
								*flag=1;
						}	
					} else if(strcmp(ant->info.operador,"/")==0){
						if(aux->terminal=='V'){
							y=aux->info.valor;
							x/=y;
							(*L)->info.valor=x;
							(*L)->cauda=aux->cauda;
							free(aux);
							free(ant);
						}
						else{
							if(strcmp(aux->info.funcao,"Math.sqrt")==0){
								ant2=aux;
								y=calculaSqrt(&ant2, &aux, x);
							}
							else if(strcmp(aux->info.funcao,"Math.abs")==0){
								ant2=aux;
								y=calculaAbs(&ant2, &aux, x);
							}
							if(y!=-1){
							x/=y;
							(*L)->info.valor=x;
							(*L)->cauda=aux->cauda;
							free(aux);
							free(ant);
							}else{
								*flag=1;
							}
						}
					} else if(strcmp(ant->info.operador,"%")==0){
						if(aux->terminal=='V'){
							y=aux->info.valor;
							x= (int)x % (int)y;
							(*L)->info.valor=x;
							(*L)->cauda=aux->cauda;
							free(aux);
							free(ant);
						}
						else{
							if(strcmp(aux->info.funcao,"Math.sqrt")==0){
								ant2=aux;
								y=calculaSqrt(&ant2, &aux, x);
							}
							else if(strcmp(aux->info.funcao,"Math.abs")==0){
								ant2=aux;
								y=calculaAbs(&ant2, &aux, x);
							}
							if(y!=-1){
							x= (int)x % (int)y;
							(*L)->info.valor=x;
							(*L)->cauda=aux->cauda;
							free(aux);
							free(ant);
							}else 
								*flag=1;
						}
					} else if(strcmp(ant->info.operador,"**")==0){
						if(aux->terminal=='V'){
							y=aux->info.valor;
							x=pow(x,y);
							(*L)->info.valor=x;
							(*L)->cauda=aux->cauda;
							free(aux);
							free(ant);
						}
						else{
							if(strcmp(aux->info.funcao,"Math.sqrt")==0){
								ant2=aux;
								y=calculaSqrt(&ant2, &aux, x);
							}
							else if(strcmp(aux->info.funcao,"Math.abs")==0){
								ant2=aux;
								y=calculaAbs(&ant2, &aux, x);
							}
							if(y!=-1){
							x=pow(x,y);
							(*L)->info.valor=x;
							(*L)->cauda=aux->cauda;
							free(aux);
							free(ant);
							}else
								*flag=1;
						}
					}
				}else
					*flag=1;
			}else
				*flag=1;
		}
		aux=*L;
	}
	return x;
}


float resolveEquacao(Tokens **aux, Pilha **pVar, char *flag){
	 PilhaGen *p1,*p2;
	 float result=0.0f;
	 initGen(&p1), initGen(&p2);
	 ListaGen *l = NULL, *atual;
	 while(*aux!=NULL && (*aux)->token != NULL && !*flag){
		  if(l==NULL){
			   l=atual=criaNo(&*aux, &*pVar, &*flag);
			   if(!*flag)
			   	pushGen(&p2,l);
		  }
		  else if(strcmp((*aux)->token,"(")==0){
		  	(*aux)->token[0] = '0';
			(*aux)->token[1] = '\0';	
			atual -> cauda = criaNo(&*aux, &*pVar, &*flag);
			if(!*flag){
			    atual = atual -> cauda;
				pushGen(&p1,atual);
				*aux = (*aux)->prox;
				if(*aux!=NULL){
					atual->cabeca = criaNo(&*aux, &*pVar, &*flag);
					atual = atual->cabeca;
				}else 
					*flag=1;
			}
		  }
		  else if(strcmp((*aux)->token,")")==0){
		   	popGen(&p1,&atual);
		  }
		  else{
			   atual->cauda = criaNo(&*aux, &*pVar, &*flag);
			   atual = atual->cauda;
		  }
		  *aux = (*aux)->prox;
	 }
	 while(!isEmptyGen(p2)){
		  popGen(&p2,&atual);
		  if(l==atual)
		   	result = calcula(&l,&*flag);
		  else
		   	atual -> info.valor = calcula(&(atual->cabeca),&*flag);
	 }
	 return result;
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
