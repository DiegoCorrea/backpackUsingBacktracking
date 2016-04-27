# include <stdio.h>
# define MAX 10000

int capacidade, tamanho, valores[MAX];
float pesos[MAX];

void input();
void output();

int main(){
  
  input();

  output();

  return 0;
}

void input(){
  int i;

  scanf("%d", &tamanho);

  for(i = 0; i < tamanho; scanf("%d",&valores[i]), i++);

  for(i = 0; i < tamanho; scanf("%f",&pesos[i]), i++);

  scanf("%d", &capacidade);
}

void output(){
  int i;

  printf("Entrada\n");

  printf("Quantidade de itens: %d\n", tamanho);

  printf("Valores: ");
  for (i = 0; i < tamanho; i++) printf("%d ", valores[i]);
  printf("\n");

  printf("Pesos: ");
  for (i = 0; i < tamanho; i++) printf("%.2f ", pesos[i]);
  printf("\n");

  printf("Capacidade da mochila: %d\n", capacidade);
}