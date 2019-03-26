#include<stdio.h>
#include <stdlib.h>
#include "str_builder.h"

void print(const char* msg) {
    printf("%s\n", msg);
}

char* array_int_to_string(int values[], int size) {

    str_builder_t *sb = str_builder_create();

    str_builder_append_str(sb, "[ ", 0);

    for(int i = 0; i < size - 1; ++i) {
        str_builder_append_int(sb, values[i]);
        str_builder_append_str(sb, ", ", 0);
    }

    str_builder_append_int(sb, values[size - 1]);

    str_builder_append_str(sb, " ]", 0);

    char* str = str_builder_dump(sb, NULL);
    str_builder_destroy(sb);
    return str;
}

char* array_double_to_string(double values[], int size) {
    str_builder_t *sb = str_builder_create();

    str_builder_append_str(sb, "[ ", 0);

    for(int i = 0; i < size - 1; ++i) {
        str_builder_append_double(sb, values[i]);
        str_builder_append_str(sb, ", ", 0);
    }

    str_builder_append_double(sb, values[size - 1]);

    str_builder_append_str(sb, " ]", 0);

    char* str = str_builder_dump(sb, NULL);
    str_builder_destroy(sb);
    return str;
}

// gcc -o run_tests c_test.c str_builder.c

int main(int argc, char **argv)
{
    int i_values[] = { 1, 2, 3, 4, 5 };
    print(array_int_to_string(i_values, 5));

    double d_values[] = { 1.6, 2.6, 3.6, 4.6, 5.6 };
    print(array_double_to_string(d_values, 5));
}