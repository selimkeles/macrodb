// tablehandler.h
#ifndef TABLEHANDLER_H
#define TABLEHANDLER_H

#include "macrodb.h"
#include <stdbool.h>

// enumeration based on our table
#define DATA(name, type, def) name,
enum table_index_t {
#include "table.h"
    TABLE_MAX
};
#undef DATA

typedef enum table_index_t table_index_t;

// extern variables based on our table
#define DATA(name, type, def) extern type name;
#include "table.h"
#undef DATA

#endif // TABLEHANDLER_H