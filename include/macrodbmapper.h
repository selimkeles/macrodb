#ifndef MACRODBMAPPER_H
#define MACRODBMAPPER_H
#include <stdint.h>
#include <stddef.h>  // for size_t
#include "macrodb.h"

uint32_t mdb_find_address(table_index_t index);
size_t mdb_find_variable_size(table_index_t index);
#endif

