#include "kvs.h"
#include <stdio.h>

kvs_t* do_recovery(kvs_t* kvs){
    char key[100];
    char value[5000];
    
    FILE* fp =fopen("kvs.img","r");
    if(fp)
    {
    	while (fgets(key, sizeof(key), fp) != NULL) {
    		node_t* new_node = (node_t*)malloc(sizeof(node_t));	
    		key[strcspn(key, "\n")] = 0;
    		
    		fgets(value, sizeof(value), fp);
		strncpy(new_node->key, key, sizeof(new_node -> key));
		new_node->value = strdup(value);
		
		if(kvs->db == NULL)
			kvs->db = new_node;
		else{
			node_t* current = kvs->db;
			while(current->next != NULL){
				current = current->next;	
			}
			current->next = new_node;
		}
		kvs->items++;
	}
	fclose(fp);
	return kvs;
    }
    else
    	return kvs;
}

   
