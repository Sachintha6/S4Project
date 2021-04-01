#ifndef _LIST_H_
#define _LIST_H_

struct list
{
	struct list *next;
	int data;
};

void list_init(struct list *list);
int list_is_empty(struct list *list);
int list_len(struct list *list);

void list_push(struct list *list, int value);
int list_pop(struct list *list);

void list_insert(struct list *list, int value, int place);
struct list *list_find(struct list *list, int value);

#endif
