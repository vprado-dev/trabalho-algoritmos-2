#include<conio.h>
#include<locale.h>
#include<stdbool.h>
#include<stdio.h>
#include<windows.h>
#include<wincon.h>

#include"util/util.h"

void menuInicial();

int main() {
  setlocale(LC_ALL, "pt_br");

  SetConsoleTitle("Trabalho 2 - Eduardo Pires & Vinicius Prado");

  menuInicial();

  return 0;
}

/////////////////////////////////////////////////////////////////

void menuInicial() {
  cursor(0); // esconde o cursor

  int pos = 10;
  unsigned char input;
  bool flagAjuda = false, continuaExecucao = true;

  do {
    inicializacao();

    gotoxy(5, 3); printf("[ESC] Sair");
    gotoxy(20, 3); printf("[F1] Ajuda");

    gotoxy(5, 5); printf("Escolha uma das opções!");

    gotoxy(5, 10); printf("Gerenciamento de arquivos");
    gotoxy(5, 11); printf("Gerenciamento de jogadores");
    gotoxy(5, 12); printf("Sair");

    gotoxy(3, pos); printf(">"); // coloca a seta na posição

    input = getch();

    gotoxy(3, pos); printf(" "); // coloca a seta na posição

    if (flagAjuda) { // MELHORAR!!!!!!!
      gotoxy(60, 16);
      printf("Escolha uma opção!!");
    }

    switch (input){
      case 72: // seta para cima
        pos -= 1;
        if(pos < 10) pos = 12;
        break;
      case 80: // seta para baixo
        pos += 1;
        if(pos > 12) pos = 10;
        break;
      case 13: // enter
        // chamar as devidas funções
        break;
      case ';':
        flagAjuda = true;
        break;
      default: break;
    }

  } while (continuaExecucao);

}