#include <stdlib.h>
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
    struct list *new;
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
    // Default: logical place in sorted list
    if (place < 0){
        while (list->next != NULL && list->next->data < value)
        {
            list = list->next;
        }
    }
    // determined place !!(not tested)!!
    else
    {
        int cpt = 0;
        while (list->next != NULL && cpt < place)
        {
            list = list->next;
            cpt++;
        }
    }

    struct list *elm;
    elm->data = value;
    elm->next = list->next;
    list->next = elm;
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
