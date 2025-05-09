#ifndef MACRODB_H
#define MACRODB_H

#include <stddef.h>  // for size_t
#include "tablehandler.h"
#include "pal.h"

typedef enum
{
    DB_OK,
    DB_ENTRY_NOT_FOUND,
    DB_OUT_OF_MEMORY,
    DB_EXIST_NO_ENTRY,
    DB_INVALID_ARGUMENT,
    DB_INVALID_DATA_TYPE,
    DB_MAGIC_NUMBER_MISMATCH,
    DB_READ_ERROR,
    DB_WRITE_ERROR,
} db_status;

db_status mdb_init(void);
db_status mdb_read(table_index_t index);
db_status mdb_write(table_index_t index, void *data);
db_status mdb_fetch_db(void);
#endif