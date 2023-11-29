#include "kvs.h"

int set(kvs_t* kvs, const char* key, const char* value) {
    node_t* new_node = (node_t*) malloc(sizeof(node_t));
    strcpy(new_node->key, key); 
    new_node->value = strdup(value); 
    
    new_node->next = kvs->db;
    kvs->db = new_node;
    kvs->items++;

    return 0;
}

