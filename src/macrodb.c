#include "macrodb.h"
#include "macrodbsafety.h"
#include "macrodbmapper.h"
#include "tablehandler.h"  // for table definitions


// initialize all variables with default values since they are extern
#define DATA(name, type, def) type name = def;
#include "table.h"
#undef DATA

db_status mdb_read(table_index_t index)
{
    db_status status = DB_OK;
    if (mdb_check_entry_boundaries(index) != DB_OK) return DB_INVALID_ARGUMENT;
    size_t address = mdb_find_address(index);
    if (address == 0) return DB_ENTRY_NOT_FOUND;
    size_t size = mdb_find_variable_size(index);
    if (size == 0) return DB_INVALID_ARGUMENT;
    
    #define DATA(name, type, def) \
        if (index == name) status = mdb_read_memory(address, size, &name); 
    #include "table.h"
    #undef DATA

    return status;
}

db_status mdb_write(table_index_t index, void *data)
{    
    db_status status = DB_OK;
    if (mdb_check_entry_boundaries(index) != DB_OK) return DB_INVALID_ARGUMENT;
    if (data == NULL) return DB_INVALID_ARGUMENT;
    size_t address = mdb_find_address(index);
    if (address == 0) return DB_ENTRY_NOT_FOUND;
    size_t size = mdb_find_variable_size(index);
    if (size == 0) return DB_INVALID_ARGUMENT;

    status = mdb_write_memory(address, size, data);     
    return status;

}

db_status mdb_init(void)
{
    db_status status;
    if ((status = mdb_check_db_boundaries()) != DB_OK) return status;
    if ((status = mdb_check_db_size()) != DB_OK) return status;
    if ((status = mdb_fetch_db()) != DB_OK) return status;
    return DB_OK;
}


db_status mdb_fetch_db(void)
{
    db_status status;
    for (table_index_t i = 0; i < TABLE_MAX; i++) {
        status = mdb_validate_magic(i);
        if (status != DB_OK && status != DB_MAGIC_NUMBER_MISMATCH) return status;
        if (status == DB_MAGIC_NUMBER_MISMATCH) 
        {
            #define DATA(name, type, def) \
                if (i == name) {        \
                    type val = def; \
                    status = mdb_write(i, &val); \
                    if (status != DB_OK) return status; \
                    status = mdb_read(i); \
                }
            #include "table.h"
            #undef DATA
        }
        else{
            status = mdb_read(i);
        }
    }

    return status;
}