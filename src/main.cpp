#include <cstdio>

#include "list.h"

int main()
{
    List list = {};

    ListCtor (&list, MIN_CAPACITY);

    InsertHead (&list, 18);

    for (int i = 3; i < 9; i++)
    {
        InsertTail (&list, i);
    }

    ListDelete (&list, 4);

    for (int i = 0; i < MIN_CAPACITY; i++)
    {
        printf("%d) Value = %d, Head = %d, Tail = %d, Free = %d\n",
                i, list.nodes[i].value, list.head, list.tail, list.free);
        printf("next = %d, prev = %d\n", list.nodes[i].next, list.nodes[i].prev);
    }
}
