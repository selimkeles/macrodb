# MacroDB

MacroDB is a lightweight, embedded database system designed for embedded systems and microcontrollers. It provides a simple interface for storing and retrieving data with built-in safety checks and memory management.

## Features

- Simple key-value storage interface
- Memory-safe operations with boundary checks
- Magic number validation for data integrity
- Platform abstraction layer for portability
- Configurable memory size and address space
- Type-safe data storage and retrieval

## Requirements

- CMake 3.14 or higher
- C compiler with C11 support
- Git (for cloning submodules)

## Building

1. Clone the repository with submodules:
```bash
git clone --recursive https://github.com/yourusername/macrodb.git
cd macrodb
```

2. Create a build directory and run CMake:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

3. Run tests:
```bash
ctest --output-on-failure
```

## Usage

```c
#include "macrodb.h"

int main() {
    // Initialize the database
    db_status status = mdb_init();
    if (status != DB_OK) {
        // Handle error
        return -1;
    }

    // Read a value
    my_dummy_struct data;
    status = mdb_read(MY_DUMMY_STRUCT, &data);
    
    // Write a value
    my_dummy_struct new_data = {
        .id = 1,
        .age = 25,
        .name = "John Doe"
    };
    status = mdb_write(MY_DUMMY_STRUCT, &new_data);
}
```

## Configuration

The database can be configured by modifying the following parameters in `include/platform/pal.h`:

- `PAL_MEMORY_SIZE`: Total size of the memory space
- `PAL_MEMORY_START`: Starting address of the memory space

## TODO

### Upcoming Features
1- Advanced Struct Support
   - Nested struct storage
   - Array of structs support
   - Dynamic struct field allocation
   - Struct versioning for backward compatibility
   - Automatic struct serialization/deserialization

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct and the process for submitting pull requests.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Authors

- Selim Keles - Initial work

## Acknowledgments

- Unity Test Framework for testing support
