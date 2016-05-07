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

int capacidade, n, valores[MAX], X[MAX], lucroSomando;
float pesos[MAX], lucro[MAX], lucroMaximoFracionario;
int escolhidos[MAX];

void input();
void outputInput();
void outputFraction();

/* Ordenar */
int partition(int inicio, int final);
int randomizedPartition(int inicio, int final);
void quickSort(int inicio, int fim);

int main(){
  
  input();

  quickSort(0, n-1);
  outputInput();
  
  //outputFraction();

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

  printf("Valor: %.1f\n", lucroMaximoFracionario);

  for(i = 0; i < n ; i++){
    if(item[i].porcao > 0)
      printf("i%d %1.f\n", item[i].chave, item[i].porcao);
  }
}
/*  Mochila Fracionaria*/
int RKnap(){
  int i = 0, j = 0, profit;
  float weight;

  for (j = 0; i < n; j++){
    X[j] = 0;  
  }
  while((weight < capacidade) && (i < n)){
    if (weight + pesos[i] <= capacidade){
      X[i] = 1;
      weight = weight + pesos[i];
      profit = profit + valores[i];
      i++;
    }else{
      X[i] = (capacidade - weight)/pesos[i];
      weight = capacidade;
      profit = profit + X[i]*valores[i];
      i++;
    }
  }
  return profit;
}

/*
void knapsack3(int l){

  if((l = n) && (lucroSomando > OptP)){
    OptP = lucroSomando;
    //OptX = ;
  }

  if (l = n){
    C[l] = 0;
  } else {
    if (CurW + pesos[l] < capacidade) {
      C[l] = 1;      
    } else {
      C[l] = 0;
    }
  }
  B = lucroSomando + RKnap();
  for(;;){
    if() return;
  }
}
*/

/*  Quick Sort para ordenar os lucros fracionarios*/
int partition(int inicio, int fim) {
    int direita, esquerda;
    float pivo;
    itemType *tmp;

    pivo = emOrdem[inicio]->lucro;
    direita = fim;
    esquerda = inicio;

    while (esquerda < direita) {
      while(emOrdem[esquerda]->lucro <= pivo && esquerda <= fim) { esquerda = esquerda + 1; }
      while(emOrdem[direita]->lucro > pivo && direita > inicio){ direita = direita - 1; }
      if (esquerda < direita){
        tmp = emOrdem[esquerda];
        emOrdem[esquerda] = emOrdem[direita];
        emOrdem[direita] = tmp;
      }
    }
    tmp = emOrdem[direita];
    emOrdem[direita] = emOrdem[inicio];
    emOrdem[inicio] = tmp;

    return direita;
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