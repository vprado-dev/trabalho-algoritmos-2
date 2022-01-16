#ifndef __UTIL_H_
#define __UTIL_H_

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

void inicializacao();
void cursor(int status);
void gotoxy(int x, int y);
void criaCabecalho(char []);

#endif