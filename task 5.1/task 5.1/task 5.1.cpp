#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

int main(void)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    int i, n;
    int found = 0;
    char search_famil[20];

    
    printf("Введите количество студентов: ");
    scanf_s("%d", &n);

    if (n <= 0)
    {
        printf("Ошибка: количество должно быть больше 0!\n");
        return 1;
    }

    
    struct student
    {
        char famil[20];
        char name[20];
        char facult[20];
        int Nomzach;
    };

   
    struct student* stud = (struct student*)malloc(n * sizeof(struct student));

    if (stud == NULL)
    {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }

    
    printf("\n--- Ввод данных о студентах ---\n");
    for (i = 0; i < n; i++)
    {
        printf("\nСтудент %d:\n", i + 1);

        printf("Введите фамилию: ");
        scanf_s("%19s", stud[i].famil, (unsigned)_countof(stud[i].famil));

        printf("Введите имя: ");
        scanf_s("%19s", stud[i].name, (unsigned)_countof(stud[i].name));

        printf("Введите факультет: ");
        scanf_s("%19s", stud[i].facult, (unsigned)_countof(stud[i].facult));

        printf("Введите номер зачётной книжки: ");
        scanf_s("%d", &stud[i].Nomzach);
    }

    
    printf("\n--- Список студентов ---\n");
    for (i = 0; i < n; i++)
    {
        printf("%d. %s %s, %s, зачетка: %d\n",
            i + 1, stud[i].famil, stud[i].name,
            stud[i].facult, stud[i].Nomzach);
    }

    
    printf("\nВведите фамилию для поиска (можно частично): ");
    scanf_s("%19s", search_famil, (unsigned)_countof(search_famil));

    printf("\n--- Результаты поиска ---\n");
    for (i = 0; i < n; i++)
    {
        
        
        if (strstr(stud[i].famil, search_famil) != NULL)
        {
            printf("\nСтудент найден!\n");
            printf("Фамилия: %s\n", stud[i].famil);
            printf("Имя: %s\n", stud[i].name);
            printf("Факультет: %s\n", stud[i].facult);
            printf("Номер зачётной книжки: %d\n", stud[i].Nomzach);
            found = 1;
        }
    }

    if (!found)
    {
        printf("Студент с фамилией, содержащей '%s', не найден.\n", search_famil);
    }

    
    free(stud);
    printf("\nПамять освобождена.\n");

    return 0;
}