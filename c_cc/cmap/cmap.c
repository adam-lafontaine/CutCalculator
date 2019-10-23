#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "cmap.h"
#include "../struct/piece_combo.h"

//======= NODE ==============================

struct cmap_node_t;
typedef struct cmap_node_t ct_node;

cmap_pair* create_pair(const char* key, cc_value_type value) {

	cmap_pair* pair = piece_combo_create(key, value);
	if (pair == NULL)
		return NULL;

	return pair;
}

typedef struct cmap_node_t {
	size_t id;
	ct_node* child[CMAP_KEY_LENGTH];
	ct_node* parent;

	cmap_pair* pair;
} ct_node;


void clear_value(ct_node* node) {

	piece_combo_destroy(node->pair);
	node->pair = NULL;
}

void destroy_pair(cmap_pair* pair) {
	if (pair == NULL)
		return;

	piece_combo_destroy(pair);
}


ct_node* create_node(const size_t id) {
	ct_node* node = (ct_node*)malloc(sizeof(ct_node));

	if (node == NULL)
		return NULL;

	node->id = id;
	node->parent = NULL;
	node->pair = NULL;	

	size_t i = 0;
	while (i < CMAP_KEY_LENGTH)
		node->child[i++] = NULL;

	return node;
}

void destroy_node(ct_node* node) {
	if (node == NULL)
		return;

	for (size_t i = 0; i < CMAP_KEY_LENGTH; ++i) {
		if (node->child[i] != NULL) {
			destroy_node(node->child[i]);
			node->child[i] = NULL;
		}
	}

	if (node->pair != NULL) {
		destroy_pair(node->pair);
		node->pair = NULL;
	}
	
	node->parent = NULL;

	free(node);
}


bool is_empty_node(const ct_node* node) {
	if (node->pair != NULL)
		return false;

	for (size_t i = 0; i < CMAP_KEY_LENGTH; ++i) {
		if (node->child[i] != NULL)
			return false;
	}

	return true;
}

bool is_root_node(const ct_node* node) {
	return node->parent == NULL;
}


void add_child_node(ct_node* node, size_t index) {
	ct_node* child = create_node(index);
	child->parent = node;

	destroy_node(node->child[index]);		

	node->child[index] = child;
}

ct_node* lookup_node(const ct_node* node, const char* key) {
	ct_node* found = (ct_node*)node;

	char* c = (char*)key;

	while (*c != '\0') {
		size_t idx = c_idx(c++);
		if (found->child[idx] == NULL)
			return NULL;

		found = found->child[idx];
	}

	return found;
}

ct_node* next_child(ct_node* node) {

	if (node->pair != NULL)
		return node;

	for (size_t id = 0; id < CMAP_KEY_LENGTH; ++id) {
		if (node->child[id] != NULL)
			return next_child(node->child[id]);
	}

	return node;
}

ct_node* next_node(ct_node* node, size_t id) {
	if (id > CMAP_KEY_LENGTH - 1 || node == NULL)
		return NULL;

	for (; id < CMAP_KEY_LENGTH; ++id) {
		if (node->child[id] != NULL)
			return next_child(node->child[id]);
	}

	return next_node(node->parent, node->id + 1);
}

//======= HELPERS =================================

bool is_valid_char(const char c) {
	return strchr(KEY_CHARS, c) != NULL;
}


//======= PUBLIC ==================================

struct cmap_t {
	ct_node* root;
};


cmap* cmap_create() {
	cmap* map = (cmap*)malloc(sizeof(cmap));

	if (map == NULL)
		return NULL;

	map->root = create_node(0);
	if (map->root == NULL) {
		free(map);
		return NULL;
	}

	return map;
}


void cmap_destroy(cmap* map) {
	if (map->root == NULL)
		return;
	
	destroy_node(map->root);

	free(map);
}


void cmap_add(cmap* map, const char* key, const cmap_value_t value) {
	char* c = (char*)key;

	while (*c != '\0') {
		if (!is_valid_char(*c++))
			return;
	}

	ct_node* node = map->root;
	if (node == NULL || node->child == NULL)
		return;

	c = (char*)key;

	while (*c != '\0') {
		size_t idx = c_idx(c++);
		if (node->child[idx] == NULL)
			add_child_node(node, idx);

		node = node->child[idx];
	}

	if (node == NULL)
		return;

	cmap_pair* pair = create_pair(key, value);
	if (pair == NULL) {
		return;
	}	

	node->pair = pair;
}

void cmap_remove(cmap* map, const char* key) {
	ct_node* node = lookup_node(map->root, key);
	if (node == NULL)
		return;
	
	clear_value(node);
	
	// cleanup
	while (!is_root_node(node)) {
		size_t child_id = node->id;
		node = node->parent;

		if (is_empty_node(node->child[child_id])) {
			destroy_node(node->child[child_id]);
			node->child[child_id] = NULL;
		}			
	}
}

cmap_pair* cmap_get(cmap* map, const char* key) {
	ct_node* node = lookup_node(map->root, key);
	if (node == NULL)
		return NULL;

	return node->pair;
}

cmap_pair* cmap_get_next(cmap* map, const char* key) {
	ct_node* node = lookup_node(map->root, key);
	if (node == NULL)
		return NULL;

	ct_node* next = next_node(node, 0);
	if (next == NULL)
		return NULL;

	return next->pair;
}


cmap_pair* cmap_get_first(cmap* map) {
	ct_node* node = next_child(map->root);
	if (node == NULL)
		return NULL;

	return node->pair;
}