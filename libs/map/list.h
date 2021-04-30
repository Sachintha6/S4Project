#ifndef _LIST_H_
#define _LIST_H_

struct list
{
	struct list *next;
	int data;
};

// Gen
void list_init(struct list *list);
int list_is_empty(struct list *list);
int list_len(struct list *list);

// Elements
void list_push(struct list *list, int value);
int list_pop(struct list *list);
void list_insert(struct list *list, int value, int place);
int list_remove(struct list *list, int place);
int list_remove_val(struct list *list, int value);

// Finder
struct list *list_find(struct list *list, int value);
int list_contains(struct list *list, int value);

//Display
void print_list(struct list *list);

#endif
