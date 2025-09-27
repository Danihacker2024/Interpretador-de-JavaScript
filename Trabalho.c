#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>

#include "ListaDeListasToken.h"
#include "StrDin.h"
#include "PilhaVar.h" 
#include "Funcoes.h"
#include "Interface.h"

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
					juntaString(&str,inicio);
					adicionarLinha(&inicio);
					break;
				case ';':
				case ' ':
				case '\t':
					juntaString(&str,inicio);
					break;
				case ',':
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


Pilha *MemoriaRAM(Pilha *p){
	Pilha *p2;
	init(&p2);
	var aux = inicializaVar(0); 
	int y=6;   
	Menu2();
	gotoxy(28,y);
	printf("&\tidentificador\tvalor\tponteiro\tterminal");
	y++;
	while(!isEmpty(p)){
		pop(&p,&aux);
		gotoxy(28,y);
		printf("%u\t%s\t",&aux,aux.nome);
		if(aux.terminal==1)
			printf("%d\t",aux.valorInt);
		else if(aux.terminal==2)
			printf("%.2f\t",aux.valorFloat);
		else if(aux.terminal==3)
			printf("%s\t",aux.valorString);
		else
			printf("-\t");
		printf("[NULL]\t");
		printf("\t%d",aux.terminal);
		y++;
		push(&p2,aux);
	}
	getch();
	return p2;
}

void MostrarTela(Linha *consoleLog){
	consoleLog = buscaPrimeiraLinha(consoleLog);
	Tokens *aux;
	var var;
	int y=6, x=28;
	Menu2();
	while(consoleLog!=NULL){
		aux=consoleLog->pTokens;
		gotoxy(x,y);
		while(aux!=NULL){
			printf("%s ",aux->token);
			aux=aux->prox;	
		}
		consoleLog=consoleLog->prox;  
		y++;
	}
	//printf("\n");
	getch();
}



Linha *ExecutaSequencial(Linha *linha, Pilha **p){
	int tam=0,tamFuncao,tamOriginal;
	char flagBreak=0;
	char op;
	var variavel;
	var var2=inicializaVar(-1);
	Linha *Local = NULL;
	LinhaF *funcao = NULL;
	LinhaF *linhaF = NULL;
	var testeV = inicializaVar(-1);
	char achou=0;
	char nomeF[20];
	Linha *listaConsoleLog = NULL;
	Flag flag;
	iniciaFlag(&flag);
	Tokens *aux,*varInicial;
	int y=6;
	Linha *primeira = linha;
	while(linha!=NULL && !flag.erro){
		aux = linha->pTokens;
		while(aux!=NULL && !flag.erro && !flagBreak){
			if(flag.executa){
				if(strcmp(aux->token,"console.log")==0){
					consoleLog(&aux, &listaConsoleLog, &flag.erro,&*p);
				}
				if(strcmp(aux->token,"let")==0 || strcmp(aux->token,"var")==0){
					variavel = inicializaVar(0);
					aux=aux->prox;
					if(aux!=NULL){
						if(aux->prox==NULL){
							strcpy(variavel.nome,aux->token);
						}else{
							varInicial=aux;
							variavel = declaracao(&aux,&flag.erro,*p);
							if(aux->prox!=NULL && (variavel.terminal==1 || variavel.terminal==2)){
								variavel=inicializaVar(2);
								strcpy(variavel.nome,varInicial->token);
								variavel.valorFloat = resolveEquacao(&varInicial,&*p,&flag.erro);
							}
						} 
						if(!flag.erro)
							push(&*p,variavel);
					}else 
						flag.erro=1;
				}
				 if(strcmp(aux->token,"if")==0){
					flag.executa = flag.If = If(&*p,&aux,&flag.erro); 
				} if(strcmp(aux->token,"function")==0){
					function(&*p,&aux,&flag.erro,&linhaF);
					flag.executa=0;
					tamFuncao=tam;	
				}
				if(aux!=NULL){
					testeV = buscaVariavel(&*p,&aux);
					if(strcmp(testeV.nome,aux->token)==0){						
						//atribuicao de variavel ja declarada - seja calculos, incrementos, chamada de funcao, etc.
						aux=aux->prox;
						if(aux!=NULL){
							
							if(strcmp(aux->token,"=")==0){
								aux=aux->prox;
								if(aux!=NULL){
									if(aux->token[0]!='"' && aux->token[0]!=39){
										if(aux->prox!=NULL){
											testeV.valorFloat = resolveEquacao(&aux,&*p,&flag.erro);
											testeV.terminal=2;
											testeV.valorInt=0;
											testeV.valorString[0]='\0';
										} else{
											var2 = buscaVariavel(&*p,&aux);
											if(var2.terminal==1){
												testeV.valorInt=var2.valorInt;
												testeV.terminal=1;
												testeV.valorFloat=0.00;
												testeV.valorString[0]='\0';
											} else if(var2.terminal==2){
												testeV.valorFloat=testeV.valorFloat;
												testeV.terminal=2;
												testeV.valorInt=0;
												testeV.valorString[0]='\0';
											} else if(var2.terminal==3){
												strcpy(testeV.valorString,var2.valorString);
												testeV.terminal=3;
												testeV.valorInt=0;
												testeV.valorFloat=0.00f;
											}else if(Inteiro(aux->token)){
												testeV.valorInt=converteInt(aux->token);
												testeV.terminal=1;
												testeV.valorFloat=0.00;
												testeV.valorString[0]='\0';
											} else if(Float(aux->token)){
												testeV.valorFloat=converteFloat(aux->token);
												testeV.terminal=2;
												testeV.valorInt=0;
												testeV.valorString[0]='\0';
											} else
												flag.erro=1;
										}
									} else{
										aux=aux->prox;
										while(aux!=NULL && aux->token[0]!='"' && aux->token[0]!=39){
											strcat(testeV.valorString," ");
											strcat(testeV.valorString,aux->token);
											aux=aux->prox;
										}
										testeV.valorInt=0;
										testeV.valorFloat=0.00;
										testeV.terminal=3;
									}
									atualizaVariavel(&*p,testeV);
								}else
									flag.erro=1;
							}	
						}			
					}
				}
				//chamada de funcao
				if(aux!=NULL)
					funcao = buscaFuncao(linhaF, aux->token);
				if(funcao!=NULL){
					//verifica variaveis dentro da chamada antes de ir pra linha da funcao
					aux=aux->prox;
					if(aux!=NULL){
						if(strcmp(aux->token,"(")==0){
							if(aux->prox!=NULL && strcmp(aux->prox->token,")")!=0)
								chamaFuncao(funcao,&aux,&flag.erro,&*p);
							Local=linha;
							while(linha!=NULL && !flag.funcao){
								linha=linha->ant;
								aux=linha->pTokens;
								if(aux!=NULL){
									aux=aux->prox;
									if(aux!=NULL){
										if(strcmp(aux->token,linhaF->nomeFunc)==0){
											flag.funcao=1;
											tamOriginal=tam;
											tam=tamFuncao;
											//while(aux->prox!=NULL)
												//aux=aux->prox;
											//linha=linha->prox;
											//aux=linha->pTokens;
											flagBreak=1;		
										}
									}
								}
							}
						}
					}
				}
			}
			if(aux!=NULL){
				if(strcmp(aux->token,"else")==0){
					if(!flag.If){
						aux=aux->prox;
						if(aux!=NULL){
							if(strcmp(aux->token,"if")==0){
								flag.executa = flag.If = If(&*p,&aux,&flag.erro);
							}else 
								flag.executa=1;
						}
					}else{
						flag.executa=0;
					}
				}
			}
			if(aux!=NULL){
				if(strcmp(aux->token,"}")==0){
					if(!flag.executa)
						flag.executa=1;
					if(flag.funcao){
					    flag.funcao=0;
					    tam=tamOriginal;
					    while(linha != NULL && linha != Local) { 
					        linha = linha->prox;
					    }
					    if (linha != NULL) {
					        linha = linha->prox;
					    }
					}
				}
			}
			if(aux!=NULL)
				aux=aux->prox;
		}
		if(linha!=NULL)
			linha=linha->prox;
		if(flagBreak)
			flagBreak=0;
		tam++;
		op = getch();
		Menu3();
		exibirTokens(primeira,tam);
		if(op == 0 || op == 224){
			op = getch();
			if(op==67){
				if (*p!=NULL)
					*p = MemoriaRAM(*p);
				else{
					gotoxy(28,6);
					printf("Nao ha variaveis na Memoria");
					getch();	
				}
			}else if(op==68){
				if(listaConsoleLog!=NULL)
					MostrarTela(listaConsoleLog);
				else{
					gotoxy(28,6);
					printf("Nao ha console.logs para mostrar");
					getch();	
				}		
			}	
		} 
	}
	if(flag.erro){
		Menu2();
		gotoxy(28,6);
		printf("Erro na execucao do programa");
		getch();
	}
	gotoxy(28,6);
	printf("Fim da execucao");
	return listaConsoleLog;		
}


int main(void){
	Linha *codigo;
	Linha *consoleLog=NULL;
    exibirParticipantes();
    int opcao;
    Pilha *p;
	init(&p);
	var var = inicializaVar(-1);
    //vai precisar mudar a logica
    do {   
        Menu1();    
        gotoxy(15,22);
		opcao = getch();
		if (opcao == 0 || opcao == 224) {
            // segunda leitura -> tecla especial
            opcao = getch();
            //n�o � possivel fazer as outras coisas se ele n�o ler o arquivo primeiro
	        switch(opcao){
	        	case 65://F7 Abrir arquivo fonte   
	        		codigo = leArq();
				    if (codigo != NULL) {  
						do{ 
	        				Menu2();
				            exibirTokens(codigo,0);
							gotoxy(21,22);
							opcao = getch();
							if (opcao == 0 || opcao == 224) {
	            			// segunda leitura -> tecla especial
	            				opcao = getch();
		        				switch(opcao){
									case 66://F8 Executar programa 
										while(!isEmpty(p))
											pop(&p,&var);
						                consoleLog = ExecutaSequencial(codigo, &p);
						                break;
						            case 67://F9 Mostrar conteudo da Memoria RAM 
										if (p!=NULL)
											p = MemoriaRAM(p);
										else{
											gotoxy(28,6);
											printf("Nao ha variaveis na Memoria");
											getch();	
										}
						                break;
						            case 68://F10 Mostrar tela (resultados do console.log)
						            	if(consoleLog!=NULL)
						            		MostrarTela(consoleLog);
						            	break;
						        	default:
						                gotoxy(50, 10);
						                printf("Opcao invalida...");
						                getch();
						                break;
		        				}
							}
				    	}while(opcao!=27);
					} else {
				        gotoxy(50, 19);
				        printf("Nenhum token lido.");
				    }
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

