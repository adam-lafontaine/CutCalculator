#include <stdio.h>
#include <stdbool.h>
#include "./dot_h/sb_stringbuilder.h"
#include "./dot_h/cc_test.h"

void print(const char* msg) {
    printf("%s\n", msg);
}

// gcc -o run_tests cc_test.c sb_stringbuilder.c

int main(int argc, char **argv) {
    char buffer[100];

    test_stringbuilder_create_destroy(buffer, 100);
    print(buffer);
    
}

//===========================


void test_stringbuilder_create_destroy(char* buffer, size_t max_size) {

    if(max_size < 50) {
        return;
    }

    size_t size = 10;

    unsigned count_before = sb_ref_count;

    string_t* str = sb_create_empty(size);

    unsigned count_created = sb_ref_count;
    
    sb_destroy(str);

    unsigned count_after = sb_ref_count;    
        

    if(count_before != 0)
        sprintf(buffer, "Fail - ref count before create != 0 (%u)", sb_ref_count);

    if(count_created != 1)
        sprintf(buffer, "Fail - ref count after create != 1 (%u)", sb_ref_count);

    if(count_after != 0)
        sprintf(buffer, "Fail - ref count after destroy != 0 (%u)", sb_ref_count);

    sprintf(buffer, "Pass");
}



