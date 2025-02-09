#include "macrodbmapper.h"
#include "macrodb.h" // for DB_OK

uint32_t mdb_find_address(table_index_t index)
{
    uint32_t current_offset = 0;

// Calculate offset to the requested index
#define DATA(capital, name, type, def) \
    if (index == name)                 \
    {                                  \
        return current_offset;         \
    }                                  \
    current_offset += sizeof(type) + 1;
#include "table.h"
#undef DATA
    return 0; // Return 0 if not found
}

size_t mdb_find_variable_size(table_index_t index)
{
    size_t total_size = 0;

// Calculate size for entry including magic value
#define DATA(capital, name, type, def)      \
    if (index == name)                      \
    {                                       \
        return sizeof(type) + sizeof(char); \
    }
#include "table.h"
#undef DATA

    return total_size;
}
