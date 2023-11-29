#include "kvs.h"

void do_snapshot(FILE* fp, kvs_t* kvs){
	node_t * current = kvs->db;
	for(int i =0; i<kvs->items; i++){
		char* key= current -> key;
		char* value= current -> value;
		fprintf(fp, "%s\n%s" , key , value);
    		current = current -> next;
	}
}

