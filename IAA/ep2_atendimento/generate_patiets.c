#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CORES 5
#define NUM_CATEGORIAS 6

const char *cores[] = {"Vermelho", "Laranja", "Amarelo", "Verde", "Azul"};
const char *categorias[] = {"PCD", "Gravida", "Idoso", "Pessoa Obesa", "Recem Nascido", "N/A"};

int randomN(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main(int argc, char * argv[]) {
  if (argc < 2) {
    printf("Insira o número de pacientes!");
  }

  srand(time(NULL));

  freopen("pacientes.csv", "w", stdout);
  int patients = atoi(argv[1]);

  for (int i = 0; i < patients; i++) {
    int cor = randomN(0, NUM_CORES - 1);
    printf("%s,%s,%d", 
      cores[cor], 
      categorias[randomN(0, NUM_CATEGORIAS - 1)], 
      randomN(3, (cor * 60)*(cor > 1) + 20)
    );

    if (i != patients - 1)
      printf("\n");
  }

  return 0;
}