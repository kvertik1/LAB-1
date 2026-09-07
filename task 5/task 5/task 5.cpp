#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

int main(void)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    int i;
    int searchNomzach;

    struct student
    {
        char famil[20];
        char name[20];
        char facult[20];
        int Nomzach;
    } stud[3];

    /* Ввод данных о студентах */
    for (i = 0; i < 3; i++)
    {
        printf("Введите фамилию студента:\n");
        scanf_s("%19s", stud[i].famil, (unsigned)_countof(stud[i].famil));

        printf("Введите имя студента:\n");
        scanf_s("%19s", stud[i].name, (unsigned)_countof(stud[i].name));

        printf("Введите факультет студента:\n");
        scanf_s("%19s", stud[i].facult, (unsigned)_countof(stud[i].facult));

        printf("Введите номер зачётной книжки:\n");
        scanf_s("%d", &stud[i].Nomzach);

        printf("\n");
    }

    /* Ввод номера для поиска */
    printf("Введите номер зачётной книжки для поиска: ");
    scanf_s("%d", &searchNomzach);

    /* Поиск студента */
    for (i = 0; i < 3; i++)
    {
        if (stud[i].Nomzach == searchNomzach)
        {
            printf("\nСтудент найден!\n");
            printf("Фамилия: %s\n", stud[i].famil);
            printf("Имя: %s\n", stud[i].name);
            printf("Факультет: %s\n", stud[i].facult);
            printf("Номер зачётной книжки: %d\n", stud[i].Nomzach);

            return 0;
        }
    }

    printf("\nСтудент с таким номером зачётной книжки не найден.\n");

    return 0;
}