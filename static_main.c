#include "kvs.h"

int main(){
	char buffer[5000];
	char * token;
	char * arr[3];

        kvs_t* kvs = open();
	if(!kvs) {
		printf("Failed to open kvs\n");
		return -1;
	}
	
	FILE *fp1 = fopen("cluster004.trc", "r");
	FILE *fp2 = fopen("kvs.img", "a");
	if (!fp1 || !fp2 ){
		printf("Failed to open file\n");
		return -1;
	}
			
	while(fgets(buffer, sizeof(buffer), fp1) != NULL) {
		token = strtok(buffer,",");
		for(int i=0; i<3; i++){
			arr[i]=token;
			token = strtok(NULL,",");
		}
		set(kvs, arr[1], arr[2]);
	}
	
	do_snapshot(fp2,kvs);
	
	fclose(fp1);
	fclose(fp2);
	close(kvs);
	return 0;
}


