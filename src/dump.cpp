#include <cstdio>
#include <cassert>
#include <cstdlib>

#include "list.h"
#include "dump.h"

const int MAX_COMMAND_LENGTH = 125;

#define $print(...) fprintf (file, __VA_ARGS__)

void ListDump (List* list, const char* dot_file, const char* log_file, function_info info)
{
    assert (list);
    assert (dot_file);
    assert (log_file);

    static int dump_number = 1;

    FILE* file = fopen (dot_file, "w");

    $print ("digraph G { rankdir = TB\n" "splines = ortho; edge[minlen = 3, penwidth = 3];\n\n");

    $print ("Info[shape=record, fillcolor=\"grey\", width=0.2, style=\"filled\","
            "label=\" {Capacity: %d | Size: %d | Linear: %s}\"] \n\n",
            list->capacity, list->size, (list->linear == true) ? "true" : "false");

    $print ("{rank = max; node0[shape=record, width=0.2, style=\"filled\", fillcolor=\"Lime\","
                    "label=\" {id: 0 | value: %s | next: %s | prev: %s}\"]} \n \n",
                    "nill", "nill", "nill");

    $print ("{rank = same;\n");

    for (int i = 1; i < list->capacity; i++)
    {
        if (list->nodes[i].prev == PREV_FOR_FREE)
        {
            $print ("node%d[shape=record, width=0.2, style=\"filled\", fillcolor=\"Turquoise\","
                    "label=\" {id: %d | value: %s | next: %d | prev: %d}\"] \n \n",
                    i, i, "POIZON", list->nodes[i].next, list->nodes[i].prev);
        }
        else
        {
            $print ("node%d[shape=record, width=0.2, style=\"filled\", fillcolor=\"yellow\","
                    "label=\" {id: %d | value: %d | next: %d | prev: %d}\"] \n \n",
                    i, i, list->nodes[i].value, list->nodes[i].next, list->nodes[i].prev);
        }
    }

    $print ("}\nFree->node%d\n", list->free);
    $print ("Head->node%d\n", list->head);
    $print ("Tail->node%d\n\n", list->tail);

    $print ("edge[style=invis, constraint = true]\n");
    $print ("node0");
    for (int i = 1; i < list->capacity; i++)
    {
        $print (" -> node%d", i);

        if (i == list->capacity - 1)
        {
            $print ("[style=invis, weight = 10000];");
        }
    }
    $print ("\n\n");

    $print ("edge[style=solid, constraint = false]\n");
    for (int i = 1; i < list->capacity; i++)
    {
        $print ("node%d -> node%d;\n", i, list->nodes[i].next);
    }

    $print ("\n}");

    fclose (file);

    char shell_command[MAX_COMMAND_LENGTH] = "";
    sprintf (shell_command, "dot -v -Tpng data/graph.dot -o data/graph%d.png", dump_number);
    system (shell_command);

    file = fopen (log_file, "a");

    $print ("<pre>\n<font size=5>\n"
            "Called from file: %s, function: %s, line: %d\n"
            "</font>\n</pre>\n", info.filename, info.function_name, info.line);
    $print ("<img width=\"1400px\" src=\"graph%d.png\"> \n\n"
            "---------------------------------------------------------------------"
            "--------------------------------------------------------------------------\n\n", dump_number);

    fclose (file);

    ++dump_number;
}
