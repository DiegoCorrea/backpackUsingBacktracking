# include <stdio.h>
# include <stdlib.h>
# define MAX 10000

typedef struct item{
  int chave;
  int valor;
  float peso;

  float lucro;

  int escolhido;
  float porcao;
}itemType;

itemType item[MAX], *emOrdem[MAX];

int capacidade, n, escolhaOtima[MAX];
float lucroMaximoFracionario = 0.0;
int lucroMaximoInteiro = 0, C[MAX];

/* Entrada e Saída */
void input();
void outputInput();
void outputFraction();
void outputInteger();

/* Ordenar */
int partition(int inicio, int final);
int randomizedPartition(int inicio, int final);
void quickSort(int inicio, int fim);

/* Algoritmo da mochila fracionaria */
float RKnap(int,int);
void knapsack3(int l, int pesoCorrente);

int main(){
  
  input();

  quickSort(0, n-1);
  outputInput();
  
  lucroMaximoFracionario = RKnap(0,capacidade);

  outputFraction();
  printf("\n");
  printf("Entrando no Knapsack\n");
  knapsack3(0, 0);
  printf("\n");
  outputInteger();

  return 0;
}

/*  Tratamento de entrada e saida */
void input(){
  int i;

  scanf("%d", &n);

  for(i = 0; i < n; scanf("%d",&item[i].valor), i++);

  for(i = 0; i < n; scanf("%f",&item[i].peso), i++);

  scanf("%d", &capacidade);

  for(i = 0; i < n; i++){
    item[i].lucro = item[i].valor/item[i].peso;
    item[i].chave = i+1;
    item[i].porcao = 0.0;
    item[i].escolhido = 0;
    emOrdem[i] = &item[i];
  }
}

void outputInput(){
  int i;

  printf("Entrada\n");

  printf("Quantidade de itens: %d\n", n);
  printf("Capacidade da mochila: %d\n", capacidade);
  for (i = 0; i < n; i++){
    printf("i%d -> valor:%d peso:%.1f lucro:%.1f\n", item[i].chave, item[i].valor, item[i].peso, item[i].lucro);
  }
  printf("\n");

  printf("Em Ordem de Lucro\n");
  for (i = 0; i < n; i++){
    printf("i%d %.1f\n", emOrdem[i]->chave, emOrdem[i]->lucro);
  }
  printf("\n");
}

void outputFraction(){
  int i;

  printf("Resultado francionario\n");

  printf("Valor: %.3f\n", lucroMaximoFracionario);

  for(i = 0; i < n ; i++){
    if(item[i].porcao > 0){
      printf("i%d Porcao:%.3f\n", item[i].chave, item[i].porcao);
    } else {
      printf("i%d Nenhuma porção foi pega\n", item[i].chave);
    }
  }
}
void outputInteger(){
  int i;

  printf("Resultado Inteiro\n");

  printf("Valor: %d\n", lucroMaximoInteiro);

  for(i = 0; i < n ; i++){
    if(item[i].escolhido != 0){
      printf("i%d Valor: %d Pego\n", item[i].chave, item[i].valor);
    } else {
      printf("i%d Não pego\n", item[i].chave);
    }
  }
}
/*  Mochila Fracionaria*/
float RKnap(int i, int capacidadeMomentanea){
  float pesoMomentaneo = 0.0, lucroMaximo = 0.0;

  for(;(pesoMomentaneo < capacidadeMomentanea) && (i < n); i++){
    if (pesoMomentaneo + emOrdem[i]->peso <= capacidadeMomentanea){
      emOrdem[i]->porcao = 1.0;
      pesoMomentaneo = pesoMomentaneo + emOrdem[i]->peso;
      lucroMaximo = lucroMaximo + emOrdem[i]->valor;
    }else{
      emOrdem[i]->porcao = (capacidadeMomentanea - pesoMomentaneo)/emOrdem[i]->peso;
      pesoMomentaneo = capacidadeMomentanea;
      lucroMaximo = lucroMaximo + ((emOrdem[i]->porcao)*(emOrdem[i]->valor));
    }
  }
  return lucroMaximo;
}


void knapsack3(int l, int pesoCorrente){
  int i, lucroSomandoAteN = 0, lucroSomandoAteL = 0;
  float limiteSuperior = 0.0;

  for(i = 0; i < n ; i++) { 
    lucroSomandoAteN = lucroSomandoAteN + item[i].valor*escolhaOtima[i];
    printf("lucroSomandoAteN: %d, ", lucroSomandoAteN);
  }
  printf("\n");

  if((l == n) && (lucroSomandoAteN > lucroMaximoInteiro)){
    lucroMaximoInteiro = lucroSomandoAteN;
    for(i = 0; i < n ; i++) { item[i].escolhido = escolhaOtima[i]; }
  }

  if (l == n){
    C[l] = 0;
    printf("Final, não pode continuar, retornando\n");
    return;
  } else {
    if (pesoCorrente + item[l].peso <= capacidade) {
      C[l] = 1;
    } else {
      C[l] = 0;
    }
  }

  for(i = 0; i < l; i++) { 
    lucroSomandoAteL = lucroSomandoAteL + item[i].valor*escolhaOtima[i];
  }
  limiteSuperior = lucroSomandoAteL + RKnap(l,capacidade - pesoCorrente);

  for(i = 0; i <= l; i++){
    if( limiteSuperior <= lucroMaximoInteiro) 
      return;
/*
    printf("L: %d C[l]: %d ", l, C[l]);

    printf("Limite Superior: %f Lucro Somando Até N: %d\n", limiteSuperior, lucroSomandoAteN);

    if( C[l] == 1 ){
      printf("Pegou ou não o item\n");
    } else {
      printf("NÃO PEGOU O ITEM\n");
    }
*/
    escolhaOtima[l] = C[l];
    knapsack3(l + 1, pesoCorrente + item[l].peso*C[l]);
    if( C[l] == 1 ){
      escolhaOtima[l] = 0;
      C[l] = 0;
      knapsack3(l + 1, pesoCorrente);
    }
  }
}


/*  Quick Sort para ordenar os lucros fracionarios*/
int partition(int inicio, int fim) {
    int direita, esquerda;
    float pivo;
    itemType *tmp;

    pivo = emOrdem[fim]->lucro;
    direita = fim;
    esquerda = inicio;

    while (esquerda < direita) {
      while(emOrdem[esquerda]->lucro > pivo && esquerda <= fim) { esquerda = esquerda + 1; }
      while(emOrdem[direita]->lucro <= pivo && direita > inicio){ direita = direita - 1; }
      if (esquerda < direita){
        tmp = emOrdem[esquerda];
        emOrdem[esquerda] = emOrdem[direita];
        emOrdem[direita] = tmp;
      }
    }
    tmp = emOrdem[esquerda];
    emOrdem[esquerda] = emOrdem[fim];
    emOrdem[fim] = tmp;

    return esquerda;
}
int randomizedPartition(int inicio, int final){
  int i = (rand() % final + inicio);
  itemType *tmp;

  tmp = emOrdem[i];
  emOrdem[i] = emOrdem[inicio];
  emOrdem[inicio] = tmp;
  return partition(inicio,final);
}
void quickSort(int inicio, int final){
  int pivo;
  if (inicio < final){
    pivo = randomizedPartition(inicio,final);
    quickSort(inicio,pivo - 1);
    quickSort(pivo + 1,final);
  }
}