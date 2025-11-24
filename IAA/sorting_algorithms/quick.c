// CARACTERISTICAS:
// Desempenho: melhor caso O(n), Pior caso (n²);
// É estavel;
// in-place;

#include <stdio.h>

void quickSort(int arr[], int low, int high);

int partition(int arr[], int low, int high);

void swap(int *a, int *b); 

void printArray(int arr[], int n);

int main() {
    int arr[]= {5, 4, 2, 1, 6, 3};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Array original: ");
    printArray(arr, arr_size);

    quickSort(arr, 0, arr_size);

    printf("Array ordenado: ");
    printArray(arr, arr_size);

    return 0;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivo = partition(arr, low, high);

        quickSort(arr, low, pivo - 1);
        quickSort(arr, pivo + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    // Pega o pivo como o ultimo numero do array.
    int pivot = arr[high];

    //
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    // Coloca o pivo para sua posição ordenada.
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}