#ifndef __CMAP_H__
#define __CMAP_H__

#include "cmap_config.h"
#include "../cc_types.h"

struct cmap_t;
typedef struct cmap_t cmap;

typedef piece_combo cmap_pair;


cmap* cmap_create();

void cmap_destroy(cmap* map);

void cmap_add(cmap* map, const char* key, const cmap_value_t value);

void cmap_remove(cmap* map, const char* key);

cmap_pair* cmap_get(cmap* map, const char* key);

cmap_pair* cmap_get_first(cmap* map);

cmap_pair* cmap_get_next(cmap* map, const char* key);



#endif // !__CMAP_H__

