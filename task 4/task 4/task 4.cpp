#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");
    printf("Сумма значений в каждом столбце двумерного массива\n\n");

    int rows = 3, cols = 4;
    int arr[3][4];
    int i, j;

    srand((unsigned int)time(NULL));

    printf("Исходный массив 3x4:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            arr[i][j] = rand() % 21;
            printf("%4d ", arr[i][j]);
        }
        printf("\n");
    }

    printf("\nСумма по столбцам:\n");
    for (j = 0; j < cols; j++) {
        int sum = 0;
        for (i = 0; i < rows; i++) {
            sum += arr[i][j];
        }
        printf("Столбец %d: %d\n", j + 1, sum);
    }

    printf("\nСумма по строкам:\n");
    for (i = 0; i < rows; i++) {
        int sum = 0;
        for (j = 0; j < cols; j++) {
            sum += arr[i][j];
        }
        printf("Строка %d: %d\n", i + 1, sum);
    }

    return 0;
}