# include <stdio.h>
# define MAX 10000

int capacidade, n, valores[MAX], X[MAX];
float pesos[MAX];
int escolhidos[MAX];

void input();
void knapsack(int );
void output();

int main(){
  
  input();

  knapsack(0);

  output();

  return 0;
}

void input(){
  int i;

  scanf("%d", &n);

  for(i = 0; i < n; scanf("%d",&valores[i]), i++);

  for(i = 0; i < n; scanf("%f",&pesos[i]), i++);

  scanf("%d", &capacidade);
}

void output(){
  int i;

  printf("Entrada\n");

  printf("Quantidade de itens: %d\n", n);

  printf("Valores: ");
  for (i = 0; i < n; i++) printf("%d ", valores[i]);
  printf("\n");

  printf("Pesos: ");
  for (i = 0; i < n; i++) printf("%.2f ", pesos[i]);
  printf("\n");

  printf("Capacidade da mochila: %d\n", capacidade);
}

void knapsack(int l){

}

void RKnap(){
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
}