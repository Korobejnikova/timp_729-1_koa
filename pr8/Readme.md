# Введение

Цель работы - изучение базовых команд терминала ОС Linux, получение навыков работы с алгоритмами сортировки в языке программирования C.

## Задание

Необходимо реализовать программу на языке C, реализующую сортировки: Шелла и "Расческа".

1.  Программа принимает на вход количество элементов и на отдельной строке массив элементов;
2. Программа выводит в stdout отсортированный по возрастанию массив;
3. В файл shellSort.log записывается порядок преобразования массива с помощью алгоритма сортировки Шелла.
4. В combSort.log записывается порядок преобразования массива алгоритмом сортировки "Расческа".

## Ход работы

Для выполнения работы, были разработаны программы для реализации двух алгоритмов сортировки.

Код, реализующий сортировки Шелла и Расческа, представлен ниже

```c
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

```

### Таблица с входными и выходными данными

Таблица с результатами.

***
|input | output |
|-----------------:|:-------------------:|
|8 | |
|-74 70 -23 -68 -62 -53 41 44  | -74 -68 -62 -53 -23 41 44 70 |
***

## Заключение

Были получены навыки работы с алгоритмами сортировки в C.
Был составлен отчёт с помощью языка разметки Markdown.
