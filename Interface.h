#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <conio2.h>


//interface
void Moldura(int ci, int li, int cf, int lf, int corT, int corF) {
    int i;
    textcolor(corT);
    textbackground(corF);
    gotoxy(ci, li);
    printf("%c", 201);
    gotoxy(ci, lf);
    printf("%c", 200);
    gotoxy(cf, li);
    printf("%c", 187);
    gotoxy(cf, lf);
    printf("%c", 188);
    for (i = ci + 1; i < cf; i++) {
        gotoxy(i, li);
        printf("%c", 205);
        gotoxy(i, lf);
        printf("%c", 205);
        //Sleep(0.1);
    }
    for (i = li + 1; i < lf; i++) {
        gotoxy(ci, i);
        printf("%c", 186);
        gotoxy(cf, i);
        printf("%c", 186);
        //Sleep(0.1);
    }
}

void FormPrincipal(void) {
    Moldura(1, 1, 120, 30, 6, 0);
    Moldura(2, 2, 119, 4, 7, 0);
    gotoxy((120 - strlen("=== Interpretador JavaScript ===")) / 2, 3);
    printf("=== Interpretador JavaScript ===");
    Moldura(2, 5, 25, 29, 9, 0);
    Moldura(26, 5, 119, 29, 3, 0);
}

void Menu1() {
    system("cls");
	FormPrincipal();
    textcolor(15);
    textbackground(0);
    textcolor(10);
    textbackground(0);
    gotoxy(3,21);
    printf("[F7] Abrir Arquivo");
    gotoxy(3,22);
    printf("[ESC] - Sair");
}

void Menu2(){
	system("cls");
	FormPrincipal();
    textcolor(15);
    textbackground(0);
    textcolor(10);
    textbackground(0);
    gotoxy(3,18);
    printf("[F8] Executar programa");
    gotoxy(3,19);
    printf("[F9] Mostrar conteudo");
    gotoxy(3,20);
    printf("da Memoria RAM");
    gotoxy(3,21);
    printf("[F10] Mostrar tela");
    gotoxy(3,22);
    printf("[ESC] - Voltar");
}


void exibirParticipantes(void){
	Moldura(1, 1, 120, 30, 6, 0);
    Moldura(2, 2, 119, 4, 7, 0);
    Moldura(2, 5, 119, 29, 3, 0);
    textcolor(15);
    textbackground(0);
	gotoxy(44,3);printf("### PARTICIPANTES DO GRUPO ###");
	textcolor(2);
    textbackground(0);
    gotoxy(45,11);printf("Daniel Martins de Almeida Neves");
    gotoxy(45,13);printf("Guilherme Gouveia de Oliveira e Silva");
    textcolor(0);
    textbackground(0);
    Sleep(2000);
}

//fim da interface
