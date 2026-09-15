#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

double multiply_matrices(int N)
{
    size_t size = (size_t)N * (size_t)N;

    int* a = (int*)malloc(size * sizeof(int));
    int* b = (int*)malloc(size * sizeof(int));
    int* c = (int*)malloc(size * sizeof(int));

    if (!a || !b || !c) {
        printf("ОШИБКА ПАМЯТИ при N = %d\n", N);
        free(a); free(b); free(c);
        return -1.0;
    }

    srand((unsigned)time(NULL));
    for (size_t k = 0; k < size; ++k) {
        a[k] = rand() % 100 + 1;
        b[k] = rand() % 100 + 1;
    }

    clock_t start = clock();

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int elem_c = 0;
            for (int r = 0; r < N; ++r) {
                elem_c += a[i * N + r] * b[r * N + j];
            }
            c[i * N + j] = elem_c;
        }
    }

    clock_t end = clock();

    free(a); free(b); free(c);

    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main(void)
{
    /* --- Русификатор --- */
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int sizes[] = { 100, 200, 400, 1000, 2000, 4000, 10000 };
    int n = (int)(sizeof(sizes) / sizeof(sizes[0]));
    double results[7];

    printf("=== ЗАДАНИЕ 1: Измерение времени перемножения матриц ===\n\n");

    for (int k = 0; k < n; ++k) {
        printf("Идет расчет для N = %d (пожалуйста, подождите)...\n", sizes[k]);
        fflush(stdout);
        results[k] = multiply_matrices(sizes[k]);
    }

    printf("\nИТОГОВАЯ ТАБЛИЦА РЕЗУЛЬТАТОВ:\n");
    printf("+---------------------+----------------------+\n");
    printf("|   Размер матрицы    |   Время счета (сек)  |\n");
    printf("+---------------------+----------------------+\n");
    for (int k = 0; k < n; ++k) {
        if (results[k] < 0.0) {
            printf("| %10d x %-10d |   ОШИБКА ПАМЯТИ      |\n",
                sizes[k], sizes[k]);
        }
        else {
            printf("| %10d x %-10d | %20.2f |\n",
                sizes[k], sizes[k], results[k]);
        }
    }
    printf("+---------------------+----------------------+\n");

    printf("\nНажмите Enter для выхода...");
    getchar();
    return 0;
}