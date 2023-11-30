#include "kvs.h"
#include <stdio.h>

kvs_t* do_custom_recovery(kvs_t* kvs){
    int fd, retval;
    int index=0 , cnt =0;
    char buffer[5000];  
    node_t* new_node = NULL;
    if((fd=open("kvs.img",O_RDONLY)) > 0){
        while (read(fd, &buffer[index] , 1) > 0){
    	    if(buffer[index] == '\n'){   	         
    		    if(cnt%2 ==0){
    		    	buffer[index] ='\0';
    		        new_node = (node_t*)malloc(sizeof(node_t));
    		        strncpy(new_node->key, buffer, sizeof(new_node -> key));
    		    }
    		    else{
    		        new_node->value = strdup(buffer);
    		        
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
    		    memset(buffer,0,index);
    		    index=0;
    		    cnt++;
	    }
  	    else
  	    	index++;
  	}
	if((retval = close(fd)) < 0){
		perror("close");
		exit(1);
	}
	return kvs;
    }
    else
    	return kvs;
}

   
