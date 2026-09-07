#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");
    printf("Инициализация массива случайными числами\n\n");

    int arr[20];
    int n = 20;
    int i;

    srand((unsigned int)time(NULL));

    for (i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    printf("Массив случайных чисел (0-99):\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}