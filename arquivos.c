#include<stdio.h>
#include<windows.h>

#include"util/util.h"

///////////////////////////////////////////////////////////////// FUNÇÕES

void menuInicialConfiguracao(){
  cursor(0); // esconde o cursor

  inicializacao();

  gotoxy(5, 3); printf("[ESC] Sair");
  gotoxy(20, 3); printf("[F1] Ajuda");

  gotoxy(5, 5); printf("PRODUCT MANAGER");
  gotoxy(5, 6); printf("Configurações");

  system("pause");
}