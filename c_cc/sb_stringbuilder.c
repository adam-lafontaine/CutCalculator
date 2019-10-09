#include <stdlib.h>
#include "./dot_h/sb_stringbuilder.h"

#include <stdio.h>

struct sb_string_tag {
    char *value;
    size_t capacity;
    size_t size;
};

string_t *sb_create_empty(const size_t size) {
    string_t* str = (string_t *)malloc(sizeof(string_t));

    if(str != NULL) {        
        str->capacity = size;
        str->size = 0;
        ++sb_ref_count;
        str->value = (char *)calloc(size + 1, sizeof(char));
        if(str->value != NULL) {
            str->value[0] = '\0';
        }
    }

    return str;
}

void sb_destroy(string_t *str) {
    if(!str)
        return;

    free(str->value);
    free(str);
    --sb_ref_count;
}