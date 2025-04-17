// ! NEVER EVER USE THIS FILE DIRECTLY
// ! ALWAYS ADD NEW ENTRIES AT THE END
// ! DO NOT MODIFY OR REMOVE EXISTING ENTRIES
// ! BE SURE DEFAULT VALUES DO NOT EXCEEDS TYPE SIZE

// enum_name| variable_name| type| size| default_value
DATA(DATA_INT, data_int, int, sizeof(int), 15)
DATA(DATA_FLOAT, data_float, float, sizeof(float), 10.5)
DATA(DATA_DOUBLE, data_double, double, sizeof(double), 20.6)
DATA(DATA_CHAR, data_char, char, sizeof(char), 'S')
DATA(DATA_STRING, data_string, char*, sizeof(char)*10, "selim")
DATA(DATA_STRUCT, data_struct, my_dummy_struct_t, sizeof(my_dummy_struct_t), {1, 30, "selim"})