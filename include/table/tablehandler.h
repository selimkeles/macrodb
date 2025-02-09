// tablehandler.h
#ifndef TABLEHANDLER_H
#define TABLEHANDLER_H

#include "macrodb.h"
#include <stdbool.h>
#include "macrodbtypes.h"

// enumeration based on our table
#define DATA(capital, name, type, def) capital,
typedef enum {
#include "table.h"
    TABLE_MAX
} table_index_t;
#undef DATA

// extern variables based on our table
#define DATA(capital, name, type, def) extern type name;
#include "table.h"
#undef DATA

#endif // TABLEHANDLER_H