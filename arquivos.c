#include <conio.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <windows.h>

#include"util/util.h"

///////////////////////////////////////////////////////////////// CONSTANTES

const char *name = "files";

///////////////////////////////////////////////////////////////// CABEÇALHO

void alteraDataHora(dateTime *dataHora);
void resetaDataHora(dateTime *dataHora);
void listaArquivos(dateTime *dataHora);
bool verificaFiles();

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

    gotoxy(5, 10); printf("Listar arquivos");
    gotoxy(5, 11); printf("Renomear um arquivo");
    gotoxy(5, 12); printf("Deletar arquivos");
    gotoxy(5, 13); printf("Definir arquivo do CRUD");
    gotoxy(5, 14); printf("Alterar Data e Hora");
    gotoxy(5, 15); printf("Resetar Data e Hora");
    gotoxy(5, 16); printf("Voltar");

    if (flagAjuda){
      // implementar alguma coisa
    }

    gotoxy(3, pos); printf(">"); // coloca a seta na posição

    input = getch();

    gotoxy(3, pos); printf(" "); // coloca a seta na posição

    switch (input){
      case 72: // seta para cima
        pos -= 1;
        if(pos < 10) pos = 16;
        break;
      case 80: // seta para baixo
        pos += 1;
        if(pos > 16) pos = 10;
        break;
      case 13: // enter
        if(pos == 10){ // gerenciar diretórios
          listaArquivos(&dataHoraLocal);
        }
        if(pos == 11){ // alterar data e hora
          alteraDataHora(&dataHoraLocal);
        }
        if(pos == 12){ // resetar data e hora
          resetaDataHora(&dataHoraLocal);
        }
        if(pos == 13){ // voltar
          continuaExecucao = 0;
          system("cls");
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

void resetaDataHora(dateTime *dataHora){
  (*dataHora).minuto = 0;
  (*dataHora).hora = 0;
  (*dataHora).dia = 0;
  (*dataHora).mes = 0;
  (*dataHora).ano = 0;
}

void listaArquivos(dateTime *dataHora){
  if(!verificaFiles())
    system("mkdir files");

  struct dirent *de;
  DIR *dr = opendir("./files");

  // verificando se não houve nenhum erro
  if (dr == NULL) 
  {
      printf("Houve um erro no programa!");
      return;
  }

  // verificando se existem arquivos na pasta

  bool possuiArquivos = false;

  while ((de = readdir(dr)) != NULL){
    if(strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..")){
      possuiArquivos = true;
      break;
    }
  }

  if(!possuiArquivos){
    gotoxy(50, 10); printf("Não existem arquivos válidos a serem exibidos!");
    gotoxy(50, 11); printf("Pressione qualquer tecla para continuar...");
    system("pause >nul");
    return;
  }

  // listando os arquivos

  int linhas = 10, num = 1;
  while((de = readdir(dr)) != NULL){
    gotoxy(45, linhas); printf("[%d]", num);
    gotoxy(50, linhas); printf("%s\n", de->d_name);
    num += 1;
    linhas += 1;

    if(num == 15){ // limite de quinze arquivos
      gotoxy(50, linhas + 2); printf("Deseja gerenciar mais arquivos?");
      gotoxy(50, linhas + 3); printf("É necessário obter a versão premium!");
      break;
    }
  }

  closedir(dr); 
  gotoxy(50, linhas + 4); printf("Pressione qualquer tecla para continuar...");
  system("pause >nul");

  return;
}

bool verificaFiles(){
  struct dirent *de;
  DIR *dr = opendir(".");

  while ((de = readdir(dr)) != NULL){
    if(strcmp(de->d_name, "files") == 0){
      return true;
    }
  }

  return false;
}

