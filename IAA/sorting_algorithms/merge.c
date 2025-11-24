// CARACTERISTICAS:
// Desempenho: sempre O(n * log n);
// É estavel;
// Não é in-place, gasta memória O(n);
// Equação de recorrência: T(n) = 2T(n/2) + n; 

#include <stdio.h>

void mergeSort(int arr[], int left, int right);

void merge(int arr[], int left, int middle, int right);

void printArray(int arr[], int n);

int main() {
    int arr[]= {5, 4, 2, 1, 6, 3};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Array original: ");
    printArray(arr, arr_size);

    mergeSort(arr, 0, arr_size - 1);

    printf("Array ordenado: ");
    printArray(arr, arr_size);

    return 0;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int m = left + (right - left)/2;

        mergeSort(arr, left, m);
        mergeSort(arr, m + 1, right);

        merge(arr, left, m, right);
    } 
}

// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) 
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) 
        R[j] = arr[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}