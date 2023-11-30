#include "kvs.h"

void do_custom_snapshot(kvs_t* kvs){
	int fd ,retval;
	const char newline = '\n';
	if((fd =open("kvs.img", O_RDWR | O_CREAT | O_APPEND ,0644)) < 0){
	    perror("open");
	    exit(1);
	}
	
	node_t * current = kvs->db;
	for(int i =0; i<kvs->items; i++){
	     if(write(fd, current ->key, strlen(current->key)) < 0){
		    perror("write");
		    break;
	     }
	     
	     if(write(fd, &newline, 1) < 0){
		    perror("write");
		    break;
	     }
	     
	     if(write(fd, current ->value, strlen(current->value)) < 0){
		     perror("write");
		     break;
	     }
	     /*
	     if(write(fd, &newline, 1) < 0){
		     perror("write");
		     break;
	     }
	     */
	     
    	     current = current -> next;
	}
	
	if((retval = close(fd)) < 0){
		perror("close");
		exit(1);
	}
}

