#include<conio.h>
#include<locale.h>
#include<stdbool.h>
#include<stdio.h>
#include<windows.h>
#include<wincon.h>


//Exibe uma mensagem e pausa a execucao
void mensagemPausa(char* msg) {
  printf(msg);
  getchar();
}

void inicializacao() {
  system("cls");

  // define o tamanho da tela
  system("mode con:cols=110 lines=30");
}

// 1 => exibe o cursor
// 0 => esconde o cursor
void cursor(int status) {
  switch (status) {
  case 0: {
    CONSOLE_CURSOR_INFO cursor = { 1, FALSE };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    break;
  }
  case 1: {
    CONSOLE_CURSOR_INFO cursor = { 1, TRUE };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    break;
  }
  }
}

// x => coluna, y => linha
void gotoxy(int x, int y)
{
  COORD c;

  c.X = x - 1;
  c.Y = y - 1;

  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}