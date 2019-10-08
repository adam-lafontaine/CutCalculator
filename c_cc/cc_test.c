#include <stdio.h>
#include <stdbool.h>
#include "./dot_h/sb_stringbuilder.h"
#include "./dot_h/cc_test.h"

void print(const char* msg) {
    printf("%s\n", msg);
}

// gcc -o run_tests cc_test.c sb_stringbuilder.c

int main(int argc, char **argv) {

    print(test_stringbuilder_create_destroy());
    
}

//===========================


char* test_stringbuilder_create_destroy() {
    char* success = "Pass";
    size_t size = 10;

    string_t* str = sb_create_empty(size);
    
    sb_destroy(str);

    return success;
}



