# Введение
***
Цель: Освоить работу в среде Gitlab. Написать три программы на языке программирования C. Составить отчёт, используя язык разметки Markdown.

## Задание

1. Написать программу, печатающую в stdout фразу "Hello, world!" на отдельной строке.
1. Написать программу, принимающую на вход два числа, разделённые пробелом, и суммирующую их. Ввод чисел производить из stdin, вывод результата - в stdout. Вводимые числа не превосходят по модулю 2147483647.
1. Написать программу, принимающую на вход числа x и y, разделённые пробелом, и вычисляющую x в степени y. Ввод чисел производить из stdin, вывод результата - в stdout. Вводимые числа не превосходят по модулю 2147483647. Реализовывать возведение в степень через цикл/рекурсию не допускается.
***

# Ход работы

В ходе выполнения практической работы была установлена ОС Linux. После установки Linux, в терминале прописываем команды, для установки нужного ПО:

```
sudo apt-get update
sudo apt-get install git splint build-essential -y
```

После написания программы, выполняется проверка программы через spiint, где программа проверяется на ошибки и частоту написания кода.

Загружаем программы на gitlab и убеждаемся, что pipeline проходит успешно

[![](https://gitlab.com/ItsLupus/practices/-/raw/master/pr1/image/pr1.png)](https://gitlab.com/ItsLupus/practices/-/blob/master/pr1/image/pr1.png)

Пишем отчет по работе в разметке Markdown.

## Код 01_hello.c

```
#include <stdio.h>

int main()
{
    printf ("Hello, World!\n");

    return 0;
}

```

## Код 02_sum.c

```
#include <stdio.h>

int main(){
    double a, b, sum;
    if(scanf("%lf %lf", &a, &b) == 2){
        sum = a + b;
        printf("%lf\n", sum);
    }
    
    return 0;
}

```
## Код 03_pow.c

```
#include <stdio.h>
#include <math.h>

int main(){
    double x, y, power;
    if(scanf("%lf %lf", &x, &y) == 2){
        power = pow(x, y);
        printf("%lf\n", power);
    }

    return 0;
}

```

На рисунке представлен скриншот успешного прохождения pipeline

[![](https://gitlab.com/Korobejnikova/practices/-/raw/master/pr1/pr1.png)](http://https://gitlab.com/Korobejnikova/practices/-/blob/master/pr1/pr1.png)

***

# Вывод

В ходе выполения практической работы был освоен ресурс Gitlab, написаны 3 программы на языке C, которые прошли pipeline. Освоен язык разметки Markdown
***
