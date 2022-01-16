#include<conio.h>
#include<locale.h>
#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<wincon.h>

///////////////////////////////////////////////////////////////// TIPOS

struct dateTime{
  int minuto;
  int hora;
  int dia;
  int mes;
  int ano;
};

typedef struct dateTime dateTime;

///////////////////////////////////////////////////////////////// CABEÇALHOS

void gotoxy(int, int);

///////////////////////////////////////////////////////////////// FUNÇÕES

void inicializacao(dateTime dataHora){
    system("cls");
    
    // define o tamanho da tela
    system("mode con:cols=110 lines=30");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if(dataHora.minuto == 0 &&
      dataHora.hora == 0 &&
      dataHora.dia == 0 &&
      dataHora.mes == 0 &&
      dataHora.ano == 0){
      gotoxy(80, 3); printf("%02d:%02d %02d/%02d/%02d", tm.tm_hour, tm.tm_min, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    }
    else{
      gotoxy(80, 3); printf("%02d:%02d %02d/%02d/%02d", dataHora.minuto, dataHora.hora, dataHora.dia, dataHora.mes, dataHora.ano);
    }
}

void criaCabecalho(char title[]){
  gotoxy(5, 3); printf("[ESC] Sair");
  gotoxy(20, 3); printf("[F1] Ajuda");

  gotoxy(5, 5); printf("PRODUCT MANAGER");
  gotoxy(5, 6); printf("%s", title);
}

// 1 => exibe o cursor
// 0 => esconde o cursor
void cursor(int status){
	switch (status) {
		case 0: {
			CONSOLE_CURSOR_INFO cursor = {1, FALSE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
		case 1: {
			CONSOLE_CURSOR_INFO cursor = {1, TRUE};
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