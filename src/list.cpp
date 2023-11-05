#include <cassert>
#include <cstdlib>
#include <cstdio>

#include "list.h"

const int DUMMY_ELEM    =  0;
const int PREV_FOR_FREE = -1;
const int POIZON        =  696969;

static ListErrors VerifyFullList (List* list);

void ListCtor (List* list, int capacity)
{
    assert (list);

    list->nodes = (Node*) calloc (capacity, sizeof (Node));
    assert (list->nodes);

    list->capacity = capacity;

    for (int i = 1; i < capacity - 1; i++)
    {
        list->nodes[i].next  = i + 1;
        list->nodes[i].prev  = PREV_FOR_FREE;
        list->nodes[i].value = POIZON;
    }

    list->nodes[DUMMY_ELEM].next = DUMMY_ELEM;
    list->nodes[DUMMY_ELEM].prev = DUMMY_ELEM;

    list->nodes[capacity - 1].next  = DUMMY_ELEM;
    list->nodes[capacity - 1].prev  = PREV_FOR_FREE;
    list->nodes[capacity - 1].value = POIZON;

    list->head = DUMMY_ELEM;
    list->tail = DUMMY_ELEM;
    list->free = 1;
}

ListErrors InsertHead (List* list, elem_t value)
{
    assert (list);

    if ((VerifyFullList (list)) == LIST_IS_FULL) return LIST_IS_FULL;

    int free_elem_id = list->free;
    list->free = list->nodes[list->free].next;

    list->nodes[list->head].prev = free_elem_id;

    list->nodes[free_elem_id].value = value;
    list->nodes[free_elem_id].next  = list->head;
    list->nodes[free_elem_id].prev  = DUMMY_ELEM;
    list->head = free_elem_id;

    if (list->tail == DUMMY_ELEM)
    {
        list->tail = free_elem_id;
    }

    return NO_ERROR;
}

ListErrors InsertTail (List* list, elem_t value)
{
    assert (list);

    if ((VerifyFullList (list)) == LIST_IS_FULL) return LIST_IS_FULL;

    int free_elem_id = list->free;
    list->free = list->nodes[list->free].next;

    list->nodes[list->tail].next = free_elem_id;

    list->nodes[free_elem_id].value = value;
    list->nodes[free_elem_id].prev  = list->tail;
    list->nodes[free_elem_id].next  = DUMMY_ELEM;
    list->tail = free_elem_id;

    if (list->head == DUMMY_ELEM)
    {
        list->head = free_elem_id;
    }

    return NO_ERROR;
}

ListErrors InsertAfter (List* list, elem_t value, int position)
{
    assert (list);

    if ((VerifyFullList (list)) == LIST_IS_FULL) return LIST_IS_FULL;

    if (position == list->tail) return InsertTail (list, value);

    if (position >= list->capacity)
    {
        printf ("Position is bigger than capacity!\n");
        return POS_BIGGER_THAN_CAPACITY;
    }

    int free_elem_id = list->free;
    list->free = list->nodes[list->free].next;

    int after_position_id = list->nodes[position].next;
    list->nodes[position].next = free_elem_id;
    list->nodes[after_position_id].prev = free_elem_id;

    list->nodes[free_elem_id].prev  = position;
    list->nodes[free_elem_id].next  = after_position_id;
    list->nodes[free_elem_id].value = value;

    return NO_ERROR;
}

ListErrors InsertBefore (List* list, elem_t value, int position)
{
    assert (list);

    if ((VerifyFullList (list)) == LIST_IS_FULL) return LIST_IS_FULL;

    if (position == list->head) return InsertHead (list, value);

    if (position > list->capacity)
    {
        printf ("Position is bigger than capacity!\n");

        return POS_BIGGER_THAN_CAPACITY;
    }

    return InsertAfter (list, value, list->nodes[position].prev);
}

ListErrors ListDelete (List* list, int position)
{
    assert (list);

    if (position >= list->capacity)
    {
        printf ("Position is bigger than capacity!\n");
        return POS_BIGGER_THAN_CAPACITY;
    }

    list->nodes[position].value = POIZON;

    if (position == list->head)
    {
        if (list->head == list->tail) // One element in list
        {
            list->tail = DUMMY_ELEM;
            list->head = DUMMY_ELEM;
        }
        else
        {
            list->head = list->nodes[list->head].next;
            list->nodes[list->head].prev = DUMMY_ELEM;
        }
    }
    else if (position == list->tail)
    {
        list->tail = list->nodes[list->tail].prev;
        list->nodes[list->tail].next = DUMMY_ELEM;
    }
    else
    {
        list->nodes[list->nodes[position].prev].next = list->nodes[position].next;
        list->nodes[list->nodes[position].next].prev = list->nodes[position].prev;
    }

    int free_elem_id = list->free;

    list->free = position;
    list->nodes[list->free].prev = -1;
    list->nodes[list->free].next = free_elem_id;

    return NO_ERROR;
}

static ListErrors VerifyFullList (List* list)
{
    assert (list);

    if (list->free == 0)
    {
        printf ("List is full!\n");
        return LIST_IS_FULL;
    }

    return NO_ERROR;
}
