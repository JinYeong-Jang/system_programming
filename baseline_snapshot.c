#include "kvs.h"

void do_baseline_snapshot(kvs_t* kvs){
	clock_t start= clock();

	FILE *fp = fopen("kvs.img", "w");
	node_t * current = kvs->db;
	for(int i =0; i<kvs->items; i++){
		char* key= current -> key;
		char* value= current -> value;
		fprintf(fp, "%s\n%s\n" , key , value);
    		current = current -> next;
	}
	fclose(fp);
	clock_t end = clock();
	printf("baseline_snapshot() 함수 실행 시간: %lf 초\n", (double)(end-start) / CLOCKS_PER_SEC);
}

