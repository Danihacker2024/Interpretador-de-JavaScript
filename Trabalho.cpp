#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Trabalho.h"
#include "StrDin.h"
#include "Pilha.h" 
#include "Funcoes.h"
#include "Interface.h"

int If(Pilha **p, Tokens **aux, int *flag) {
    var var1, var2;
    int num;
    float numf;
    int condicao1, condicao2;
	char logico[5];
    *aux = (*aux)->prox;
    // NULL representa o fim da linha
    if (*aux != NULL) {
        if (strcmp((*aux)->token, "(") == 0) {
            *aux = (*aux)->prox;
            if (*aux != NULL) {
                if (strcmp((*aux)->token, "!") == 0) {
                    *aux = (*aux)->prox;
                    if (*aux != NULL) {
                        var1 = buscaVariavel(&p, &aux);
                        if (var1.valorInt != -1) {
                            *aux = (*aux)->prox;
                            if (*aux != NULL) {
                                if (strcmp((*aux)->token, "==") == 0) {
                                    *aux = (*aux)->prox;
                                    if (*aux != NULL) {
                                        var2 = buscaVariavel(&p, &aux);
                                        // onde parei
                                        if (var2.valorInt != -1) {
                                            if (var1.valorInt == !var2.valorInt) {
                                                condicao1 = 1;
                                            } else if (var1.valorFloat == !var2.valorFloat) {
                                                condicao1 = 1;
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Inteiro((*aux)->token)) {
                                            num = converteInt((*aux)->token);
                                            if (var1.valorInt == !num) {
                                                condicao1 = 1;
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Float((*aux)->token)) {
                                            numf = converteFloat((*aux)->token);
                                            if (var1.valorInt == !numf || var1.valorFloat == !numf) {
                                                condicao1 = 1;
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else {
                                            flag = 1;
                                        }
                                    } else {
                                        flag = 1;
                                    }
                                } else if (strcmp((*aux)->token, "!=") == 0) {
                                    *aux = (*aux)->prox;
                                    if (*aux != NULL) {
                                        var2 = buscaVariavel(&p, &aux);
                                        if (var2.valorInt != -1) {
                                            if (var1.valorInt != !var2.valorInt) {
                                                condicao1 = 1;
                                            } else if (var1.valorFloat != !var2.valorFloat) {
                                                condicao1 = 1;
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Inteiro((*aux)->token)) {
                                            num = converteInt((*aux)->token);
                                            if (var1.valorInt != !num) {
                                                condicao1 = 1;
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Float((*aux)->token)) {
                                            numf = converteFloat((*aux)->token);
                                            if (var1.valorInt != !numf || var1.valorFloat != !numf) {
                                                condicao1 = 1;
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else {
                                            flag = 1;
                                        }
                                    } else {
                                        flag = 1;
                                    }
                                } else if ((*aux)->token[0] == '<') {
                                    *aux = (*aux)->prox;
                                    if (*aux != NULL) {
                                        var2 = buscaVariavel(&p, &aux);
                                        if (var2.valorInt != -1) {
                                            if (var1.valorInt < !var2.valorInt) {
                                                condicao1 = 1;
                                            } else if (var1.valorFloat < !var2.valorFloat) {
                                                condicao1 = 1;
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Inteiro((*aux)->token)) {
                                            num = converteInt((*aux)->token);
                                            if (var1.valorInt < !num) {
                                                condicao1 = 1;
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Float((*aux)->token)) {
                                            numf = converteFloat((*aux)->token);
                                            if (var1.valorInt < !numf || var1.valorFloat < !numf) {
                                                condicao1 = 1;
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else {
                                            flag = 1;
                                        }
                                    } else {
                                        flag = 1;
                                    }
                                } else if ((*aux)->token[0] == '>') {
                                    *aux = (*aux)->prox;
                                    if (*aux != NULL) {
                                        var2 = buscaVariavel(&p, &aux);
                                        if (var2.valorInt != -1) {
                                            if (var1.valorInt > !var2.valorInt) {
                                                condicao1 = 1;
                                            } else if (var1.valorFloat > !var2.valorFloat) {
                                                condicao1 = 1;
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Inteiro((*aux)->token)) {
                                            num = converteInt((*aux)->token);
                                            if (var1.valorInt > !num) {
                                                condicao1 = 1;
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Float((*aux)->token)) {
                                            numf = converteFloat((*aux)->token);
                                            if (var1.valorInt > !numf || var1.valorFloat > !numf) {
                                                condicao1 = 1;
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else {
                                            flag = 1;
                                        }
                                    } else {
                                        flag = 1;
                                    }
                                } else if (strcmp((*aux)->token, ">=") == 0) {
                                    *aux = (*aux)->prox;
                                    if (*aux != NULL) {
                                        var2 = buscaVariavel(&p, &aux);
                                        if (var2.valorInt != -1) {
                                            if (var1.valorInt >= !var2.valorInt) {
                                                condicao1 = 1;
                                            } else if (var1.valorFloat >= !var2.valorFloat) {
                                                condicao1 = 1;
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Inteiro((*aux)->token)) {
                                            num = converteInt((*aux)->token);
                                            if (var1.valorInt >= !num) {
                                                condicao1 = 1;
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Float((*aux)->token)) {
                                            numf = converteFloat((*aux)->token);
                                            if (var1.valorInt >= !numf || var1.valorFloat >= !numf) {
                                                condicao1 = 1;
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else {
                                            flag = 1;
                                        }
                                    } else {
                                        flag = 1;
                                    }
                                } else if (strcmp((*aux)->token, "<=") == 0) {
                                    *aux = (*aux)->prox;
                                    if (*aux != NULL) {
                                        var2 = buscaVariavel(&p, &aux);
                                        if (var2.valorInt != -1) {
                                            if (var1.valorInt <= !var2.valorInt) {
                                                condicao1 = 1;
                                            } else if (var1.valorFloat <= !var2.valorFloat) {
                                                condicao1 = 1;
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Inteiro((*aux)->token)) {
                                            num = converteInt((*aux)->token);
                                            if (var1.valorInt <= !num) {
                                                condicao1 = 1;
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else if (Float((*aux)->token)) {
                                            numf = converteFloat((*aux)->token);
                                            if (var1.valorInt <= !numf || var1.valorFloat <= !numf) {
                                                condicao1 = 1;
                                            } else {
                                                condicao1 = 0;
                                            }
                                        } else {
                                            flag = 1;
                                        }
                                    } else {
                                        flag = 1;
                                    }
                                }
                            }
                        } else {
                            flag = 1;
                        }
                    } else {
                        flag = 1;
                    }
                } else {
                    var1 = buscaVariavel(&p, &aux);
                    if (var1.valorInt != -1) {
                        *aux = (*aux)->prox;
                        if (*aux != NULL) {
                            if (strcmp((*aux)->token, "==") == 0) {
                                *aux = (*aux)->prox;
                                if (*aux != NULL) {
                                    var2 = buscaVariavel(&p, &aux);
                                    // onde parei
                                    if (var2.valorInt != -1) {
                                        if (var1.valorInt == var2.valorInt) {
                                            condicao1 = 1;
                                        } else if (var1.valorFloat == var2.valorFloat) {
                                            condicao1 = 1;
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Inteiro((*aux)->token)) {
                                        num = converteInt((*aux)->token);
                                        if (var1.valorInt == num) {
                                            condicao1 = 1;
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Float((*aux)->token)) {
                                        numf = converteFloat((*aux)->token);
                                        if (var1.valorInt == numf || var1.valorFloat == numf) {
                                            condicao1 = 1;
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else {
                                        flag = 1;
                                    }
                                } else {
                                    flag = 1;
                                }
                            } else if (strcmp((*aux)->token, "!=") == 0) {
                                *aux = (*aux)->prox;
                                if (*aux != NULL) {
                                    var2 = buscaVariavel(&p, &aux);
                                    if (var2.valorInt != -1) {
                                        if (var1.valorInt != var2.valorInt) {
                                            condicao1 = 1;
                                        } else if (var1.valorFloat != var2.valorFloat) {
                                            condicao1 = 1;
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Inteiro((*aux)->token)) {
                                        num = converteInt((*aux)->token);
                                        if (var1.valorInt != num) {
                                            condicao1 = 1;
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Float((*aux)->token)) {
                                        numf = converteFloat((*aux)->token);
                                        if (var1.valorInt != numf || var1.valorFloat != numf) {
                                            condicao1 = 1;
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else {
                                        flag = 1;
                                    }
                                } else {
                                    flag = 1;
                                }
                            } else if ((*aux)->token[0] == '<') {
                                *aux = (*aux)->prox;
                                if (*aux != NULL) {
                                    var2 = buscaVariavel(&p, &aux);
                                    if (var2.valorInt != -1) {
                                        if (var1.valorInt < var2.valorInt) {
                                            condicao1 = 1;
                                        } else if (var1.valorFloat < var2.valorFloat) {
                                            condicao1 = 1;
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Inteiro((*aux)->token)) {
                                        num = converteInt((*aux)->token);
                                        if (var1.valorInt < num) {
                                            condicao1 = 1;
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Float((*aux)->token)) {
                                        numf = converteFloat((*aux)->token);
                                        if (var1.valorInt < numf || var1.valorFloat < numf) {
                                            condicao1 = 1;
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else {
                                        flag = 1;
                                    }
                                } else {
                                    flag = 1;
                                }
                            } else if ((*aux)->token[0] == '>') {
                                *aux = (*aux)->prox;
                                if (*aux != NULL) {
                                    var2 = buscaVariavel(&p, &aux);
                                    if (var2.valorInt != -1) {
                                        if (var1.valorInt > var2.valorInt) {
                                            condicao1 = 1;
                                        } else if (var1.valorFloat > var2.valorFloat) {
                                            condicao1 = 1;
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Inteiro((*aux)->token)) {
                                        num = converteInt((*aux)->token);
                                        if (var1.valorInt > num) {
                                            condicao1 = 1;
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Float((*aux)->token)) {
                                        numf = converteFloat((*aux)->token);
                                        if (var1.valorInt > numf || var1.valorFloat > numf) {
                                            condicao1 = 1;
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else {
                                        flag = 1;
                                    }
                                } else {
                                    flag = 1;
                                }
                            } else if (strcmp((*aux)->token, ">=") == 0) {
                                *aux = (*aux)->prox;
                                if (*aux != NULL) {
                                    var2 = buscaVariavel(&p, &aux);
                                    if (var2.valorInt != -1) {
                                        if (var1.valorInt >= var2.valorInt) {
                                            condicao1 = 1;
                                        } else if (var1.valorFloat >= var2.valorFloat) {
                                            condicao1 = 1;
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Inteiro((*aux)->token)) {
                                        num = converteInt((*aux)->token);
                                        if (var1.valorInt >= num) {
                                            condicao1 = 1;
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else if (Float((*aux)->token)) {
                                        numf = converteFloat((*aux)->token);
                                        if (var1.valorInt >= numf || var1.valorFloat >= numf) {
                                            condicao1 = 1;
                                        } else {
                                            condicao1 = 0;
                                        }
                                    } else {
                                        flag = 1;
                                    }
                                } else {
                                    flag = 1;
                                }
                            } else if (strcmp((*aux)->token, "<=") == 0) {
                                *aux = (*aux)->prox;
                                if (*aux != NULL) {
                                    var2 = buscaVariavel(&p, &aux);
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
                                        flag = 1;
                                    }
                                } else {
                                    flag = 1;
                                }
                            }
                            //aqui começa a condição 2
							*aux = (*aux)->prox;
							if (*aux != NULL) {
							    if (strcmp((*aux)->token, "&&") == 0 || strcmp((*aux)->token, "||") == 0) {
							        strcpy(logico, (*aux)->token);  // guarda o operador lógico
							        *aux = (*aux)->prox;
							        if (*aux != NULL) {
							            // ============================
							            // TRATANDO A CONDICAO 2
							            // ============================
							
							            if (strcmp((*aux)->token, "!") == 0) {
							                *aux = (*aux)->prox;
							                if (*aux != NULL) {
							                    var1 = buscaVariavel(&p, &aux);
							                    if (var1.valorInt != -1) {
							                        *aux = (*aux)->prox;
							                        if (*aux != NULL) {
							                            if (strcmp((*aux)->token, "==") == 0) {
							                                *aux = (*aux)->prox;
							                                if (*aux != NULL) {
							                                    var2 = buscaVariavel(&p, &aux);
							                                    if (var2.valorInt != -1) {
							                                        if (var1.valorInt == !var2.valorInt) {
							                                            condicao2 = 1;
							                                        } else if (var1.valorFloat == !var2.valorFloat) {
							                                            condicao2 = 1;
							                                        } else {
							                                            condicao2 = 0;
							                                        }
							                                    } else if (Inteiro((*aux)->token)) {
							                                        num = converteInt((*aux)->token);
							                                        condicao2 = (var1.valorInt == !num);
							                                    } else if (Float((*aux)->token)) {
							                                        numf = converteFloat((*aux)->token);
							                                        condicao2 = (var1.valorInt == !numf || var1.valorFloat == !numf);
							                                    } else {
							                                        flag = 1;
							                                    }
							                                } else flag = 1;
							                            }
							                            else if (strcmp((*aux)->token, "!=") == 0) {
							                                *aux = (*aux)->prox;
							                                if (*aux != NULL) {
							                                    var2 = buscaVariavel(&p, &aux);
							                                    if (var2.valorInt != -1) {
							                                        if (var1.valorInt != !var2.valorInt) {
							                                            condicao2 = 1;
							                                        } else if (var1.valorFloat != !var2.valorFloat) {
							                                            condicao2 = 1;
							                                        } else {
							                                            condicao2 = 0;
							                                        }
							                                    } else if (Inteiro((*aux)->token)) {
							                                        num = converteInt((*aux)->token);
							                                        condicao2 = (var1.valorInt != !num);
							                                    } else if (Float((*aux)->token)) {
							                                        numf = converteFloat((*aux)->token);
							                                        condicao2 = (var1.valorInt != !numf || var1.valorFloat != !numf);
							                                    } else {
							                                        flag = 1;
							                                    }
							                                } else flag = 1;
							                            }
							                            else if ((*aux)->token[0] == '<') {
							                                *aux = (*aux)->prox;
							                                if (*aux != NULL) {
							                                    var2 = buscaVariavel(&p, &aux);
							                                    if (var2.valorInt != -1) {
							                                        condicao2 = (var1.valorInt < !var2.valorInt || var1.valorFloat < !var2.valorFloat);
							                                    } else if (Inteiro((*aux)->token)) {
							                                        num = converteInt((*aux)->token);
							                                        condicao2 = (var1.valorInt < !num);
							                                    } else if (Float((*aux)->token)) {
							                                        numf = converteFloat((*aux)->token);
							                                        condicao2 = (var1.valorInt < !numf || var1.valorFloat < !numf);
							                                    } else {
							                                        flag = 1;
							                                    }
							                                } else flag = 1;
							                            }
							                            else if ((*aux)->token[0] == '>') {
							                                *aux = (*aux)->prox;
							                                if (*aux != NULL) {
							                                    var2 = buscaVariavel(&p, &aux);
							                                    if (var2.valorInt != -1) {
							                                        condicao2 = (var1.valorInt > !var2.valorInt || var1.valorFloat > !var2.valorFloat);
							                                    } else if (Inteiro((*aux)->token)) {
							                                        num = converteInt((*aux)->token);
							                                        condicao2 = (var1.valorInt > !num);
							                                    } else if (Float((*aux)->token)) {
							                                        numf = converteFloat((*aux)->token);
							                                        condicao2 = (var1.valorInt > !numf || var1.valorFloat > !numf);
							                                    } else {
							                                        flag = 1;
							                                    }
							                                } else flag = 1;
							                            }
							                            else if (strcmp((*aux)->token, ">=") == 0) {
							                                *aux = (*aux)->prox;
							                                if (*aux != NULL) {
							                                    var2 = buscaVariavel(&p, &aux);
							                                    if (var2.valorInt != -1) {
							                                        condicao2 = (var1.valorInt >= !var2.valorInt || var1.valorFloat >= !var2.valorFloat);
							                                    } else if (Inteiro((*aux)->token)) {
							                                        num = converteInt((*aux)->token);
							                                        condicao2 = (var1.valorInt >= !num);
							                                    } else if (Float((*aux)->token)) {
							                                        numf = converteFloat((*aux)->token);
							                                        condicao2 = (var1.valorInt >= !numf || var1.valorFloat >= !numf);
							                                    } else {
							                                        flag = 1;
							                                    }
							                                } else flag = 1;
							                            }
							                            else if (strcmp((*aux)->token, "<=") == 0) {
							                                *aux = (*aux)->prox;
							                                if (*aux != NULL) {
							                                    var2 = buscaVariavel(&p, &aux);
							                                    if (var2.valorInt != -1) {
							                                        condicao2 = (var1.valorInt <= !var2.valorInt || var1.valorFloat <= !var2.valorFloat);
							                                    } else if (Inteiro((*aux)->token)) {
							                                        num = converteInt((*aux)->token);
							                                        condicao2 = (var1.valorInt <= !num);
							                                    } else if (Float((*aux)->token)) {
							                                        numf = converteFloat((*aux)->token);
							                                        condicao2 = (var1.valorInt <= !numf || var1.valorFloat <= !numf);
							                                    } else {
							                                        flag = 1;
							                                    }
							                                } else flag = 1;
							                            }
							                        }
							                    } else flag = 1;
							                } else flag = 1;
							            }
							            *aux=(*aux)->prox;
										if(strcmp(logico,"&&")==0)
											return (condicao1 && condicao2);
										else
											return (condicao1 || condicao2);
							        } else flag = 1;
							    }
							    if((*aux)->token[0]==')')
							    	return condicao1;
							    else
							    	flag=1;
							}else 
								flag = 1;

                        }
                    } else {
                        flag = 1;
                    }
                }
            } else {
                flag = 1;
            }
        } else {
            flag = 1;
        }
    } else {
        flag = 1;
    }
    
}


var declaracao(Tokens **aux,int *flag){
	var variavel;
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
								variavel.valorFloat=NULL;
								strcpy(variavel.valorString,NULL);
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
								variavel.valorInt=NULL;
								strcpy(variavel.valorString,NULL);
							}
						}else
							flag=1;
					}else{
						if(Inteiro((*aux)->token)){
							variavel.valorInt=converteInt((*aux)->token);
							variavel.valorFloat=NULL;
							strcpy(variavel.valorString,NULL);
						}
						else if(Float((*aux)->token)){
							variavel.valorFloat=converteFloat((*aux)->token);
							variavel.valorInt=NULL;
							strcpy(variavel.valorString,NULL);
						}
						else if((*aux)->token[0]==39 || (*aux)->token[0]=='"'){
							*aux=(*aux)->prox;
							while((*aux)->token[0]!='"' && flag && (*aux)->token[0]!=39){
								if(*aux!=NULL){
									strcat(variavel.valorString,(*aux)->token);
									*aux=(*aux)->prox;
									if((*aux)->token[0]!=39 || (*aux)->token[0]!='"' || *aux!=NULL)
										strcat(variavel.valorString," ");
								} else
									flag=0;
							}
							variavel.valorInt=NULL;
							variavel.valorFloat=NULL;
						}	
					}
				}else
					flag=1;
			}else
				flag=1;
		}
	}else 
		flag=1;
	return variavel;
}

Linha *leArq(){
	Linha *inicio=NULL;
	StrDin *str=NULL;
	char arquivo[50];
	char caracter;
	gotoxy(28,6);
	printf("Digite o nome do arquivo ou o caminho absoluto:");
	gotoxy(28,8);
	gets(arquivo);
	FILE *arq = fopen(arquivo,"r");
	if (arq != NULL) {
		fscanf(arq,"%c",&caracter);
		adicionarLinha(&inicio);
		while(!feof(arq)){
			switch(caracter){
				case '*':
					juntaString(&str,inicio);
					insereCaracter(&str,caracter,inicio);
					fscanf(arq,"%c",&caracter);
					//se for * ï¿½ elevado
					if(caracter=='*'){
						insereCaracter(&str,caracter,inicio);
						juntaString(&str,inicio);
					//senï¿½o ï¿½ um * normal
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
					//se for igual ï¿½ comparaï¿½ï¿½o
					if(caracter=='='){
						insereCaracter(&str,caracter,inicio);
						juntaString(&str,inicio);
					//senï¿½o ï¿½ somente um caracter
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
	}
	else if(arq==NULL){
		gotoxy(28, 10);
        printf("Erro: nao foi possivel abrir o arquivo!");
	}
	
	return inicio;
}

void ExecutaSequencial(Linha *linha, struct pilha **p){
	int flag=0,flagif=1;
	Tokens *aux;
	int y=6;
	while(linha!=NULL && !flag){
		aux = linha->pTokens;
		while(aux!=NULL && !flag && flagif){
			//chamadas da funï¿½ï¿½o aqui
			/*
			if(strcmp(aux->token,"console.log")==0){
				system("cls");
				FormPrincipal();   
				Menu();
				consoleLog(&aux,y);
				y++;
			}*/
			if(strcmp(aux->token,"let")==0 || strcmp(aux->token,"var")==0){
				struct variavel variavel = declaracao(&aux,&flag);
				if(!flag)
					push(&p,variavel);
				//system("cls");
				//FormPrincipal();   
				//Menu();
				/*
				gotoxy(28,y);
				printf("%s = ",variavel.nome);
				printf("%s",variavel.valorString);
				y++;*/	
			} else if(strcmp(aux->token,"if")==0){
				flagif = If(&p,&aux,&flag);
			}
			aux=aux->prox;	
		}
		linha=linha->prox;
		if(!flagif && strcmp(aux->token,"}")==0){
			flagif=1;
			aux=aux->prox;
			if(aux!=NULL){
				if(strcmp(aux->token,"else")==0){
					aux=aux->prox;
					if(aux!=NULL){
						if(strcmp(aux->token,"if")==0){
							flagif = If(&p,&aux,&flag);
						}
					}
				}
			}else{
				aux=linha->pTokens;
				if(aux!=NULL){
					if(strcmp(aux->token,"else")==0){
						aux=aux->prox;
						if(aux!=NULL){
							if(strcmp(aux->token,"if")==0){
								flagif = If(&p,&aux,&flag);
							}
						}
					}
				}
				linha=linha->prox;
			}
		}
	}
	if(flag){
		gotoxy(28,6);
		printf("Erro na execucao do codigo");
	}		
}

void MemoriaRAM(Pilha *p){
	var aux;
	int y=6;
	system("cls");
	FormPrincipal();   
	Menu();
	gotoxy(28,y);
	printf("&\tidentificador\tvalor\tponteiro");
	y++;
	while(!isEmpty(p)){
		pop(&p,&aux);
		gotoxy(28,y);
		printf("%u\t%s\t",&aux,aux.nome);
		if(aux.valorInt!=NULL)
			printf("%d\t",aux.valorInt);
		else if(aux.valorFloat!=NULL)
			printf("%.2f\t",aux.valorFloat);
		else 
			printf("%s\t",aux.valorString);
		y++;	
	}
}

int main(void){
	Linha *codigo;
    exibirParticipantes();
    char opcao;
    Pilha *p;
	init(&p);
    //vai precisar mudar a logica
    do {
        system("cls");
        FormPrincipal();   
        Menu();    
        gotoxy(21,21);
		opcao = getch();
		if (opcao == 0 || opcao == 224) {
            // segunda leitura -> tecla especial
            opcao = getch();
            //nï¿½o ï¿½ possivel fazer as outras coisas se ele nï¿½o ler o arquivo primeiro
	        switch(opcao){
	        	case 65://F7 Abrir arquivo fonte
	        		system("cls");
	        		FormPrincipal();   
	        		Menu();
	        		do{
		        		codigo = leArq();
				        if (codigo != NULL) {
				        	system("cls");
	        				FormPrincipal();   
	        				Menu();
				            exibirTokens(codigo);
							gotoxy(21,21);
							opcao = getch();
							if (opcao == 0 || opcao == 224) {
	            			// segunda leitura -> tecla especial
	            				opcao = getch();
		        				switch(opcao){
		        					case 65:
										break;
									case 66://F8 Executar programa 
						                ExecutaSequencial(codigo, &p);
						                break;
						            case 67://F9 Mostrar conteudo da Memoria RAM 
										if (p!=NULL)
											MemoriaRAM(p);
						                break;
						            case 68://F10 Mostrar tela (resultados do console.log)
						            	break;
						        	default:
						                gotoxy(50, 10);
						                printf("Opcao invalida...");
						                getch();
						                break;
		        				}
							}
				        } else {
				            gotoxy(50, 19);
				            printf("Nenhum token lido.");
				        }
				    }while(opcao!=65 && opcao!=27);
	        		break;
	            default:
	                gotoxy(50, 10);
	                printf("Escolha um arquivo primeiro");
	                getch();
	                break;
            }
        }
    } while(opcao != 27);

    return 0;
}

