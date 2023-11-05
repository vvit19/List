#ifndef LIST_H
#define LIST_H

const int MIN_CAPACITY = 10;

typedef int elem_t;

enum ListErrors
{
    NO_ERROR = 0,
    LIST_IS_FULL = 1,
    POS_BIGGER_THAN_CAPACITY = 2,
};

struct Node
{
    elem_t  value;
    int     prev;
    int     next;
};

struct List
{
    Node*  nodes;
    int    capacity;

    int    free;
    int    head;
    int    tail;
};

void        ListCtor     (List* list, int capacity);
ListErrors  InsertHead   (List* list, elem_t value);
ListErrors  InsertTail   (List* list, elem_t value);
ListErrors  InsertAfter  (List* list, elem_t value, int position);
ListErrors  InsertBefore (List* list, elem_t value, int position);
ListErrors  ListDelete   (List* list, int position);
void        ListDtor     (List* list);

#endif // LIST_H
