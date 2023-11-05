#include <cstdio>
#include <cstdlib>

#include "list.h"

int main()
{
    List list = {};

    ListCtor (&list, MIN_CAPACITY);

    InsertHead (&list, 18);

    for (int i = 1; i < 6; i++)
    {
        InsertTail (&list, i);
    }

    InsertAfter  (&list, 10, 3);
    ListDelete (&list, 2);
    InsertBefore (&list, 20, 4);

    FILE* file = fopen("graph.dot", "w");
    ListDump (&list, file);
    fclose(file);

    free (list.nodes);
}
