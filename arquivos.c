#include<conio.h>
#include<stdbool.h>
#include<stdio.h>
#include<windows.h>

#include"util/util.h"

///////////////////////////////////////////////////////////////// FUNÇÕES

void menuInicialConfiguracao(){
  cursor(0); // esconde o cursor

  int pos = 10;
  unsigned char input;
  bool flagAjuda = false, continuaExecucao = true;

  do{
    inicializacao();

    gotoxy(5, 3); printf("[ESC] Voltar");
    gotoxy(20, 3); printf("[F1] Ajuda");

    gotoxy(5, 5); printf("PRODUCT MANAGER");
    gotoxy(5, 6); printf("Configurações");

    gotoxy(5, 10); printf("Gerenciar diretórios");
    gotoxy(5, 11); printf("Data e Horário");
    gotoxy(5, 12); printf("Voltar");

    if (flagAjuda){
      // implementar alguma coisa
    }

    gotoxy(3, pos); printf(">"); // coloca a seta na posição

    input = getch();

    gotoxy(3, pos); printf(" "); // coloca a seta na posição

    switch (input){
      case 72: // seta para cima
        pos -= 1;
        if(pos < 10) pos = 12;
        break;
      case 80: // seta para baixo
        pos += 1;
        if(pos > 12) pos = 10;
        break;
      case 27: // esc
        continuaExecucao = 0;
        system("cls");
        break;
      default: break;
    }

  }while(continuaExecucao);
}