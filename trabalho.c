#include<conio.h>
#include<locale.h>
#include<stdbool.h>
#include<stdio.h>
#include<windows.h>
#include<wincon.h>

#include"util/util.h"

char[] nomeArquivo; // usar esse arquivo para o CRUD

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

    gotoxy(5, 5); printf("PRODUCT MANAGER");
    gotoxy(5, 6); printf("Escolha uma das opções!");

    gotoxy(5, 10); printf("Gerenciamento de arquivos");
    gotoxy(5, 11); printf("Gerenciamento de produtos");
    gotoxy(5, 12); printf("Sair");

    if (flagAjuda) {
      gotoxy(55, 16); printf("[Gerenciamento de arquivos]");
      gotoxy(65, 17); printf("Permite a manipulação dos arquivos do CRUD!");
      gotoxy(55, 19); printf("[Gerenciamento de produtos]");
      gotoxy(65, 20); printf("Permite a manipulação dos produtos do CRUD!");
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
      case 13: // enter
        if(pos == 12){
          continuaExecucao = 0;
          system("cls");
        }
        break;
      case 27: // esc
        continuaExecucao = 0;
        system("cls");
        break;
      case ';': // F1
        flagAjuda = true;
        break;
      default: break;
    }

  } while (continuaExecucao);
}