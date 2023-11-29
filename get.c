#include "kvs.h"

char* get(kvs_t* kvs, const char* key)
{
    char* value = (char*)malloc(sizeof(char)*100);
    value = strdup("-1\n");
    node_t * current = kvs->db;
    if(!value)
    {
	printf("Failed to malloc\n");
	return NULL;
    }

    for(int i=0; i< kvs->items; i++)
    {
        if(!strcmp(current -> key,key))
        {   
        	strcpy(value, current -> value);
        	break;
        }
        current = current -> next;
    }
    return value;

}


