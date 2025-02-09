#include "unity.h"
#include "platform/pal.h"
#include <stdint.h>
#include <string.h>

void setUp(void)
{
    // Setup function called before every test
}

void tearDown(void)
{
    // Teardown function called after every test
    extern void cleanup_memory_file(void);
    cleanup_memory_file();
}

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

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_write_read_byte);
    RUN_TEST(test_write_read_word);
    RUN_TEST(test_write_read_dword);
    RUN_TEST(test_invalid_address);
    RUN_TEST(test_null_pointer);
    RUN_TEST(test_sequential_writes);

    return UNITY_END();
}