// CARACTERISTICAS:
// Desempenho: melhor caso O(n), Pior caso (n²);
// É estavel;
// in-place;

#include <stdio.h>

void heapSort(int arr[], int n);

void heapify(int arr[], int n, int i);

void printArray(int arr[], int n);

int main() {
    int arr[]= {5, 4, 2, 1, 6, 3};
    int arr_size = sizeof(arr) / sizeof(arr[0]);


    printf("Array original: ");
    printArray(arr, arr_size);

    heapSort(arr, arr_size);

    printf("Array ordenado: ");
    printArray(arr, arr_size);

    return 0;
}

void heapSort(int arr[], int n) {
    // costroi o heap
    for (int i = n/2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }


    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // arruma o heap novamente
        heapify(arr, i, 0);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[right])
        largest = left;

    if (right < n && arr[right] > arr[left])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
    
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}