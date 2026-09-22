#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct node {
    char inf[256];
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
    p->next = NULL;
    return p;
}

void enqueue(void) {
    struct node* p = get_struct();
    if (p == NULL) return;
    if (head == NULL) {
        head = p;
        last = p;
    }
    else {
        last->next = p;
        last = p;
    }
    printf("Элемент добавлен в очередь\n");
}

void dequeue(void) {
    if (head == NULL) {
        printf("Очередь пуста\n");
        return;
    }
    struct node* tmp = head;
    printf("Извлечён элемент: %s\n", tmp->inf);
    head = head->next;
    if (head == NULL) last = NULL;
    free(tmp);
}

void review(void) {
    struct node* struc = head;
    if (head == NULL) {
        printf("Очередь пуста\n");
        return;
    }
    printf("\n--- Очередь (FIFO), начало слева ---\n");
    while (struc) {
        printf("%s\n", struc->inf);
        struc = struc->next;
    }
    printf("------------------------------------\n");
}

int main(void) {
    setlocale(LC_ALL, "Russian");
    int c;
    do {
        printf("\n=== Очередь (FIFO) ===\n");
        printf("1 - enqueue (добавить в конец)\n");
        printf("2 - dequeue (извлечь из начала)\n");
        printf("3 - просмотреть очередь\n");
        printf("0 - выход\n");
        printf("Ваш выбор: ");
        (void)scanf("%d", &c);
        switch (c) {
        case 1: enqueue(); break;
        case 2: dequeue(); break;
        case 3: review(); break;
        case 0: printf("Выход из программы.\n"); break;
        default: printf("Неверный выбор\n");
        }
    } while (c != 0);
    return 0;
}