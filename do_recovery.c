#include "kvs.h"

int do_recovery(kvs_t* kvs , FILE* fp){
    char key[100];
    char value[5000];
    node_t *last_node = NULL;

    while (fgets(key, sizeof(key), fp) != NULL) {
    	node_t* new_node = (node_t*)malloc(sizeof(node_t));
        key[strcspn(key, "\n")] = 0;
        fgets(value, sizeof(value), fp);
        strncpy(new_node->key, key, sizeof(new_node -> key));
	new_node->value = strdup(value);
        new_node->next = NULL;

        if (last_node == NULL)
            kvs->db = new_node; 
        else
            last_node->next = new_node;
        last_node = new_node; 
        kvs->items++;
        }
	return 0;
}

   
