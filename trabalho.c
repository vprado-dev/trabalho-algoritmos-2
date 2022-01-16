#include <conio.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <windows.h>
#include <wincon.h>

#include "util/util.h"
#include "arquivos.h"

///////////////////////////////////////////////////////////////// VARIÁVEIS

dateTime dataHora; // datetime definido pelo usuário

///////////////////////////////////////////////////////////////// CABEÇALHOS

void menuInicial();
void iniciaData();

///////////////////////////////////////////////////////////////// FUNÇÕES

int main() {
  setlocale(LC_ALL, "pt_br");

  SetConsoleTitle("Trabalho 2 - Eduardo Pires & Vinicius Prado");

  iniciaData();

  menuInicial();

  return 0;
}

void menuInicial() {
  cursor(0); // esconde o cursor

  int pos = 10;
  unsigned char input;
  bool flagAjuda = false, continuaExecucao = true;

  do {
    inicializacao(dataHora);

    char titulo[] = "Menu Inicial";
    criaCabecalho(titulo);

    gotoxy(5, 10); printf("Gerenciamento de produtos");
    gotoxy(5, 11); printf("Configurações");
    gotoxy(5, 12); printf("Sair");

    if (flagAjuda) {
      gotoxy(45, 16); printf("[Gerenciamento de produtos]");
      gotoxy(55, 17); printf("Permite a manipulação dos produtos cadastrados");
      gotoxy(70, 18); printf("e o cadastro de novos produtos!");

      gotoxy(45, 20); printf("[Configurações]");
      gotoxy(55, 21); printf("Alteração de informações do sistema");
      gotoxy(70, 22); printf("e gerenciamento de arquivos.");
      
      gotoxy(45, 24); printf("[Sair]");
      gotoxy(55, 25); printf("Encerra o sistema");
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
        if(pos == 11){ // configurações
          menuInicialConfiguracao(&dataHora);
        }
        if(pos == 12){ // sair
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

void iniciaData(){
  dataHora.minuto = 0;
  dataHora.hora = 0;
  dataHora.dia = 0;
  dataHora.mes = 0;
  dataHora.ano = 0;
}