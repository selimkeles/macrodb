// Add non standard types here (structs, enums, etc.)
// ! DO NOT MODIFY OR REMOVE EXISTING TYPES, ADD NEW TYPES INSTEAD
#ifndef MACRODBTYPES_H
#define MACRODBTYPES_H

#include <stdbool.h>

// String type definitions
typedef char string_10[10];  // Fixed-size string of 10 characters
typedef char string_20[20];  // Fixed-size string of 20 characters
typedef char string_50[50];  // Fixed-size string of 50 characters
typedef char string_100[100]; // Fixed-size string of 100 characters

typedef struct
{
    int id;
    int age;
    char name[20];
} my_dummy_struct;

#endif
