#include <stdbool.h>
#include <stdio.h>
#include <windows.h>

#include "../util/util.h"
#include "./arquivos.h"
#include "../functions/fncrud.h"

FILE* fp;

void menuInicialCrud(dateTime dataHora, char *nomeArquivo){
  inicializacao(dataHora);

  char titulo[] = "Gerenciamento de Produtos";
  criaCabecalho(titulo);

  

  // //Chamar depois que ja tiver alterado a variavel fileName
  // setupArquivo(nomeArquivo, &fp);

  // // Insere produto
  // incluiProduto();

  // // Lista produtos - TODOS
  // listaProdutos();

  // //Altera produto
  // alteraProduto();

  // // Exclui Produto
  // excluiProduto(fileName);
  // setupArquivo(fileName, &fp);//Tem que chamar essa funcao depois da exclusao

  // pesquisaProduto();
}