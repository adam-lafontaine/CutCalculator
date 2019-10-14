#ifndef __CMAP_CONFIG_H__
#define __CMAP_CONFIG_H__

// include desired character options for string keys
static const char KEY_CHARS[] = "abcdefghijklmnopqrstuvwxyz";

// define value type at implementation
// e.g. typedef int cmap_value_t

// define if value type is a pointer to enable proper memory cleanup
//#define CMAP_VALUE_IS_PTR

// do not touch
#define CMAP_KEY_LENGTH sizeof KEY_CHARS - 1


// defines how a character is mapped to an array index
// implementation in cmap_config.c
size_t c_idx(char* c);

#endif // !__CMAP_CONFIG_H__
