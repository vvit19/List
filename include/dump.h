#ifndef DUMP_H
#define DUMP_H

#include <cstdio>

#include "list.h"

struct function_info
{
    const char* function_name;
    const char* filename;
    int line;
};

void ListDump (List* list, const char* dot_file, const char* log_file, function_info info);

#endif
