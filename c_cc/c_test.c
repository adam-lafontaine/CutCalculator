#include<stdio.h>
#include <stdlib.h>
#include "str_builder.h"

void print(const char* msg) {
    printf("%s\n", msg);
}

char* array_to_string(int values[], int size) {

    str_builder_t *sb = str_builder_create();

    str_builder_add_str(sb, "[ ", 0);

    for(int i = 0; i < size - 1; ++i) {
        str_builder_add_int(sb, values[i]);
        str_builder_add_str(sb, ", ", 0);
    }

    str_builder_add_int(sb, values[size - 1]);

    str_builder_add_str(sb, " ]", 0);

    char* str = str_builder_dump(sb, NULL);
    str_builder_destroy(sb);
    return str;
}

// gcc -o run_tests c_test.c str_builder.c

int main(int argc, char **argv)
{
    int values[] = { 1, 2, 3, 4, 5 };
    print(array_to_string(values, 5));
}