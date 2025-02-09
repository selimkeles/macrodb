#ifndef XDBSAFETY_H
#define XDBSAFETY_H

#include "macrodb.h"
// For every entry in the table, there is a magic number
// which is used to check if the data is written previously
// if magic number is not found, in init default value will be used
#define MAGIC_NUMBER 0x35
#define MAGIC_NUMBER_SIZE sizeof(MAGIC_NUMBER)

db_status mdb_check_db_size(void);
db_status mdb_check_db_boundaries(void);
db_status mdb_check_entry_boundaries(table_index_t index);
db_status mdb_validate_magic(table_index_t index);

#endif