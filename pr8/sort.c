#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void comb(int* arr, int size){
    double reduction = 1.2473;
    int step = size - 1;
    int i = 0;

    while(step >= 1){
        for(i = 0; i + step < size; i++){
            if(arr[i] > arr[i + step]){
                int temp = arr[i];
                arr[i] = arr[i + step];
                arr[i + step] = temp;
                printArray("combSort.log", arr, size);
            }
        }
        step /= reduction;
    }
}

void shell(int* arr, int size){
    for (int s = size / 2; s > 0; s /= 2)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = i + s; j < size; j += s)
            {
                if (arr[i] > arr[j])
                {
                    int temp = arr[j];
                    arr[j] = arr[i];
                    arr[i] = temp;  
                    printArray("shellSort.log", arr, size);
                }
            }
        }
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

    int* arrForShellSort = (int*)malloc(sizeof(int) * size);
    int* arrForCombSort = (int*)malloc(sizeof(int) * size);

    int value;
    for(int i = 0; i < size; i++){
        scanf("%d", &value);
        arrForShellSort[i] = value;
        arrForCombSort[i] = value;
    }
    shell(arrForShellSort, size);
    comb(arrForCombSort, size);
    for(int i = 0; i < size; i++){
        printf("%d ", arrForCombSort[i]);
    }
    printf("\n");

    return 0;
}
