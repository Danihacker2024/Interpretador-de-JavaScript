#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Trabalho.h"
#include "StrDin.h"
#include "Pilha.h" 
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

Linha *ExecutaSequencial(Linha *linha, struct pilha **p){
	Linha *listaConsoleLog;
	Flag flag;
	Tokens *aux;
	int y=6;
	while(linha!=NULL && !flag.erro){
		aux = linha->pTokens;
		while(aux!=NULL && !flag.erro && flag.If){
			//chamadas da fun��o aqui
			
			if(strcmp(aux->token,"console.log")==0){
				consoleLog(&aux, &listaConsoleLog, &flag.erro,&*p);
			}
			if(strcmp(aux->token,"let")==0 || strcmp(aux->token,"var")==0){
				struct variavel variavel = declaracao(&aux,&flag.erro);
				if(!flag.erro)
					push(&*p,variavel);
				//system("cls");
				//FormPrincipal();   
				//Menu();
				/*
				gotoxy(28,y);
				printf("%s = ",variavel.nome);
				printf("%s",variavel.valorString);
				y++;*/	
			} else if(strcmp(aux->token,"if")==0){
				flag.If = If(&*p,&aux,&flag);
			}
			aux=aux->prox;	
		}
		linha=linha->prox;
		if(!flag.If && strcmp(aux->token,"}")==0){
			flag.If=1;
			aux=aux->prox;
			if(aux!=NULL){
				if(strcmp(aux->token,"else")==0){
					aux=aux->prox;
					if(aux!=NULL){
						if(strcmp(aux->token,"if")==0){
							flag.If = If(&p,&aux,&flag);
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
								flag.If = If(&p,&aux,&flag);
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
	return listaConsoleLog;		
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

void MostrarTela(Linha *consoleLog,Pilha **p){
	Tokens *aux;
	var x;
	while(consoleLog!=NULL){
		aux=consoleLog->pTokens;
		while(aux!=NULL){
			if(strcmp(aux->token,",")==0 || strcmp(aux->token,"+")==0){
				x = buscaVariavel(&*p,aux);
				if(x.valorInt!=NULL){
					printf("%d",x.valorInt);
				}else if(x.valorFloat!=NULL){
					printf("%f",x.valorFloat);
				} else
					printf("%s",x.valorString);
			}else{
				printf("%s ",aux->token);
				aux=aux->prox;	
			}	
		}
		consoleLog->prox;
	}
	printf("\n");
}




int main(void){
	Linha *codigo;
	Linha *consoleLog;
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
            //n�o � possivel fazer as outras coisas se ele n�o ler o arquivo primeiro
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
						                consoleLog = ExecutaSequencial(codigo, &p);
						                break;
						            case 67://F9 Mostrar conteudo da Memoria RAM 
										if (p!=NULL)
											MemoriaRAM(p);
						                break;
						            case 68://F10 Mostrar tela (resultados do console.log)
						            		MostrarTela(consoleLog,&p);
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

