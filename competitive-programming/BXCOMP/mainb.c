#include <stdio.h>
#include <stdlib.h>


int fibo(int end) {
    int n1 = 0;
    int n2 = 1;
    int sum = 0;
    
    while(sum < end) {
        sum = n1 + n2;
        n1 = n2;
        n2 = sum;
    }
    
    if (sum == end) {
        return 1;
    }
    return 0;
}

char jogada(int num) {
    if (fibo(num)) {
        return 's';
    } else if (num%2 == 0) {
        return 'p';
    } else {
        return 't';
    }
}

int comparar(char pet, char rex) {
    if (pet == 's') {
        
        if (rex =='s') {
            return 0;
        } 
        else if (rex == 'p') {
            return -1;
        }
        else if (rex == 't') {
            return 1;
        }
        
    } else if (pet == 'p') {
        
        if (rex =='s') {
            return 1;
        } 
        else if (rex == 'p') {
            return 0;
        }
        else if (rex == 't') {
            return -1;
        }
        
    } else if (pet == 't') {
        
        if (rex =='s') {
            return -1;
        } 
        else if (rex == 'p') {
            return 1;
        }
        else if (rex == 't') {
            return 0;
        }
        
    }
}

int main()
{
    int casos;
    scanf("%d", &casos);
    
    int *result = (int*) malloc(casos * sizeof(int));
    
    for (int i = 0; i < casos; i++) {
        int pontos = 0;
        
        int rodadas;
        scanf("%d", &rodadas);
        
        for (int j = 0; j < rodadas; j++) {
            int pet, rex;
            scanf("%d %d", &pet, &rex);
            char jPet = jogada(pet);
            char jRex = jogada(rex);
            pontos += comparar(jPet, jRex);
        }
        result[i] = pontos;
    }
    
    for (int i = 0; i < casos; i++) {
            if (result[i] < 0) {
                printf("NOOO, ACHO QUE OS DINOSSAUROS VAO TER CORUJA AO FORNO HOJE NA JANTA\n");
            } else if (result[i] > 0) {
                printf("A CORUJA VOLTOU A PIAAAAAR!!!!!!\n");
            } else {
                printf("Precisamos marcar uma revanche...\n");
            }
    }
    return 0;
}


