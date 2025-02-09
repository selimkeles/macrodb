#include "macrodbsafety.h"
#include "pal.h"
#include "macrodbmapper.h"


db_status mdb_check_db_size(void)
{
    size_t total_size = 0;
    size_t alignment_padding = 0;

    
    // Calculate size for each entry in the table including alignment requirements
    #define DATA(name, type, def) \
        alignment_padding = (sizeof(type) % sizeof(void*)) ? \
            (sizeof(void*) - (sizeof(type) % sizeof(void*))) : 0; \
        total_size += sizeof(type) + sizeof(char) + alignment_padding;
    #include "table.h"
    #undef DATA
    
    // Validate total size against available memory
    if (total_size > PAL_MEMORY_SIZE) {
        return DB_OUT_OF_MEMORY;
    }
    
    // Ensure minimum required size
    if (total_size < sizeof(char)) {
        return DB_NO_ENTRY_FOUND;
    }
    
    return DB_OK;
}

db_status mdb_check_db_boundaries(void)
{
    // Validate memory boundaries
    if (PAL_MEMORY_START >= PAL_MEMORY_END) {

        return DB_INVALID_ARGUMENT;
    }
    return DB_OK;
}

db_status mdb_check_entry_boundaries(table_index_t index)
{
    if (index < 0 || index >= TABLE_MAX) return DB_INVALID_ARGUMENT;
    return DB_OK;
}

db_status mdb_validate_magic(table_index_t index)
{
    size_t address = mdb_find_address(index);
    if (address == 0) return DB_ENTRY_NOT_FOUND; 

    if (PAL_MEMORY_START + address + MAGIC_NUMBER_SIZE > PAL_MEMORY_SIZE) return DB_OUT_OF_MEMORY;
    char magic_number;
    if (mdb_read_memory(address, MAGIC_NUMBER_SIZE, &magic_number) != DB_OK) return DB_READ_ERROR;
    
    if (magic_number != MAGIC_NUMBER) {
        return DB_MAGIC_NUMBER_MISMATCH;
    }
    return DB_OK;

}
