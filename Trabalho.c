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

Linha *ExecutaSequencial(Linha *linha, struct pilha **p){
	var variavel;
	Linha *Local;
	LinhaF *linhaF = NULL;
	var testeV = inicializaVar(-1);
	char achou=0;
	char nomeF[20];
	Linha *listaConsoleLog = NULL;
	Flag flag;
	iniciaFlag(&flag);
	Tokens *aux;
	int y=6;
	while(linha!=NULL && !flag.erro){
		aux = linha->pTokens;
		while(aux!=NULL && !flag.erro){
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
						}else 
							variavel = declaracao(&aux,&flag.erro,*p); // na declaração deve ter opcao para chamada de funcao
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
				} 
				testeV = buscaVariavel(&*p,&aux);
				if(strcmp(testeV.nome,aux->token)==0){
					//atribuicao de variavel ja declarada - seja calculos, incrementos, chamada de funcao, etc.
				}
				//chamada de funcao
				buscaFuncao(&linhaF,aux->token);
				if(linhaF!=NULL){
					//verifica variaveis dentro da chamada antes de ir pra linha da funcao
					aux=aux->prox;
					if(aux!=NULL){
						if(strcmp(aux->token,"(")==0){
							chamaFuncao(linhaF,&aux,&flag.erro,&*p);
							Local=linha;
							while(linha!=NULL && !flag.funcao){
								linha=linha->ant;
								aux=linha->pTokens;
								aux=aux->prox;
								if(aux!=NULL){
									if(strcmp(aux->token,linhaF->nomeFunc)==0){
										flag.funcao=1;
										linha=linha->prox;		
									}
								}
							}
						}
					}
				}
			}

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
			if(strcmp(aux->token,"}")==0){
				if(!flag.executa)
					flag.executa=1;
				if(flag.funcao){
				    flag.funcao=0;
				    while(linha != NULL && linha != Local) { 
				        linha = linha->prox;
				    }
				    if (linha != NULL) {
				        linha = linha->prox;
				    }
				}
			}
			if(aux!=NULL)
				aux=aux->prox;
		}
		if(linha!=NULL)
			linha=linha->prox;
	}
	if(flag.erro){
		Menu2();
		gotoxy(28,6);
		printf("Erro na execucao do programa");
		getch();
	}
	return listaConsoleLog;		
}

Pilha *MemoriaRAM(Pilha *p){
	Pilha *p2;
	init(&p2);
	var aux = inicializaVar(0); 
	int y=6;   
	Menu2();
	gotoxy(28,y);
	printf("&\tidentificador\tvalor\tponteiro");
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
		printf("[NULL]");
		y++;
		push(&p2,aux);
	}
	getch();
	return p2;
}

void MostrarTela(Linha *consoleLog,Pilha **p){
	Tokens *aux;
	var var;
	int y=6, x=28;
	Menu2();
	while(consoleLog!=NULL){
		aux=consoleLog->pTokens;
		while(aux!=NULL){
			if(strcmp(aux->token,",")==0 || strcmp(aux->token,"+")==0){
				aux=aux->prox;
				var = buscaVariavel(&*p,&aux);
				if(var.terminal==1){
					gotoxy(x,y);
					printf("%d",var.valorInt);
				}else if(var.terminal==2){
					gotoxy(x,y);
					printf("%f",var.valorFloat);
				} else
					gotoxy(x,y);
					printf("%s",var.valorString);
			}else{
				gotoxy(x,y);
				printf("%s",aux->token);
				aux=aux->prox;	
			}
			x+=strlen(aux->token);	
		}
		consoleLog=consoleLog->prox;
		y++;
	}
	printf("\n");
	getch();
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
            //nï¿½o ï¿½ possivel fazer as outras coisas se ele nï¿½o ler o arquivo primeiro
	        switch(opcao){
	        	case 65://F7 Abrir arquivo fonte   
	        		codigo = leArq();
				    if (codigo != NULL) {  
						do{ 
	        				Menu2();
				            exibirTokens(codigo);
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
						                break;
						            case 68://F10 Mostrar tela (resultados do console.log)
						            	if(consoleLog!=NULL)
						            		MostrarTela(consoleLog,&p);
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

