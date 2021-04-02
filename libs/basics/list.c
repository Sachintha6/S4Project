#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void list_init(struct list *list)
{
    list->next = NULL;
}

int list_is_empty(struct list *list)
{
    if (list->next == NULL)
    {
        return 1;
    }
    return 0;
}

int list_len(struct list *list)
{
    unsigned int cpt = 0;

    while (list->next != NULL)
    {
        list = list->next;
        cpt++;
    }

    return cpt;
}

void list_push(struct list *list, int value)
{
    struct list *new = (struct list*)malloc(sizeof(struct list));
    new->data = value;
    new->next = list->next;
    list->next = new;
}

int list_pop(struct list *list)
{
    if (list_is_empty(list) == 1)
    {
        return -1;
    }
    else
    {
        struct list *first = list->next;
        list->next = first->next;

        return first->data;
    }
}

void list_insert(struct list *list, int value, int place)
{
    int cpt = 0;
    while (list->next != NULL && cpt < place)
    {
        list = list->next;
        cpt++;
    }

    struct list *elm = (struct list*)malloc(sizeof(struct list));
    elm->data = value;
    elm->next = list->next;
    list->next = elm;
}

int list_remove(struct list *list, int place)
{
    if (list_is_empty(list) == 1)
    {
        return -1;
    }

    int cpt = 0;
    while (list->next->next != NULL && cpt < place)
    {
        list = list->next;
        cpt++;
    }

    int val= list->next->data;
    list->next = list->next->next;

    return val;
}

int list_remove_val(struct list *list, int value)
{
    if (list_is_empty(list) == 1)
    {
        return -1;
    }

    while (list->next->next != NULL && list->next->data != value)
    {
        list = list->next;
    }

    if (list->next->next == NULL && list->next->data != value)
    {
        return -1;
    }

    int val= list->next->data;
    list->next = list->next->next;

    return val;
}

struct list *list_find(struct list *list, int value)
{
    while (list->next != NULL)
    {
        if (list->next->data == value)
        {
            return list->next;
        }
        else
        {
            list = list->next;
        }
    }

    return NULL;
}

int list_contains(struct list *list, int value)
{
    struct list *el = list_find(list, value);

    if (el != NULL)
        return 1;
    return 0;
}

void print_list(struct list *list)
{
    if (list_is_empty(list) == 1){
        printf(" empty\n");
        return;
    }

    while (list->next != NULL)
    {
        printf("%2d ", list->next->data);
        list = list->next;
    }
    printf("\n");
}
