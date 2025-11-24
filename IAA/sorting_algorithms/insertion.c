// CARACTERISTICAS:
// Desempenho: melhor caso O(n), Pior caso (n²);
// É estavel;
// in-place;

#include <stdio.h>

void insertionSort(int arr[], int n);

void printArray(int arr[], int n);

int main() {
    int arr[]= {5, 4, 2, 1, 6, 3};
    int arr_size = sizeof(arr) / sizeof(arr[0]);


    printf("Array original: ");
    printArray(arr, arr_size);

    insertionSort(arr, arr_size);

    printf("Array ordenado: ");
    printArray(arr, arr_size);

    return 0;
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}