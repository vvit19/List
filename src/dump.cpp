#include <cstdio>
#include <cassert>

#include "../include/list.h"

#define $print(...) fprintf (file, __VA_ARGS__)

void ListDump (List* list, FILE* file)
{
    assert (list);
    assert (file);

    $print ("digraph G { rankdir = LR\n\n");

    $print ("InfoNode[shape=record, color=\"grey\", width=0.2, style=\"filled\","
            "label=\" {{Capacity: %d | Size: %d | Linear: %s}}\"] \n\n",
            list->capacity, list->size, (list->linear == true) ? "true" : "false");

    for (int i = 0; i < list->capacity; i++)
    {
        if (i == DUMMY_ELEM)
        {
            $print ("node%d[shape=record, width=0.2, style=\"filled\", fillcolor=\"Lime\","
                    "label=\" {{id: %d | value: %s | <n>next: %s | <p>prev: %s}}\"] \n \n",
                    i, i, "nill", "nill", "nill");
        }
        else if (list->nodes[i].prev == PREV_FOR_FREE)
        {
            $print ("node%d[shape=record, width=0.2, style=\"filled\", fillcolor=\"Turquoise\","
                    "label=\" {{id: %d | value: %s | <n>next: %d | <p>prev: %d}}\"] \n \n",
                    i, i, "POIZON", list->nodes[i].next, list->nodes[i].prev);
        }
        else
        {
            $print ("node%d[shape=record, width=0.2, style=\"filled\", fillcolor=\"yellow\","
                    "label=\" {{id: %d | value: %d | <n>next: %d | <p>prev: %d}}\"] \n \n",
                    i, i, list->nodes[i].value, list->nodes[i].next, list->nodes[i].prev);
        }
    }

    $print ("Free->node%d\n", list->free);
    $print ("Head->node%d\n", list->head);
    $print ("Tail->node%d\n\n", list->tail);

    $print ("edge[style=invis, constraint = true]\n");
    $print ("node0");
    for (int i = 1; i < list->capacity; i++)
    {
        $print (" -> node%d", i);
    }
    $print ("\n\n");

    $print ("edge[style=solid, constraint = false]\n");
    for (int i = 1; i < list->capacity; i++)
    {
        $print ("node%d:n -> node%d;\n", i, list->nodes[i].next);
    }

    $print ("\n}");

}
