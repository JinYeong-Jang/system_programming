 #include "kvs.h"
 
 int do_recovery(kvs_t* kvs) {
     // Open the input file
     FILE* fp = fopen("kvs.img", "rb");
     if (fp == NULL) {
         return -1;
     }
     // Create a new database
     kvs_t* new_kvs = open();
     if (new_kvs == NULL) {
         return -1;
     }
     // Read the database from the file
     char key[100];
     char value[100];
     while (fread(key, sizeof(key), 1, fp) == 1) {
         fread(value, sizeof(value), 1, fp);
         set(new_kvs, key, value);
     }
     fclose(fp);
     close(kvs);
     kvs = new_kvs;
     return 0;
 }
