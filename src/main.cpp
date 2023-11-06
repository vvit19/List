#include <cstdio>
#include <cstdlib>

#include "list.h"
#include "dump.h"

#define FUNC_INFO {__PRETTY_FUNCTION__, __FILE__, __LINE__}

int main (int /*argc*/, const char** argv)
{
    List list = {};

    ListCtor (&list, MIN_CAPACITY);

    InsertHead (&list, 18);

    for (int i = 1; i < 6; i++)
    {
        InsertTail (&list, i);
    }

    ListDump (&list, argv[1], argv[2], FUNC_INFO);

    InsertAfter  (&list, 10, 3);
    ListDelete (&list, 2);
    InsertBefore (&list, 20, 4);

    ListDump (&list, argv[1], argv[2], FUNC_INFO);

    ListResize (&list, 14);

    ListDump (&list, argv[1], argv[2], FUNC_INFO);

    ListDtor (&list);
}
