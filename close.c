#include "kvs.h"

int close(kvs_t* kvs)
{
	for(int i=0; i<kvs->items; i++)
	{
		node_t* temp = kvs -> db;
		kvs -> db = kvs -> db -> next;
		free(temp->value);
		free(temp);
	}
	free(kvs);
	return 0;
}
