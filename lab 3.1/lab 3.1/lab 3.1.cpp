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

void del(char* name) {
    struct node* struc = head;
    struct node* prev = NULL;   
    int flag = 0;

    if (head == NULL) {
        printf("Список пуст\n");
        return;
    }

    if (strcmp(name, struc->inf) == 0) {
        flag = 1;
        head = struc->next;
        free(struc);
        struc = head;
    }
    else {
        prev = struc;
        struc = struc->next;
    }

    while (struc) {
        if (strcmp(name, struc->inf) == 0) {
            flag = 1;
            if (struc->next) {
                prev->next = struc->next;
                free(struc);
                struc = prev->next;
            }
            else {
                prev->next = NULL;
                free(struc);
                last = prev;
                return;
            }
        }
        else {
            prev = struc;
            struc = struc->next;
        }
    }
    if (flag == 0)
        printf("Элемент не найден\n");
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
        printf("4 - удалить элемент\n");
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
        case 4:
            printf("Введите имя для удаления: ");
            (void)scanf("%s", name);
            del(name);
            break;
        case 0:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный выбор\n");
        }
    } while (c != 0);
    return 0;
}
//УДАЛЕНИЕ НАЧАЛЬНОГО ЭЛ НЕ ПО ИМЕНИ А ПО НАЧАЛЬНОМУ ЭЛ
//ЗАДАНИЕ разработать функцию которая меняет название эл то есть данные по их приоритету то есть если два эллемента имеют приоритет 10 то у них у обоих меняеться имя которое захочет пользователь