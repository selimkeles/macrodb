#include "macrodbmapper.h"
#include "macrodb.h" // for DB_OK
#include "macrodbsafety.h" // for MAGIC_NUMBER_SIZE

uint32_t mdb_find_address(table_index_t index)
{
    uint32_t current_offset = 0;
    uint32_t alignment_padding = 0;

// Calculate offset to the requested index
#define DATA(capital, name, type, size, ...)                                                                 \
    if (index == capital)                                                                             \
    {                                                                                                 \
        /* Add magic number offset */                                                                 \
        return current_offset + MAGIC_NUMBER_SIZE;                                                    \
    }                                                                                                 \
    /* Calculate alignment padding */                                                                 \
    alignment_padding = (sizeof(type) % sizeof(void*)) ? (sizeof(void*) - (sizeof(type) % sizeof(void*))) : 0; \
    current_offset += sizeof(type) + MAGIC_NUMBER_SIZE + alignment_padding;
#include "table.h"
#undef DATA
    return 0; // Return 0 if not found
}

size_t mdb_find_variable_size(table_index_t index)
{
    size_t total_size = 0;

// Calculate size for entry including magic value
#define DATA(capital, name, type, size, ...)      \
    if (index == capital)                   \
    {                                       \
        return size;                \
    }
#include "table.h"
#undef DATA

    return total_size;
}
