#ifndef __FNCRUD_H_
#define __FNCRUD_H_

typedef struct {
  char codigo_barras[100];
  char nome[50];
  int quantidade;
  double preco;
  bool excluido;
}Produto;

void menuInicial();
void leProduto(Produto* p);
void inserirProduto(Produto p);
void incluiProduto();
void setupArquivo(char* nomeArq, FILE** file);
void listaProdutos();
void exibeProduto(Produto p);
void alteraProduto();
void excluiProduto();
void exclusaoFisicaProduto(char* nome, char* fileName);
void exclusaoLogicaProduto(char* nome);
void pesquisaProduto();
void pesquisaProdutoCodigo(char* codBarras);
void pesquisaProdutoPreco(double preco);

#endif