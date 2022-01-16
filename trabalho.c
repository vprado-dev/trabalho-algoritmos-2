#include<conio.h>
#include<locale.h>
#include<stdbool.h>
#include<stdio.h>
#include<windows.h>
#include<wincon.h>

#include"util/util.h"

FILE* fp; //produtos

typedef struct {
  char codigo_barras[100];
  char nome[50];
  int quantidade;
  double preco;
  bool excluido;
}Produto;

char fileName[50] = "produtos.bin";


// Declaracoes de Funcoes
void menuInicial();
void leProduto(Produto* p);
void inserirProduto(Produto p);
void incluiProduto();
void criaArquivo();
void listaProdutos();
void exibeProduto(Produto p);
void alteraProduto();

int main() {
  //Chamar depois que ja tiver alterado a variavel fileName
  criaArquivo();

  // Insere produto
  incluiProduto();

  // Lista produtos - TODOS
  listaProdutos();

  //Altera produto
  alteraProduto();

  return 0;

  setlocale(LC_ALL, "pt_br");

  SetConsoleTitle("Trabalho 2 - Eduardo Pires & Vinicius Prado");

  menuInicial();
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

    gotoxy(5, 5); printf("SOCCER PLAYER MANAGER");
    gotoxy(5, 6); printf("Escolha uma das opções!");

    gotoxy(5, 10); printf("Gerenciamento de arquivos");
    gotoxy(5, 11); printf("Gerenciamento de jogadores");
    gotoxy(5, 12); printf("Sair");

    gotoxy(3, pos); printf(">"); // coloca a seta na posição

    input = getch();

    gotoxy(3, pos); printf(" "); // coloca a seta na posição

    if (flagAjuda) { // MELHORAR!!!!!!!
      gotoxy(60, 16);
      printf("Escolha uma opção!!");
    }

    switch (input) {
    case 72: // seta para cima
      pos -= 1;
      if (pos < 10) pos = 12;
      break;
    case 80: // seta para baixo
      pos += 1;
      if (pos > 12) pos = 10;
      break;
    case 13: // enter
      // chamar as devidas funções
      break;
    case ';':
      flagAjuda = true;
      break;
    default: break;
    }

  } while (continuaExecucao);

}

void leProduto(Produto* p) {
  printf("Codigo de barras: ");gets(p->codigo_barras);
  printf("Nome: ");gets(p->nome);
  printf("Quantidade: ");scanf("%d", &p->quantidade);
  printf("Preco: "); scanf("%lf", &p->preco);
  p->excluido = false;
  fflush(stdin);
}

void inserirProduto(Produto p) {
  fseek(fp, 0L, SEEK_END);
  if (fwrite(&p, sizeof(p), 1, fp) != 1) {
    printf("Inserir produto: Falhou a escrita do registro\n");
    system("pause");
  }
}

void incluiProduto() {
  Produto prod;
  leProduto(&prod);
  inserirProduto(prod);
}

void criaArquivo() {
  fp = fopen(fileName, "r+b");
  if (fp == NULL) {
    fp = fopen(fileName, "w+b");
    if (fp == NULL) {
      fprintf(stderr, " Erro fatal: impossível criar arquivo de dados\n");
      getchar();
      exit(1);
    }
  }
}

void exibeProduto(Produto p) {
  printf("Cod. de Barras: %s // Nome: %s // Qtd.: %d // Preco: %.2f reais \n", p.codigo_barras, p.nome, p.quantidade, p.preco);
}

void listaProdutos() {
  long int n_Linhas = 0;
  Produto reg;
  rewind(fp);

  while (1) {
    if (fread(&reg, sizeof(reg), 1, fp) != 1)break;
    if (reg.excluido == true) continue;
    exibeProduto(reg);
    n_Linhas++;
    if (n_Linhas % 20 == 0) {
      mensagemPausa("Pressione <Enter> para continuar .  .  .");
    }
  }
  mensagemPausa("\n\nPressione <Enter> para continuar .  .  .");
}

void alteraProduto() {
  Produto p;
  long int n_reg;

  printf("Qual o numero do registro: ");
  scanf("%ld", &n_reg); fflush(stdin);

  if (fseek(fp, (n_reg - 1) * sizeof(Produto), SEEK_SET) != 0) {
    mensagemPausa("Registro inexistente ou problemas no posicionamento!!!");
    return;
  }

  if (fread(&p, sizeof(Produto), 1, fp) != 1) {
    mensagemPausa("Problemas na leitura do registro!!!");
    return;
  }

  if (p.excluido == true) {
    mensagemPausa("Um registro apagado não pode ser alterado!!! \n\n");
    return;
  }

  printf("\n\n Dados Atuais:\n\n");
  exibeProduto(p);
  printf("\n\n Novos dados \n\n");
  leProduto(&p);

  fseek(fp, -(long)sizeof(Produto), SEEK_CUR);

  fwrite(&p, sizeof(Produto), 1, fp);
  fflush(fp);
}