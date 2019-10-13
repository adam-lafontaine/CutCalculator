#ifndef __SB_STRINGBUILDER_H__
#define __SB_STRINGBUILDER_H__

#include <stddef.h>

struct sb_string_tag;
typedef struct sb_string_tag string_t;


string_t* sb_create_empty(const size_t size);

void sb_destroy(string_t *sb);

//string_t* sb_create_fill(char *string);

//void sb_reserve(string_t *str, size_t size);

//void sb_clear(string_t *sb);




#endif