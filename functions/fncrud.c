#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../util/util.h"

FILE* fp; //produtos
FILE* fp_tmp; //file temporario para exclusao fisica

typedef struct {
  char codigo_barras[100];
  char nome[50];
  int quantidade;
  double preco;
  bool excluido;
}Produto;

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
    mensagemPausa("Inserir produto: Falhou a escrita do registro\n");
  }
}

void incluiProduto() {
  Produto prod;
  leProduto(&prod);
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
  printf("Cod. de Barras: %s // Nome: %s // Qtd.: %d // Preco: %.2f reais\n", p.codigo_barras, p.nome, p.quantidade, p.preco);
}

void listaProdutos() {
  long int n_Linhas = 0;
  Produto reg;
  rewind(fp);

  while (1) {
    if (fread(&reg, sizeof(reg), 1, fp) != 1)break;
    if (reg.excluido == 1) continue;
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
  char nomeProduto[50];
  printf("Qual o nome do produto: ");
  gets(nomeProduto); fflush(stdin);

  rewind(fp);

  while (fread(&p, sizeof(Produto), 1, fp) != 0) {
    if (strcmp(nomeProduto, p.nome) == 0) {
      printf("\n\n Dados Atuais:\n\n");
      exibeProduto(p);
      printf("\n\n Novos dados \n\n");
      leProduto(&p);

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
      //Encontrou o registro
      found = 1;
      printf("\n\nDados atuais:\n\n");
      exibeProduto(p);

      char resp;
      printf("\n\nConfirma Exclusao (s/n)?: "); resp = getchar();
      fflush(stdin);

      if (toupper(resp) != 'S') {
        return;
      }

      mensagemPausa("Produto encontrado e deletado.\n");
    } else {
      fwrite(&p, sizeof(Produto), 1, fp_tmp);
    }
  }

  if (!found) {
    mensagemPausa("Produto nao encontrado.\n");
  }

  fclose(fp);
  fclose(fp_tmp);

  remove(fileName);
  rename("prod_tmp.bin", fileName);
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
      printf("\n\nDados atuais:\n\n");
      exibeProduto(p);

      char resp;
      printf("\n\nConfirma Exclusao (s/n)?: "); resp = getchar();
      fflush(stdin);

      if (toupper(resp) != 'S') {
        return;
      }

      p.excluido = true;

      fseek(fp, -(long)sizeof(Produto), SEEK_CUR);
      fwrite(&p, sizeof(Produto), 1, fp);
      fflush(fp);
      mensagemPausa("Produto encontrado e deletado.\n");
    }
  }

  if (!found) {
    mensagemPausa("Produto nao encontrado.\n");
  }
}

void excluiProduto(char* fileName) {
  char produtoPesquisa[50];
  char resp;

  printf("Qual o nome do produto: ");
  gets(produtoPesquisa); fflush(stdin);

  printf("\n\nExclusao Fisica (s/n)?: "); resp = getchar();
  fflush(stdin);

  if (toupper(resp) != 'S') {
    exclusaoLogicaProduto(produtoPesquisa);
  } else {
    exclusaoFisicaProduto(produtoPesquisa, fileName);
  }

}

void pesquisaProdutoCodigo(char* codBarras) {
  Produto p;
  rewind(fp);
  while (fread(&p, sizeof(Produto), 1, fp) != 0) {
    if (p.excluido != true && strcmp(codBarras, p.codigo_barras) == 0) {
      exibeProduto(p);
    }
  }

  mensagemPausa("\n\n Pressione <Enter> para continuar .  .  .");
}

void pesquisaProdutoPreco(double preco) {
  Produto p;
  rewind(fp);

  while (fread(&p, sizeof(Produto), 1, fp)) {
    if (p.excluido != true && p.preco == preco) {
      exibeProduto(p);
    }
  }

  mensagemPausa("\n\n Pressione <Enter> para continuar .  .  .");
}

void pesquisaProduto() {
  int op = 0;
  printf("Pelo que deseja pesquisar?\n1 - Codigo de Barras\n2 - Preco\n");
  scanf("%d", &op);fflush(stdin);

  if (op != 1 && op != 2) {
    return;
  } else if (op == 1) {
    char codBarras[50];
    printf("Qual o codigo de barras do produto a procurar: ");
    gets(codBarras); fflush(stdin);

    pesquisaProdutoCodigo(codBarras);
  } else if (op == 2) {
    double preco;
    printf("Qual o preco do produto a procurar: ");
    scanf("%lf", &preco); fflush(stdin);
    pesquisaProdutoPreco(preco);
  }
}
