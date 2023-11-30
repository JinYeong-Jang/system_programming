#include "kvs.h"

void do_baseline_snapshot(kvs_t* kvs){

	FILE *fp = fopen("kvs.img", "a");
	node_t * current = kvs->db;
	for(int i =0; i<kvs->items; i++){
		char* key= current -> key;
		char* value= current -> value;
		fprintf(fp, "%s\n%s" , key , value);
    		current = current -> next;
	}
	fclose(fp);
}
////////////////
#include "kvs.h"
#include <errno.h>
 
int do_snapshot(kvs_t* kvs, const char* filename) {

	FILE* kvs_fp = fopen(filename, "w");
	if (!kvs_fp) {
		printf("Failed to open %s file: %s", filename, strerror(errno));
		return -1;
	}
 
	node_t* current = kvs->db;
	while (current != NULL) {
		fprintf(kvs_fp, "%s %s", current->key, current->value);
		current = current->next;
	}

	fclose(kvs_fp);
 
	return 0;
 }

