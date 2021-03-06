#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "../util/util.h"

FILE* fp;
FILE* fp_tmp;

typedef struct {
  char codigo_barras[100];
  char nome[50];
  int quantidade;
  double preco;
  bool excluido;
}Produto;

void leProduto(Produto* p, int linhaInicio) {
  if(linhaInicio == 10){
    char titulo[] = "Cadastro de Produtos";
    criaCabecalho(titulo);
  }

  gotoxy(5, linhaInicio); printf("Codigo de barras: "); gets(p->codigo_barras);
  gotoxy(5, linhaInicio + 1); printf("Nome: ");             gets(p->nome);
  gotoxy(5, linhaInicio + 2); printf("Quantidade: ");       scanf("%d", &p->quantidade);
  gotoxy(5, linhaInicio + 3); printf("Preco: ");            scanf("%lf", &p->preco); 

  p->excluido = false;

  fflush(stdin);
}

void inserirProduto(Produto p) {
  fseek(fp, 0L, SEEK_END);
  if (fwrite(&p, sizeof(p), 1, fp) != 1) {
    mensagemPausa("Inserir produto: Falhou a escrita do registro\n");
  }
}

void incluiProduto() {
  Produto prod;
  system("cls");
  leProduto(&prod, 10);
  inserirProduto(prod);
}

void setupArquivo(char* nomeArq, FILE** file) {
  *file = fopen(nomeArq, "r+b");
  if (*file == NULL) {
    *file = fopen(nomeArq, "w+b");
    if (*file == NULL) {
      fprintf(stderr, " Erro fatal: impossível criar arquivo de dados\n");
      getchar();
      exit(1);
    }
  }
}

void exibeProduto(Produto p) {
  printf("Código de Barras: %s | Nome: %s | Quantidade: %d | Preco: %.2f reais\n", p.codigo_barras, p.nome, p.quantidade, p.preco);
}

void listaProdutos() {
  long int n_Linhas = 0;
  Produto reg;
  rewind(fp);

  system("cls");

  char titulo[] = "Listagem de Produtos";
  criaCabecalho(titulo);

  while (1) {
    if (fread(&reg, sizeof(reg), 1, fp) != 1) break;
    if (reg.excluido == 1) continue;

    gotoxy(5, n_Linhas + 10);
    exibeProduto(reg);
    n_Linhas++;

    if (n_Linhas % 20 == 0) {
      n_Linhas = 0;
      mensagemPausa("Pressione <Enter> para continuar .  .  .");
    }
  }
  gotoxy(5, n_Linhas + 12); mensagemPausa("Pressione <Enter> para continuar .  .  .");
}

void alteraProduto() {
  Produto p;
  char nomeProduto[50];
  
  system("cls");
  char titulo[] = "Listagem de Produtos";
  criaCabecalho(titulo);
  
  gotoxy(5, 8); printf("Nome do produto: ");
  
  gets(nomeProduto); fflush(stdin);
  rewind(fp);

  while (fread(&p, sizeof(Produto), 1, fp) != 0) {
    if (strcmp(nomeProduto, p.nome) == 0) {
      gotoxy(5, 10); printf("DADOS ATUAIS");
      gotoxy(7, 12); exibeProduto(p);
      gotoxy(5, 15); printf("NOVOS DADOS");
      leProduto(&p, 17);

      fseek(fp, -(long)sizeof(Produto), SEEK_CUR);
      fwrite(&p, sizeof(Produto), 1, fp);
      fflush(fp);
    }
  }
}

void exclusaoFisicaProduto(char* nome, char* fileName) {
  Produto p;
  int found = 0;

  rewind(fp);

  // Cria arquivo temporario
  setupArquivo("prod_tmp.bin", &fp_tmp);

  //Percorre o arquivo procurando nome
  while (fread(&p, sizeof(Produto), 1, fp) != 0) {
    if (strcmp(nome, p.nome) == 0) {
      found = 1;
      gotoxy(5, 15); printf("Dados atuais:");
      gotoxy(7, 17); exibeProduto(p);

      char resp;
      gotoxy(7, 20); printf("Confirma a exclusão? (S/N) "); resp = getchar();
      fflush(stdin);

      if (toupper(resp) != 'S') {
        return;
      }

      gotoxy(7, 22); mensagemPausa("Produto encontrado e deletado.");
    } else {
      fwrite(&p, sizeof(Produto), 1, fp_tmp);
    }
  }

  if (!found) {
    gotoxy(7, 22); mensagemPausa("Produto nao encontrado.\n");
    return;
  }

  fclose(fp);
  fclose(fp_tmp);

  remove(fileName);
  rename("prod_tmp.bin", fileName);

  return;
}

void exclusaoLogicaProduto(char* nome) {
  Produto p;
  int found = 0;
  rewind(fp);

  //Percorre o arquivo procurando nome
  while (fread(&p, sizeof(Produto), 1, fp) != 0) {
    if (strcmp(nome, p.nome) == 0) {
      //Encontrou o registro
      found = 1;
      gotoxy(5, 15); printf("Dados atuais:");
      gotoxy(7, 17); exibeProduto(p);

      char resp;
      gotoxy(7, 20); printf("Confirma a exclusão? (S/N) "); resp = getchar();
      fflush(stdin);

      if (toupper(resp) != 'S') {
        return;
      }

      p.excluido = true;

      fseek(fp, -(long)sizeof(Produto), SEEK_CUR);
      fwrite(&p, sizeof(Produto), 1, fp);
      fflush(fp);
      gotoxy(7, 20); mensagemPausa("Produto encontrado e deletado.");
    }
  }

  if (!found) {
    gotoxy(7, 20); mensagemPausa("Produto não encontrado.");
    return;
  }

  return;
}

void excluiProduto(char* fileName) {
  char produtoPesquisa[50];
  char resp;

  system("cls");
  char titulo[] = "Exclusão de Produtos";
  criaCabecalho(titulo);

  gotoxy(5, 10); printf("Qual o nome do produto: ");
  gets(produtoPesquisa); fflush(stdin);

  gotoxy(5, 12); printf("Exclusão Física (s/n)?: "); resp = getchar();
  fflush(stdin);

  if (toupper(resp) != 'S') exclusaoLogicaProduto(produtoPesquisa);
  else exclusaoFisicaProduto(produtoPesquisa, fileName);

}

void pesquisaProdutoCodigo(char* codBarras) {
  Produto p;
  rewind(fp);
  while (fread(&p, sizeof(Produto), 1, fp) != 0) {
    if (p.excluido != true && strcmp(codBarras, p.codigo_barras) == 0) {
      exibeProduto(p);
    }
  }

  gotoxy(5, 29); mensagemPausa("Pressione <Enter> para continuar...");
}

void pesquisaProdutoPreco(double preco) {
  Produto p;
  rewind(fp);

  while (fread(&p, sizeof(Produto), 1, fp)) {
    if (p.excluido != true && p.preco == preco) {
      exibeProduto(p);
    }
  }

  gotoxy(5, 29); mensagemPausa("\n\n Pressione <Enter> para continuar .  .  .");
}

void pesquisaProduto() {
  int op = 0;
  gotoxy(5, 10); printf("Pelo que deseja pesquisar?");
  gotoxy(7, 11); printf("1 - Código de Barras");
  gotoxy(7, 12); printf("2 - Preço");
  scanf("%d", &op); fflush(stdin);

  if (op != 1 && op != 2){
    return;
  } 
  else if (op == 1) {
    char codBarras[50];
    gotoxy(7, 12); printf("Qual o código de barras do produto a procurar: ");
    gets(codBarras); fflush(stdin);
    pesquisaProdutoCodigo(codBarras);
  } 
  else if (op == 2) {
    double preco;
    gotoxy(7, 12); printf("Qual o preço do produto a procurar: ");
    scanf("%lf", &preco); fflush(stdin);
    pesquisaProdutoPreco(preco);
  }

  return;
}
