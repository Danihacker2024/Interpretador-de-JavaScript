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
	char While;
	char Do;
	char For;
	int terminal;
};typedef struct flag Flag;

void iniciaFlag(Flag *flag){
	flag->erro=0;
	flag->executa=1;
	flag->If=1;
	flag->funcao=0;
	flag->Do=0;
	flag->While=0;
	flag->For=0;
	flag->terminal=0;
}



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
			}else//copiar ate aqui
				*flag=1;
    	}else //copiar ate aqui
			*flag=1;
	}else
		*flag=1;
    return 0; 
}

char comparacaoSemParenteses(Pilha **p, Tokens **aux, char *flag) {
	var var1 = inicializaVar(-1);
	var var2 = inicializaVar(-1);
    int num;
    float numf;
    char condicao1, condicao2;
	char logico[5];
	char comparador[5];
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
		return condicao1;
	}
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
							if(*aux != NULL && (*aux)->prox!=NULL && ((*aux)->prox->token[0]==39 || (*aux)->prox->token[0]=='"')){
								strcpy(variavel.valorString, (*aux)->token);
    							*aux = (*aux)->prox;
							}else{
								while (*aux != NULL && *flag && (*aux)->token[0] != '"' && (*aux)->token[0] != 39) {
								    strcat(variavel.valorString, (*aux)->token);
								
								    *aux = (*aux)->prox;
								
								    if (*aux != NULL && (*aux)->token[0] != 39 && (*aux)->token[0] != '"')
								        strcat(variavel.valorString, " ");
								}
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

void atribuicao(Tokens **aux, Pilha **p, char *flag, var *var){
	struct variavel var2=inicializaVar(-1);
	var2 = buscaVariavel(&*p,&*aux);
	if(var2.terminal==1){
		(*var).valorInt=var2.valorInt;
		(*var).terminal=1;
		(*var).valorFloat=0.00;
		(*var).valorString[0]='\0';
	} else if(var2.terminal==2){
		(*var).valorFloat=var2.valorFloat;
		(*var).terminal=2;
		(*var).valorInt=0;
		(*var).valorString[0]='\0';
	} else if(var2.terminal==3){
		strcpy((*var).valorString,var2.valorString);
		(*var).terminal=3;
		(*var).valorInt=0;
		(*var).valorFloat=0.00f;
	}else if(Inteiro((*aux)->token)){
		(*var).valorInt=converteInt((*aux)->token);
		(*var).terminal=1;
		(*var).valorFloat=0.00;
		(*var).valorString[0]='\0';
	} else if(Float((*aux)->token)){
		(*var).valorFloat=converteFloat((*aux)->token);
		(*var).terminal=2;
		(*var).valorInt=0;
		(*var).valorString[0]='\0';
	} else
		*flag=1;
}





//inicio de calculos aritmeticos
//rever criaNo
ListaGen *criaNo(Tokens **aux,Pilha **p, char *flag){
	var x = inicializaVar(-1);
	union tipo Tipo = inicializaTipo();
	ListaGen *L=NULL;
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
				Tipo.valor = (float)converteInt((*aux)->token);
				L = Cons(Tipo,NULL,NULL,'V');		
			} else if(Float((*aux)->token)){
				Tipo.valor = converteFloat((*aux)->token);
				L = Cons(Tipo,NULL,NULL,'V');
			}else{
				if(strcmp((*aux)->token,"Math.sqrt")==0 || strcmp((*aux)->token,"Math.abs")==0){
					strcpy(Tipo.funcao,(*aux)->token);
					L = Cons(Tipo,NULL,NULL,'F');
				} else {
					strcpy(Tipo.operador,(*aux)->token);
					L = Cons(Tipo,NULL,NULL,'O');
				}
			}
		}
	}
	return L;
}



float calculaPilha(PilhaGen **pO,PilhaGen **pV){
	ListaGen *aux=(ListaGen*)malloc(sizeof(ListaGen));
	float x,y,res=0;
	char op[20];
	int i=1;
	while(!isEmptyGen(*pO)){
		popGen(&*pO,&aux);
		if(aux->terminal=='O')	
			strcpy(op,aux->info.operador);
		else
			strcpy(op,aux->info.funcao);
		popGen(&*pV,&aux);
		y=aux->info.valor;
		//printf("repeticao: %d      ", i);
		//printf("y = %.2f     ",y);
		if(stricmp(op,"Math.sqrt")!=0 && stricmp(op,"Math.abs")!=0){
			if(res==0){
				popGen(&*pV,&aux);
				x=aux->info.valor;
			}
			else
				x=res;
			//printf("x = %.2f    ",x);
			//printf("op = %s     ",op);	
			if(strcmp(op,"+")==0)
				res = x+y;
			else if(strcmp(op,"-")==0)
				res = y-x;
			else if(strcmp(op,"*")==0)
				res = x*y;	
			else if(strcmp(op,"/")==0)
				res = x/y;
			else if(strcmp(op,"**")==0)
				res = pow(x,y);	
			else if(strcmp(op,"%")==0)
				res = (int)x % (int)y;
		} else if(stricmp(op,"Math.sqrt")==0)
			res = sqrt(y);
		else if(stricmp(op,"Math.abs")==0)
			res = abs(y);
		//printf("res = %.2f    ",res);
		//aux->info.valor = res;
		//pushGen(&*pV,aux);
		i++;
	}
	return res;
}



float calcula(ListaGen **L,char *flag){
	ListaGen *aux=(ListaGen*)malloc(sizeof(ListaGen));
	ListaGen *ant=(ListaGen*)malloc(sizeof(ListaGen));
	ListaGen *aux2=(ListaGen*)malloc(sizeof(ListaGen));
	PilhaGen *pV, *pO, *pVaux, *pOaux;
	float result=0;
	initGen(&pVaux);
	initGen(&pOaux);
	initGen(&pV);
	initGen(&pO);
	float x=0.0f,y;
	aux=*L;
	while(!Nula(aux)){
		if(strcmp(aux->info.operador,"+")==0 || strcmp(aux->info.operador,"-")==0){
			pushGen(&pVaux,ant);
			pushGen(&pOaux,aux);
			aux=Tail(aux);
			pushGen(&pVaux,aux);
		}
		ant=aux;			
		aux=Tail(aux);
	}
	while(!isEmptyGen(pOaux)){
		if(!isEmptyGen(pVaux)){
			popGen(&pVaux,&aux2);
			pushGen(&pV,aux2);
			popGen(&pVaux,&aux2);
			pushGen(&pV,aux2);
		}
		popGen(&pOaux,&aux2);
		pushGen(&pO,aux2);
	}
	aux=*L;
	while(!Nula(aux)){
		
		if(strcmp(aux->info.operador,"*")==0 || strcmp(aux->info.operador,"/")==0 || strcmp(aux->info.operador,"%")==0){
			if(ant!=topGen(pV))
				pushGen(&pV,ant);
			pushGen(&pO,aux);
			aux=Tail(aux);
			pushGen(&pV,aux);		
		}
		ant=aux;
		aux=Tail(aux);
	}
	aux=*L;
	while(!Nula(aux)){
		if(strcmp(aux->info.operador,"**")==0 || strcmp(aux->info.funcao,"Math.sqrt")==0 || strcmp(aux->info.funcao,"Math.abs")==0){
			if(strcmp(aux->info.operador,"**")==0){
				if(ant!=topGen(pV))
					pushGen(&pV,ant);
				pushGen(&pO,aux);
				aux=Tail(aux);
				pushGen(&pV,aux);		
			}else if(strcmp(aux->info.funcao,"Math.sqrt")==0 || strcmp(aux->info.funcao,"Math.abs")==0){
				pushGen(&pO,aux);
				aux=Tail(aux);
				pushGen(&pV,aux);
			}
		}
		ant=aux;
		aux=Tail(aux);
	}
	result = calculaPilha(&pO,&pV);
	aux=*L;
	while(!Nula(aux)){
		ant=aux;
		free(ant);
		aux=Tail(aux);
	}	
	return result;
}

float resolveEquacao(Tokens **aux, Pilha **pVar, char *flag){
	 PilhaGen *p1,*p2;
	 float result=0.0f;
	 initGen(&p1), initGen(&p2);
	 ListaGen *l = NULL, *atual;
	 char funcao=0;
	
	 while(*aux!=NULL && !*flag){
		  if(l==NULL){
			   l=atual=criaNo(&*aux, &*pVar, &*flag);
			   if(l->terminal=='F')
			   	funcao=1;
			   if(!*flag)
			   	pushGen(&p2,l);
		  }
		  else if(strcmp((*aux)->token,"(")==0 && !funcao){
		  	(*aux)->token[0] = '0';
			(*aux)->token[1] = '\0';	
			atual -> cauda = criaNo(&*aux, &*pVar, &*flag);
			if(!*flag){
			    atual = atual -> cauda;
				pushGen(&p1,atual);
				pushGen(&p2,atual);
				*aux = (*aux)->prox;
				if(*aux!=NULL){
					atual->cabeca = criaNo(&*aux, &*pVar, &*flag);
					atual = atual->cabeca;
				}else 
					*flag=1;
			}
		  }
		  else if(strcmp((*aux)->token,")")==0){
		   		if(!funcao)
			   popGen(&p1,&atual);
			   else
			   	funcao=1;
		  }
		  else{
		  	if(strcmp((*aux)->token,"(")!=0){
			   atual->cauda = criaNo(&*aux, &*pVar, &*flag);
			   atual = atual->cauda;
			   if(l->terminal=='F')
			   	funcao=1;
			}
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

void consoleLog(Tokens **aux, Linha **linha, char *flag, Pilha **p) {
    char str[50];
    var variavel;
    adicionarLinha(&*linha);
    *linha = buscaLinha(*linha);

	if (*aux!=NULL) 
		*aux = (*aux)->prox;  
	if (*aux!=NULL) 
		*aux = (*aux)->prox; 	

    while (*aux && strcmp((*aux)->token, ")") != 0) {
        if ((*aux)->token[0] == '"' || (*aux)->token[0] == '\'') {
        	*aux = (*aux)->prox;
			while (*aux != NULL && (*aux)->token[0] != '"' && (*aux)->token[0] != '\'') {
				adicionarToken(*linha, (*aux)->token);
				*aux = (*aux)->prox;
    		}
    		if(*aux!=NULL)
    			*aux = (*aux)->prox;
        } else {
            variavel = buscaVariavel(p, aux);

            if (variavel.terminal == -1) {
			    if (Inteiro((*aux)->token)) {
			        variavel.valorInt = converteInt((*aux)->token);
			        variavel.terminal = 1;
			        *aux = (*aux)->prox; 
			    } else if (Float((*aux)->token)) {
			        variavel.valorFloat = converteFloat((*aux)->token);
			        variavel.terminal = 2;
			        *aux = (*aux)->prox; 
			    } else {
			        variavel.valorFloat = resolveEquacao(&*aux, &*p, &*flag);
			        variavel.terminal = 2;
			    }
            }

            if (variavel.terminal == 1) { 
                itoa(variavel.valorInt, str, 10);
                adicionarToken(*linha, str);
            } else if (variavel.terminal == 2) { 
                sprintf(str, "%.2f", variavel.valorFloat);
                adicionarToken(*linha, str);
            } else if (variavel.terminal == 3) { 
                adicionarToken(*linha, variavel.valorString);
            } else 
                *flag = 1; 
			if(*aux!=NULL)
            	*aux = (*aux)->prox;
        }

        if (*aux && (strcmp((*aux)->token, ",") == 0 || strcmp((*aux)->token, "+") == 0)) {
            *aux = (*aux)->prox;
        }
    }

    if (*aux!=NULL) 
		*aux = (*aux)->prox;
}







/*
void consoleLog(Tokens **aux,Linha **linha, char *flag, Pilha **p){
	char str[50];
	var variavel;
	adicionarLinha(&*linha);
	*linha = buscaLinha(*linha);
	//[console.log]->[(]->["]->[conteudo]
	*aux = (*aux)->prox;
	if(aux!=NULL){
		*aux=(*aux)->prox;
		if(aux!=NULL){
			if((*aux)->token[0] != '"' && (*aux)->token[0] != 39){
				while (*aux != NULL && strcmp((*aux)->token,",")!=0 && strcmp((*aux)->token,")")!=0) {
					*aux = (*aux)->prox;
					adicionarToken(*linha, (*aux)->token);
	    		}
	    		if(*aux != NULL && strcmp((*aux)->token,",")==0){
	    			while(*aux != NULL && strcmp((*aux)->token,")")!=0){
	    				if(*aux != NULL && (*aux)->prox != NULL && strcmp((*aux)->prox->token,",")==0){
							variavel = buscaVariavel(&*p,&*aux);
							if(variavel.terminal==1){
								itoa(variavel.valorInt,str,10);
								adicionarToken(*linha,str);
							}else if (variavel.terminal==2){
								sprintf(str,"%.2f",variavel.valorFloat);
								adicionarToken(*linha,str);
							} else if(variavel.terminal==3){
								adicionarToken(*linha,variavel.valorString);
							} else
								*flag=1;
							*aux=(*aux)->prox->prox;
						}else if(*aux != NULL && (*aux)->prox != NULL && strcmp((*aux)->prox->token,",")!=0 && strcmp((*aux)->token,")")!=0){
							variavel = buscaVariavel(&*p,&*aux);
							variavel.valorFloat = resolveEquacao(&*aux,&*p,&*flag);
							sprintf(str,"%.2f",variavel.valorFloat);
							adicionarToken(*linha,str);
							printf("aux esta aqui : %s", (*aux)->token);
						}
						if(*aux != NULL && (*aux)->token[0] != '"' && (*aux)->token[0] != 39){
							while (*aux != NULL && strcmp((*aux)->token,",")!=0 && strcmp((*aux)->token,")")!=0) {
								*aux = (*aux)->prox;
								adicionarToken(*linha, (*aux)->token);
				    		}
						}
	    			}
				}
			}else{
				while(*aux != NULL && strcmp((*aux)->token,")")!=0){
					if(*aux != NULL && (*aux)->prox != NULL && strcmp((*aux)->prox->token,",")==0){
						variavel = buscaVariavel(&*p,&*aux);
						if(variavel.terminal==1){
							itoa(variavel.valorInt,str,10);
							adicionarToken(*linha,str);
						}else if (variavel.terminal==2){
							sprintf(str,"%.2f",variavel.valorFloat);
							adicionarToken(*linha,str);
						} else if(variavel.terminal==3){
							adicionarToken(*linha,variavel.valorString);
						} else
							*flag=1;
						*aux=(*aux)->prox->prox;
					}else if(*aux != NULL && (*aux)->prox != NULL && strcmp((*aux)->prox->token,",")!=0 && strcmp((*aux)->token,")")!=0){
						variavel = buscaVariavel(&*p,&*aux);
						variavel.valorFloat = resolveEquacao(&*aux,&*p,&*flag);
						sprintf(str,"%.2f",variavel.valorFloat);
						adicionarToken(*linha,str);
						printf("aux esta aqui : %s", (*aux)->token);
					}
					if(*aux != NULL && (*aux)->token[0] != '"' && (*aux)->token[0] != 39){
						while (*aux != NULL && strcmp((*aux)->token,",")!=0 && strcmp((*aux)->token,")")!=0) {
							*aux = (*aux)->prox;
							adicionarToken(*linha, (*aux)->token);
			    		}
					}
				}
			}
		}
	}
}*//*
	//versao antiga	
	while (*aux != NULL && (*aux)->token[0] != '"' && (*aux)->token[0] != 39) 
    	*aux = (*aux)->prox;
	if (*aux != NULL) {
	    *aux = (*aux)->prox; 
	    while (*aux != NULL && (*aux)->token[0] != '"' && (*aux)->token[0] != 39) {
	        adicionarToken(*linha, (*aux)->token);
	        *aux = (*aux)->prox;
	    }
	    if(*aux==NULL)
	    	*flag=1;
	}else
		*flag=1;
	//["]->[)] || ["]->[,]
	//printf("Estou quebrando aqui");
	//printf("valor de aux = %s",(*aux)->token);
	if(*aux!=NULL){
		*aux=(*aux)->prox;
		//printf("valor de aux = %s",(*aux)->token);
		if(*aux!=NULL){
			if(strcmp((*aux)->token,",")==0 || strcmp((*aux)->token,"+")==0){
				*aux=(*aux)->prox;
				//printf("valor de aux = %s",(*aux)->token);
				if(*aux!=NULL){
					variavel = buscaVariavel(&*p,&*aux);
					if(variavel.terminal==1){
						itoa(variavel.valorInt,str,10);
						adicionarToken(*linha,str);
					}else if (variavel.terminal==2){
						sprintf(str,"%.2f",variavel.valorFloat);
						adicionarToken(*linha,str);
						//*flag=1;
						//implementar calculos
					} else if(variavel.terminal==3){
						adicionarToken(*linha,variavel.valorString);
					} else
						*flag=1;
				}else 
					*flag=1;
			}
		}else
			*flag=1;
	}else 
		*flag=1;
	if((*aux)->prox!=NULL);
		*aux=(*aux)->prox;
}
*/
#endif
