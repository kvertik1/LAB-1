#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct node {
    char inf[256];
    struct node* next;
};

struct node* top = NULL;

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

void push(void) {
    struct node* p = get_struct();
    if (p == NULL) return;
    p->next = top;
    top = p;
    printf("Элемент добавлен в стек\n");
}

void pop(void) {
    if (top == NULL) {
        printf("Стек пуст\n");
        return;
    }
    struct node* tmp = top;
    printf("Извлечён элемент: %s\n", tmp->inf);
    top = top->next;
    free(tmp);
}

void peek(void) {
    if (top == NULL) {
        printf("Стек пуст\n");
        return;
    }
    printf("Вершина стека: %s\n", top->inf);
}

void review(void) {
    struct node* struc = top;
    if (top == NULL) {
        printf("Стек пуст\n");
        return;
    }
    printf("\n--- Стек (LIFO), вершина сверху ---\n");
    while (struc) {
        printf("%s\n", struc->inf);
        struc = struc->next;
    }
    printf("-----------------------------------\n");
}

int main(void) {
    setlocale(LC_ALL, "Russian");
    int c;
    do {
        printf("\n=== Стек (LIFO) ===\n");
        printf("1 - push (положить на вершину)\n");
        printf("2 - pop (снять с вершины)\n");
        printf("3 - peek (посмотреть вершину)\n");
        printf("4 - просмотреть стек\n");
        printf("0 - выход\n");
        printf("Ваш выбор: ");
        (void)scanf("%d", &c);
        switch (c) {
        case 1: push(); break;
        case 2: pop(); break;
        case 3: peek(); break;
        case 4: review(); break;
        case 0: printf("Выход из программы.\n"); break;
        default: printf("Неверный выбор\n");
        }
    } while (c != 0);
    return 0;
}