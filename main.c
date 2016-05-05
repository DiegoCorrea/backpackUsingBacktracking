# include <stdio.h>
# define MAX 10000

int capacidade, n, valores[MAX], X[MAX], lucroSomando;
float pesos[MAX];
int escolhidos[MAX];

void input();
int knapsack3(int );
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