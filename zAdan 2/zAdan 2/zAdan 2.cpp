#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

/* ---------- Счётчик глубины рекурсии ---------- */
static int depth = 0;

/* ---------- Сортировка Шелла ---------- */
void shell(int* items, int count)
{
    int i, j, gap, k;
    int x, a[5];
    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (j >= 0) && (x < items[j]); j -= gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

/* ---------- Быстрая сортировка с защитой от переполнения стека ---------- */
void qs_safe(int* items, int left, int right)
{
    int i, j;
    int x, y;

    depth++;
    if (depth > 2500) {   /* защита от бесконечной рекурсии */
        depth--;
        return;
    }

    i = left; j = right;
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs_safe(items, left, j);
    if (i < right) qs_safe(items, i, right);

    depth--;
}

void qs_wrap(int* items, int n)
{
    depth = 0;
    qs_safe(items, 0, n - 1);
}

/* ---------- Стандартная qsort ---------- */
int compare_ints(const void* a, const void* b)
{
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ia > ib) - (ia < ib);
}

void qsort_wrap(int* items, int n)
{
    qsort(items, (size_t)n, sizeof(int), compare_ints);
}

/* ---------- Заполнение массивов ---------- */
void fill_art(int* arr, int n, int type)
{
    int i;
    switch (type) {
    case 0:
        for (i = 0; i < n; ++i) arr[i] = rand() % 10000;
        break;
    case 1:
        for (i = 0; i < n; ++i) arr[i] = i;
        break;
    case 2:
        for (i = 0; i < n; ++i) arr[i] = n - i;
        break;
    case 3:
        for (i = 0; i < n / 2; ++i) arr[i] = i;
        for (i = n / 2; i < n; ++i) arr[i] = n - i;
        break;
    }
}

/* ---------- Измерение времени ---------- */
typedef void (*sort_fn)(int*, int);

double measure(sort_fn fn, int* src, int n)
{
    int* copy = (int*)malloc((size_t)n * sizeof(int));
    if (!copy) return -1.0;

    memcpy(copy, src, (size_t)n * sizeof(int));

    depth = 0;
    clock_t start = clock();
    fn(copy, n);
    clock_t end = clock();

    free(copy);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

/* ---------- main ---------- */
int main(void)
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int sizes[] = { 100, 1000, 10000 };
    int ns = (int)(sizeof(sizes) / sizeof(sizes[0]));
    const char* names[4] = { "Случайный", "Возраст.", "Убывающ.", "Пик" };

    srand((unsigned)time(NULL));

    printf("=== ЗАДАНИЕ 2: Сравнение времени сортировок ===\n");

    for (int s = 0; s < ns; ++s) {
        int n = sizes[s];
        int* orig_rand = (int*)malloc((size_t)n * sizeof(int));
        int* orig_asc = (int*)malloc((size_t)n * sizeof(int));
        int* orig_desc = (int*)malloc((size_t)n * sizeof(int));
        int* orig_peak = (int*)malloc((size_t)n * sizeof(int));

        if (!orig_rand || !orig_asc || !orig_desc || !orig_peak) {
            printf("ОШИБКА ПАМЯТИ при N = %d\n", n);
            free(orig_rand); free(orig_asc); free(orig_desc); free(orig_peak);
            getchar();
            return 1;
        }

        fill_art(orig_rand, n, 0);
        fill_art(orig_asc, n, 1);
        fill_art(orig_desc, n, 2);
        fill_art(orig_peak, n, 3);

        int* data[4] = { orig_rand, orig_asc, orig_desc, orig_peak };

        double t_shell[4], t_qs[4], t_qsort[4];

        for (int k = 0; k < 4; ++k) {
            t_shell[k] = measure(shell, data[k], n);
            t_qs[k] = measure(qs_wrap, data[k], n);
            t_qsort[k] = measure(qsort_wrap, data[k], n);
        }

        printf("\n---------------------- N = %d ----------------------\n", n);
        printf("+----------+------------+------------+------------+------------+\n");
        printf("| data/sort| %-10s | %-10s | %-10s | %-10s |\n",
            names[0], names[1], names[2], names[3]);
        printf("+----------+------------+------------+------------+------------+\n");

        printf("| Shell    | %10.4f | %10.4f | %10.4f | %10.4f |\n",
            t_shell[0], t_shell[1], t_shell[2], t_shell[3]);
        printf("| qs       | %10.4f | %10.4f | %10.4f | %10.4f |\n",
            t_qs[0], t_qs[1], t_qs[2], t_qs[3]);
        printf("| qsort    | %10.4f | %10.4f | %10.4f | %10.4f |\n",
            t_qsort[0], t_qsort[1], t_qsort[2], t_qsort[3]);

        printf("+----------+------------+------------+------------+------------+\n");
        fflush(stdout);

        free(orig_rand); free(orig_asc); free(orig_desc); free(orig_peak);
    }

    printf("\nНажмите Enter для выхода...");
    getchar();
    return 0;
}