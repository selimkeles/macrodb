#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "pal.h"

static FILE *memory_file = NULL;
static const char *MEMORY_FILE_NAME = "memory.bin";

// Initialize the memory file
static void init_memory_file(void)
{
    if (memory_file == NULL)
    {
        memory_file = fopen(MEMORY_FILE_NAME, "wb+");
        if (memory_file == NULL)
        {
            fprintf(stderr, "Failed to create memory file\n");
            return;
        }

        // Initialize file with zeros up to PAL_MEMORY_SIZE
        uint8_t zero = 0;
        for (int i = 0; i < PAL_MEMORY_SIZE; i++)
        {
            fwrite(&zero, 1, 1, memory_file);
        }
        fflush(memory_file);
    }
}

// Clean up memory file
void cleanup_memory_file(void)
{
    if (memory_file != NULL)
    {
        fclose(memory_file);
        memory_file = NULL;
    }
}

// Implementation of memory read function
int _read_memory(uint32_t address, size_t size, void *value)
{
    if (memory_file == NULL)
    {
        init_memory_file();
    }

    if (address < PAL_MEMORY_START ||
        address + size > PAL_MEMORY_END ||
        value == NULL)
    {
        return -1;
    }

    uint32_t offset = address - PAL_MEMORY_START;
    fseek(memory_file, offset, SEEK_SET);
    size_t read_size = fread(value, 1, size, memory_file);

    return (read_size == size) ? 0 : -1;
}

// Implementation of memory write function
int _write_memory(uint32_t address, size_t size, const void *value)
{
    if (memory_file == NULL)
    {
        init_memory_file();
    }

    if (address < PAL_MEMORY_START ||
        address + size > PAL_MEMORY_END ||
        value == NULL)
    {
        return -1;
    }

    uint32_t offset = address - PAL_MEMORY_START;
    fseek(memory_file, offset, SEEK_SET);
    size_t write_size = fwrite(value, 1, size, memory_file);
    fflush(memory_file);

    return (write_size == size) ? 0 : -1;
}