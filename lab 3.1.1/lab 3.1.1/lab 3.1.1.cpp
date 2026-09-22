#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct node {
    char inf[256];
    int prior;
    struct node* next;
};

struct node* head = NULL, * last = NULL;

struct node* get_struct(void) {
    struct node* p = NULL;
    char s[256];
    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL) {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }
    printf("Введите название объекта: \n");
    (void)scanf("%s", s);
    if (*s == 0) {
        printf("Запись не была произведена\n");
        free(p);
        return NULL;
    }
    strcpy(p->inf, s);
    printf("Введите приоритет: ");
    (void)scanf("%d", &p->prior);
    p->next = NULL;
    return p;
}

void spstore(void) {
    struct node* p = get_struct();
    if (p == NULL) return;

    if (head == NULL || p->prior > head->prior) {
        p->next = head;
        head = p;
        if (last == NULL) last = p;
        return;
    }

    struct node* cur = head;
    while (cur->next && cur->next->prior >= p->prior)
        cur = cur->next;

    p->next = cur->next;
    cur->next = p;
    if (p->next == NULL) last = p;
}

void review(void) {
    struct node* struc = head;
    if (head == NULL) {
        printf("Список пуст\n");
        return;
    }
    printf("\n--- Приоритетная очередь ---\n");
    while (struc) {
        printf("Имя - %s, приоритет - %d\n", struc->inf, struc->prior);
        struc = struc->next;
    }
    printf("---------------------------\n");
}

struct node* find(char* name) {
    struct node* struc = head;
    if (head == NULL) {
        printf("Список пуст\n");
        return NULL;
    }
    while (struc) {
        if (strcmp(name, struc->inf) == 0)
            return struc;
        struc = struc->next;
    }
    printf("Элемент не найден\n");
    return NULL;
}

// Удаление начального элемента списка (не по имени)
void del_first(void) {
    if (head == NULL) {
        printf("Список пуст\n");
        return;
    }
    struct node* tmp = head;
    printf("Удалён элемент: %s (приоритет %d)\n", tmp->inf, tmp->prior);
    head = head->next;
    if (head == NULL) last = NULL;
    free(tmp);
}

// Смена имени у ВСЕХ элементов с заданным приоритетом
void rename_by_prior(void) {
    if (head == NULL) {
        printf("Список пуст\n");
        return;
    }
    int pr;
    char new_name[256];
    int count = 0;

    printf("Введите приоритет, у которого нужно сменить имя: ");
    (void)scanf("%d", &pr);

    printf("Введите новое имя: ");
    (void)scanf("%s", new_name);

    struct node* struc = head;
    while (struc) {
        if (struc->prior == pr) {
            strcpy(struc->inf, new_name);
            count++;
        }
        struc = struc->next;
    }

    if (count == 0)
        printf("Элементов с приоритетом %d не найдено\n", pr);
    else
        printf("Имя изменено у %d элемент(ов)\n", count);
}

int main(void) {
    setlocale(LC_ALL, "Russian");
    int c;
    char name[256];
    do {
        printf("\n=== Приоритетная очередь ===\n");
        printf("1 - добавить элемент\n");
        printf("2 - просмотреть список\n");
        printf("3 - найти элемент\n");
        printf("4 - удалить начальный элемент\n");
        printf("5 - сменить имя у элементов с заданным приоритетом\n");
        printf("0 - выход\n");
        printf("Ваш выбор: ");
        (void)scanf("%d", &c);
        switch (c) {
        case 1: spstore(); break;
        case 2: review(); break;
        case 3:
            printf("Введите имя для поиска: ");
            (void)scanf("%s", name);
            find(name);
            break;
        case 4: del_first(); break;
        case 5: rename_by_prior(); break;
        case 0:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный выбор\n");
        }
    } while (c != 0);
    return 0;
}