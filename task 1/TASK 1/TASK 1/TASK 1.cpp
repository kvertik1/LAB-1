#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");

    printf("Разница между максимальным и минимальным элементами\n\n");

    int arr[] = { 15, 7, 22, 3, 9, 14, 6, 31, 8, 12 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int max = arr[0], min = arr[0];
    int i;

    for (i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
        if (arr[i] < min)
            min = arr[i];
    }

    printf("Массив: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\nМаксимальный элемент: %d\n", max);
    printf("Минимальный элемент: %d\n", min);
    printf("Разница (max - min): %d\n", max - min);

    return 0;
}