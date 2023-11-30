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
int main()
{
	kvs_t* kvs = open();
	if(!kvs) {
		printf("Failed to open kvs\n");
		return -1;
	}
	FILE* inputFile = fopen("cluster004.trc","r");
	if(!inputFile){
		printf("Failed to open cluster004");
		close(kvs);
		return -1;}
	FILE* outputFile=fopen("kvs.img","w");
	if(!outputFile){
		printf("Failed to open kvs.img");
		fclose(inputFile);
		close(kvs);
		return -1;
	}

	char key [1024];
	char value [1024];
	while(1){
		int nread=fread(key,1,sizeof(key),inputFile);
		if(nread<sizeof(key)){
			break;
		}
		nread=fread(value,1,sizeof(value),inputFile);
         	if(nread <sizeof(value)){
			break;
		}
		fprintf(outputFile,"%s %s\n",key,value);
	}
	do_snapshot(kvs,"cluster004.trc");
	fclose(inputFile);
	fclose(outputFile);
	close(kvs);
	return 0;
}

