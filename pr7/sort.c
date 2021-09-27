#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quick(int* arr, int left, int right, int size){
    int i = left;
    int j = right;
    int privot = arr[right + (left - right) / 2];

    do
    {
        while (arr[i] < privot)
        {
            i++;
        }
        while (arr[j] > privot){
            j--;
        }
        if (i <= j)
        {
            if (arr[i] > arr[j])
            {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;

                printArray("quicksort.log", arr, size);
            }
            i++;
            if (j > 0){    
                j--;
            }
        }
    } while (i <= j);

    if (i < right){
        quick(arr, i, right, size);
    }
    if (j > left){
        quick(arr, left, j, size);
    }
}

void heapify(int arr[], int n, int i){
    int largest = i;
    int l = 2*i + 1; 
    int r = 2*i + 2; 

    if (l < n && arr[l] > arr[largest]){
        largest = l;
    }
    if (r < n && arr[r] > arr[largest]){
        largest = r;
    }
    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        printArray("heapsort.log", arr, n);
        heapify(arr, n, largest);
    }
}

void heap(int* arr, int n){ 
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        printArray("heapsort.log", arr, n);
        heapify(arr, i, 0);
    }
}

int printArray(const char* fileName, int* arr, int size){ 
    FILE *file;
    file = fopen(fileName, "a+"); 
    if(file){
        for(int i = 0; i < size; i++){
            fprintf(file, "%d ", arr[i]);
        }
        fprintf(file, "\n");
    }
    else{
        printf("Не удалось открыть файл!\n");
    }
    fprintf(file, "\n");
    fclose(file); 

    return 0;
}

int main(void) {
    int size; 
    scanf("%d", &size); 

    int* arrForQuickSort = (int*)malloc(sizeof(int) * size);
    int* arrForHeapSort = (int*)malloc(sizeof(int) * size);

    int value;
    for(int i = 0; i < size; i++){
        scanf("%d", &value);
        arrForQuickSort[i] = value;
        arrForHeapSort[i] = value;
    }

    quick(arrForQuickSort, 0, size - 1, size);
    heap(arrForHeapSort, size);

    for(int i = 0; i < size; i++){
        printf("%d ", arrForHeapSort[i]);
    }
    printf("\n");

    return 0;
}
