#include "kvs.h"
#define BUFFER_SIZE 5000

kvs_t* do_custom_recovery(kvs_t* kvs){
    int fd, retval, nbytes;
    int cnt =0;
    char buffer[BUFFER_SIZE];
    char* line_start = buffer;
    node_t* new_node = NULL;
    
    clock_t start = clock();
    if((fd=open("kvs.img",O_RDONLY)) > 0){
        while ((nbytes=read(fd, buffer , BUFFER_SIZE-1)) > 0){
       	    buffer[nbytes] = '\0';
       	    char *line_end;
       	    while((line_end = strchr(line_start, '\n')) != NULL){
       	         *line_end = '\0'; 	         
    		    if(cnt%2 ==0){
    		        new_node = (node_t*)malloc(sizeof(node_t));
    		        strncpy(new_node->key, line_start, sizeof(new_node -> key));
    		    }
    		    else{
    		        new_node->value = strdup(line_start);
    		        
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
    		    line_start=line_end +1;
    		    cnt++;
	    }
	    
	    int remaining = buffer + nbytes - line_start;
	    if(remaining >0)
	    	memmove(buffer, line_start, remaining);
	    line_start = buffer;
  	    
  
  	}
  	
  	if(nbytes <0){
  	    perror("read");
  	    exit(1);
  	
  	}
	if((retval = close(fd)) < 0){
		perror("close");
		exit(1);
	}
	clock_t end = clock();
	printf("custom_recovery() 함수 실행 시간: %lf 초\n", (double)(end-start) / CLOCKS_PER_SEC);
	return kvs;
    }
    else
    	return kvs;
}

   
