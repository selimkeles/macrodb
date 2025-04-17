#include "unity.h"
#include "platform/pal.h"
#include "macrodb.h"
#include "macrodbtypes.h"
#include "tablehandler.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

// Helper function to print db_status
const char* get_status_string(db_status status) {
    switch(status) {
        case DB_OK: return "DB_OK";
        case DB_ENTRY_NOT_FOUND: return "DB_ENTRY_NOT_FOUND";
        case DB_OUT_OF_MEMORY: return "DB_OUT_OF_MEMORY";
        case DB_EXIST_NO_ENTRY: return "DB_EXIST_NO_ENTRY";
        case DB_INVALID_ARGUMENT: return "DB_INVALID_ARGUMENT";
        case DB_INVALID_DATA_TYPE: return "DB_INVALID_DATA_TYPE";
        case DB_MAGIC_NUMBER_MISMATCH: return "DB_MAGIC_NUMBER_MISMATCH";
        case DB_READ_ERROR: return "DB_READ_ERROR";
        case DB_WRITE_ERROR: return "DB_WRITE_ERROR";
        default: return "UNKNOWN_STATUS";
    }
}

void setUp(void)
{
    // Setup function called before every test
    printf("\n--- Starting new test ---\n");
    db_status init_status = mdb_init();
    printf("Database initialization status: %s\n", get_status_string(init_status));
}

void tearDown(void)
{
    // Teardown function called after every test
    extern void cleanup_memory_file(void);
    cleanup_memory_file();
    printf("--- Test completed ---\n");
}

// Low-level memory tests
void test_write_read_byte(void)
{
    uint8_t write_value = 0x42;
    uint8_t read_value = 0;

    // Test writing a byte
    TEST_ASSERT_EQUAL_INT(0, mdb_write_memory(PAL_MEMORY_START, sizeof(uint8_t), &write_value));

    // Test reading the same byte
    TEST_ASSERT_EQUAL_INT(0, mdb_read_memory(PAL_MEMORY_START, sizeof(uint8_t), &read_value));
    TEST_ASSERT_EQUAL_UINT8(write_value, read_value);
}

void test_write_read_word(void)
{
    uint16_t write_value = 0xABCD;
    uint16_t read_value = 0;

    TEST_ASSERT_EQUAL_INT(0, mdb_write_memory(PAL_MEMORY_START, sizeof(uint16_t), &write_value));
    TEST_ASSERT_EQUAL_INT(0, mdb_read_memory(PAL_MEMORY_START, sizeof(uint16_t), &read_value));
    TEST_ASSERT_EQUAL_UINT16(write_value, read_value);
}

void test_write_read_dword(void)
{
    uint32_t write_value = 0x12345678;
    uint32_t read_value = 0;

    TEST_ASSERT_EQUAL_INT(0, mdb_write_memory(PAL_MEMORY_START, sizeof(uint32_t), &write_value));
    TEST_ASSERT_EQUAL_INT(0, mdb_read_memory(PAL_MEMORY_START, sizeof(uint32_t), &read_value));
    TEST_ASSERT_EQUAL_UINT32(write_value, read_value);
}

void test_invalid_address(void)
{
    uint8_t value = 0;

    // Test below memory range
    TEST_ASSERT_EQUAL_INT(-1, mdb_read_memory(PAL_MEMORY_START - 1, 1, &value));
    TEST_ASSERT_EQUAL_INT(-1, mdb_write_memory(PAL_MEMORY_START - 1, 1, &value));

    // Test above memory range
    TEST_ASSERT_EQUAL_INT(-1, mdb_read_memory(PAL_MEMORY_END + 1, 1, &value));
    TEST_ASSERT_EQUAL_INT(-1, mdb_write_memory(PAL_MEMORY_END + 1, 1, &value));
}

void test_null_pointer(void)
{
    TEST_ASSERT_EQUAL_INT(-1, mdb_read_memory(PAL_MEMORY_START, 1, NULL));
    TEST_ASSERT_EQUAL_INT(-1, mdb_write_memory(PAL_MEMORY_START, 1, NULL));
}

void test_sequential_writes(void)
{
    uint8_t write_data[4] = {0x11, 0x22, 0x33, 0x44};
    uint8_t read_data[4] = {0};

    // Write sequential bytes
    for (int i = 0; i < 4; i++)
    {
        TEST_ASSERT_EQUAL_INT(0, mdb_write_memory(PAL_MEMORY_START + i, 1, &write_data[i]));
    }

    // Read them back
    TEST_ASSERT_EQUAL_INT(0, mdb_read_memory(PAL_MEMORY_START, 4, read_data));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(write_data, read_data, 4);
}

// High-level database tests
void test_db_init(void)
{
    printf("\nTesting database initialization...\n");
    db_status status = mdb_init();
    printf("Init status: %s\n", get_status_string(status));
    TEST_ASSERT_EQUAL_INT(DB_OK, status);
    
    printf("Testing double initialization...\n");
    status = mdb_init();
    printf("Second init status: %s\n", get_status_string(status));
    TEST_ASSERT_EQUAL_INT(DB_OK, status);
}

void test_db_write_read_int(void)
{
    printf("\nTesting int write/read...\n");
    int test_value = 42;
    db_status status;
    
    // Write value
    printf("Writing int value: %d\n", test_value);
    status = mdb_write(DATA_INT, &test_value);
    printf("Write status: %s\n", get_status_string(status));
    TEST_ASSERT_EQUAL_INT(DB_OK, status);
    
    // Read value back
    printf("Reading int value...\n");
    status = mdb_read(DATA_INT);
    printf("Read status: %s\n", get_status_string(status));
    printf("Read value: %d\n", data_int);
    TEST_ASSERT_EQUAL_INT(DB_OK, status);
    TEST_ASSERT_EQUAL_INT(test_value, data_int);
}

void test_db_write_read_float(void)
{
    printf("\nTesting float write/read...\n");
    float test_value = 3.14159f;
    db_status status;
    
    // Write value
    printf("Writing float value: %f\n", test_value);
    status = mdb_write(DATA_FLOAT, &test_value);
    printf("Write status: %s\n", get_status_string(status));
    TEST_ASSERT_EQUAL_INT(DB_OK, status);
    
    // Read value back
    printf("Reading float value...\n");
    status = mdb_read(DATA_FLOAT);
    printf("Read status: %s\n", get_status_string(status));
    printf("Read value: %f\n", data_float);
    TEST_ASSERT_EQUAL_INT(DB_OK, status);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, test_value, data_float);
}

void test_db_write_read_string(void)
{
    printf("\nTesting string write/read...\n");
    char* test_value = "test";
    db_status status;
    
    // Write value
    printf("Writing string value: %s\n", test_value);
    status = mdb_write(DATA_STRING, &test_value);
    printf("Write status: %s\n", get_status_string(status));
    TEST_ASSERT_EQUAL_INT(DB_OK, status);
    
    // Read value back
    printf("Reading string value...\n");
    status = mdb_read(DATA_STRING);
    printf("Read status: %s\n", get_status_string(status));
    printf("Read value: %s\n", data_string);
    TEST_ASSERT_EQUAL_INT(DB_OK, status);
    TEST_ASSERT_EQUAL_STRING(test_value, data_string);
}

void test_db_write_read_struct(void)
{
    printf("\nTesting struct write/read...\n");
    my_dummy_struct_t test_value = {42, 99, "dummy"};
    db_status status;
    
    // Write value
    printf("Writing struct value: {%d, %d, %s}\n", test_value.id, test_value.age, test_value.name);
    status = mdb_write(DATA_STRUCT, &test_value);
    printf("Write status: %s\n", get_status_string(status));
    TEST_ASSERT_EQUAL_INT(DB_OK, status);
    
    // Read value back
    printf("Reading struct value...\n");
    status = mdb_read(DATA_STRUCT);
    printf("Read status: %s\n", get_status_string(status));
    printf("Read value: {%d, %d, %s}\n", data_struct.id, data_struct.age, data_struct.name);
    TEST_ASSERT_EQUAL_INT(DB_OK, status);
    TEST_ASSERT_EQUAL_INT(test_value.id, data_struct.id);
    TEST_ASSERT_EQUAL_INT(test_value.age, data_struct.age);
    TEST_ASSERT_EQUAL_STRING(test_value.name, data_struct.name);
}

void test_db_invalid_index(void)
{
    int test_value = 42;
    db_status status;
    
    // Test invalid index for write
    status = mdb_write(TABLE_MAX, &test_value);
    TEST_ASSERT_EQUAL_INT(DB_INVALID_ARGUMENT, status);
    
    // Test invalid index for read
    status = mdb_read(TABLE_MAX);
    TEST_ASSERT_EQUAL_INT(DB_INVALID_ARGUMENT, status);
}

void test_db_fetch(void)
{
    printf("\nTesting database fetch...\n");
    db_status status;
    
    // Write some test values
    int int_value = 42;
    float float_value = 3.14159f;
    char* string_value = "test";
    
    printf("Writing test values...\n");
    status = mdb_write(DATA_INT, &int_value);
    printf("Int write status: %s\n", get_status_string(status));
    TEST_ASSERT_EQUAL_INT(DB_OK, status);
    
    status = mdb_write(DATA_FLOAT, &float_value);
    printf("Float write status: %s\n", get_status_string(status));
    TEST_ASSERT_EQUAL_INT(DB_OK, status);
    
    status = mdb_write(DATA_STRING, &string_value);
    printf("String write status: %s\n", get_status_string(status));
    TEST_ASSERT_EQUAL_INT(DB_OK, status);
    
    // Clear the memory and fetch
    printf("Clearing memory and fetching...\n");
    cleanup_memory_file();
    status = mdb_fetch_db();
    printf("Fetch status: %s\n", get_status_string(status));
    TEST_ASSERT_EQUAL_INT(DB_OK, status);
    
    // Verify default values are restored
    printf("Verifying default values...\n");
    printf("data_int = %d (expected 15)\n", data_int);
    printf("data_float = %f (expected 10.5)\n", data_float);
    printf("string = %s (expected \"selim\")\n", data_string);
    
    TEST_ASSERT_EQUAL_INT(15, data_int);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 10.5f, data_float);
    TEST_ASSERT_EQUAL_STRING("selim", data_string);
}

int main(void)
{
    UNITY_BEGIN();

    // Run low-level memory tests
    RUN_TEST(test_write_read_byte);
    RUN_TEST(test_write_read_word);
    RUN_TEST(test_write_read_dword);
    RUN_TEST(test_invalid_address);
    RUN_TEST(test_null_pointer);
    RUN_TEST(test_sequential_writes);

    // Run high-level database tests
    RUN_TEST(test_db_init);
    RUN_TEST(test_db_write_read_int);
    RUN_TEST(test_db_write_read_float);
    RUN_TEST(test_db_write_read_string);
    RUN_TEST(test_db_write_read_struct);
    RUN_TEST(test_db_invalid_index);
    RUN_TEST(test_db_fetch);

    return UNITY_END();
}