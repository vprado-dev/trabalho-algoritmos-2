#include<conio.h>
#include<stdbool.h>
#include<stdio.h>
#include<windows.h>

#include"util/util.h"

///////////////////////////////////////////////////////////////// CABEÇALHO

void alteraDataHora(dateTime *dataHora);

///////////////////////////////////////////////////////////////// FUNÇÕES

void menuInicialConfiguracao(dateTime *dataHora){
  cursor(0); // esconde o cursor

  dateTime dataHoraLocal = (*dataHora);
  int pos = 10;
  unsigned char input;
  bool flagAjuda = false, continuaExecucao = true;

  do{
    inicializacao(dataHoraLocal);

    char titulo[] = "Configurações";
    criaCabecalho(titulo);

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
      case 13: // enter
        if(pos == 11){
          alteraDataHora(&dataHoraLocal);
        }
        break;
      case 27: // esc
        continuaExecucao = 0;
        system("cls");
        break;
      default: break;
    }

  }while(continuaExecucao);

  (*dataHora) = dataHoraLocal;
}

void alteraDataHora(dateTime *dataHora){
  cursor(1);

  gotoxy(60, 10); printf("É necessário apertar [Enter] em cada campo");

  gotoxy(80, 5); printf("  :     /  /");
  gotoxy(80, 5); scanf("%d", &((*dataHora).minuto));
  gotoxy(83, 5); scanf("%d", &((*dataHora).hora));
  gotoxy(86, 5); scanf("%d", &((*dataHora).dia));
  gotoxy(89, 5); scanf("%d", &((*dataHora).mes));
  gotoxy(92, 5); scanf("%d", &((*dataHora).ano));

  cursor(0);
}