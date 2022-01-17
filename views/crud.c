#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <windows.h>

#include "../util/util.h"
#include "./arquivos.h"
#include "../functions/fncrud.h"

FILE* fp;

void menuInicialCrud(dateTime dataHora, char *nomeArquivo){
  cursor(0);

  int pos = 10;
  unsigned char input;
  bool flagAjuda = false, continuaExecucao = true;

  //Chamar depois que ja tiver alterado a variavel fileName
  setupArquivo(nomeArquivo, &fp);

  do{
    inicializacao(dataHora);

    char titulo[] = "Gerenciamento de Produtos";
    criaCabecalho(titulo);

    // printando removendo o "files/"
    gotoxy(5, 8); printf("Arquivo: %s", nomeArquivo + 6);

    gotoxy(5, 10); printf("Cadastrar novo produto");
    gotoxy(5, 11); printf("Listar Produtos");
    gotoxy(5, 12); printf("Alterar Produto");
    gotoxy(5, 13); printf("Deletar Produto");
    gotoxy(5, 14); printf("Pesquisar Produto");
    gotoxy(5, 15); printf("Voltar");
    
    if (flagAjuda){ // implementar ajuda

    }

    gotoxy(3, pos); printf(">"); // coloca a seta na posição

    input = getch();

    gotoxy(3, pos); printf(" "); // coloca a seta na posição

    switch(input){
      case 72: // seta para cima
        pos -= 1;
        if (pos < 10) pos = 15;
        break;
      case 80: // seta para baixo
        pos += 1;
        if (pos > 15) pos = 10;
        break;
      case 13: // enter
        if(pos == 10) incluiProduto();
        if(pos == 11) listaProdutos();
        if(pos == 12) alteraProduto();
        if(pos == 13){
          excluiProduto();
          setupArquivo(nomeArquivo, &fp);
        }
        if(pos == 14) pesquisaProduto();
        if(pos == 15){ // voltar
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