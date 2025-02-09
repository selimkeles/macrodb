// PAL - Platform Abstraction Layer
#ifndef PAL_H
#define PAL_H

#define PAL_MEMORY_SIZE 1024    // Your memory size
#define PAL_MEMORY_START 0x2000  // Your memory start address
#define PAL_MEMORY_END PAL_MEMORY_START + PAL_MEMORY_SIZE

// Your memory read and write functions
#define mdb_read_memory(address, size, value) _read_memory(address, size, value)   //your memory read function
#define mdb_write_memory(address, size, value) _write_memory(address, size, value) //your memory write function

#endif
