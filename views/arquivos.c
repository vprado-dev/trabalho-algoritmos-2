#include <conio.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <windows.h>

#include "../util/util.h"

///////////////////////////////////////////////////////////////// CONSTANTES

const char* name = "files";

///////////////////////////////////////////////////////////////// CABEÇALHO

void alteraDataHora(dateTime* dataHora);
void resetaDataHora(dateTime* dataHora);
void listaArquivos(dateTime* dataHora);
bool verificaFiles();
void renomeiaArquivo();
void deletaArquivo();

///////////////////////////////////////////////////////////////// FUNÇÕES

void menuInicialConfiguracao(dateTime* dataHora) {
  cursor(0); // esconde o cursor

  dateTime dataHoraLocal = (*dataHora);
  int pos = 10;
  unsigned char input;
  bool flagAjuda = false, continuaExecucao = true;

  do {
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

    if (flagAjuda) {
      // implementar alguma coisa
    }

    gotoxy(3, pos); printf(">"); // coloca a seta na posição

    input = getch();

    gotoxy(3, pos); printf(" "); // coloca a seta na posição

    switch (input) {
    case 72: // seta para cima
      pos -= 1;
      if (pos < 10) pos = 16;
      break;
    case 80: // seta para baixo
      pos += 1;
      if (pos > 16) pos = 10;
      break;
    case 13: // enter
      if (pos == 10) { // listar arquivos
        listaArquivos(&dataHoraLocal);
      }
      if (pos == 11) {
        renomeiaArquivo();
      }
      if (pos == 12) {
        deletaArquivo();
      }
      if (pos == 14) { // alterar data e hora
        alteraDataHora(&dataHoraLocal);
      }
      if (pos == 15) { // resetar data e hora
        resetaDataHora(&dataHoraLocal);
      }
      if (pos == 16) { // voltar
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

  } while (continuaExecucao);

  (*dataHora) = dataHoraLocal;
}

void alteraDataHora(dateTime* dataHora) {
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

void resetaDataHora(dateTime* dataHora) {
  (*dataHora).minuto = 0;
  (*dataHora).hora = 0;
  (*dataHora).dia = 0;
  (*dataHora).mes = 0;
  (*dataHora).ano = 0;
}

void listaArquivos(dateTime* dataHora) {
  if (!verificaFiles()) {
    system("mkdir files");
  }

  DIR* dr = opendir("files/");

  struct dirent* dir;


  // verificando se não houve nenhum erro
  if (dr == NULL)
  {
    printf("Houve um erro no programa!");
    return;
  }

  // listando os arquivos

  int linhas = 10, num = 1;
  while ((dir = readdir(dr)) != NULL) {
    if (!strcmp(dir->d_name, ".") || !(strcmp(dir->d_name, ".."))) {
      continue;
    }

    gotoxy(45, linhas); printf("[%d]", num);
    gotoxy(50, linhas); printf("%s\n", dir->d_name);
    num += 1;
    linhas += 1;

    if (num == 15) { // limite de quinze arquivos
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

void renomeiaArquivo() {
  char nome1[50] = "files/";
  char nome2[50] = "files/";
  char nomeArquivo[50];
  gotoxy(40, 20); printf("Insira o nome do arquivo a ser alterado (com extensão): ");
  gets(nomeArquivo); fflush(stdin);

  char nomeArquivoAtualizado[50];
  gotoxy(40, 22); printf("Insira o novo nome do arquivo (com extensão): ");
  gets(nomeArquivoAtualizado); fflush(stdin);

  strcat(nome1, nomeArquivo);

  strcat(nome2, nomeArquivoAtualizado);

  int result = rename(nome1, nome2);

  if (result == 0) {
    gotoxy(40, 25); mensagemPausa("O arquivo foi alterado com sucesso.");
  } else {
    gotoxy(40, 25); mensagemPausa("Falha na alteração do arquivo...");
  }
}

void deletaArquivo() {
  char dir[50] = "files/";
  char nomeArquivo[50];
  gotoxy(40, 20); printf("Insira o nome do arquivo a ser deletado (com extensão): ");
  gets(nomeArquivo); fflush(stdin);

  strcat(dir, nomeArquivo);

  if (remove(dir) == 0) {
    gotoxy(40, 25); mensagemPausa("Arquivo deletado com sucesso.");
  } else {
    gotoxy(40, 25); mensagemPausa("Falha ao deletar arquivo.");
  }
}

bool verificaFiles() {
  struct dirent* de;
  DIR* dr = opendir(".");

  while ((de = readdir(dr)) != NULL) {
    if (strcmp(de->d_name, "files") == 0) {
      return true;
    }
  }

  return false;
}

