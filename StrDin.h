#include <stdio.h>
#include <stdlib.h>

struct stringdin{
	char letra;
	struct stringdin *prox;
};typedef strut stringdin StrDin;

void init(StrDin **str){
	*str=NULL;
}

void push(StrDin **str, char c){
	StrDin *nova = (StrDin*)malloc(sizeof(StrDin));
	nova->letra=c;
	nova->prox=*str;
	*str=nova;
}
