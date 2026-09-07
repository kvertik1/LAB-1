#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");
    printf("Создание массива произвольного размера\n\n");

    int n, i;
    int* arr;

    printf("Введите размер массива: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Ошибка: размер должен быть больше 0!\n");
        return 1;
    }

    arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }

    srand((unsigned int)time(NULL));

    for (i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    printf("Массив из %d элементов:\n", n);
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);

    return 0;
}