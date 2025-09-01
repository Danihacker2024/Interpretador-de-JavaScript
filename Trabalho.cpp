#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Trabalho.h"
#include "StrDin.h"
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
					//se for * é elevado
					if(caracter=='*'){
						insereCaracter(&str,caracter,inicio);
						juntaString(&str,inicio);
					//senão é um * normal
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
					//se for igual é comparação
					if(caracter=='='){
						insereCaracter(&str,caracter,inicio);
						juntaString(&str,inicio);
					//senão é somente um caracter
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

void ExecutaSequencial(Linha *linha){
	Tokens *aux;
	while(linha!=NULL){
		aux = linha->pTokens;
		while(aux!=NULL){
			//chamadas da função aqui
			if(strcmp(aux->token,"console.log")==0){
				system("cls");
				FormPrincipal();   
				Menu();
				consoleLog(&aux);
			}
			else if(strcmp(aux->token,"let")==0 || strcmp(aux->token,"var")==0){
				var variavel = declaracao(&aux);
			}
			aux=aux->prox;	
		}
		linha=linha->prox;
	}
}


int main(void){
	Linha *codigo;
    exibirParticipantes();
    char opcao;
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
            //não é possivel fazer as outras coisas se ele não ler o arquivo primeiro
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
						                ExecutaSequencial(codigo);
						                break;
						            case 67://F9 Mostrar conteudo da Memoria RAM 
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

