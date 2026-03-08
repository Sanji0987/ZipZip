#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "hashtable.h"

int main(int argc , char **argv){
  if (argc < 2){
    fprintf(stderr , "Pls enter a file name/location\n");
    return 1;
  }

  char *filename = argv[1];

  FILE* f = fopen(filename, "rb");
  if (f == NULL){
    fprintf(stderr,"Could not open file\n");
    return 1;
  }

  fseek(f,0,  SEEK_END);
  size_t size = ftell(f);
  fseek(f ,0 ,  SEEK_SET);
  printf("the size is:%zu\n", size);

  hashtable *table;
  hashinit(&table, size);

  void *buffer = (void*)malloc(size);
  fread(buffer, size, 1, f);
  uint16_t *ptr = (uint16_t*)buffer;

  void *compressed_buffer = (void*)malloc(size);


  for (size_t i = 0; i < size/2; i++) {
    printf("%u (0x%04X)\n",ptr[i], ptr[i]);
    hashadd(table,ptr[i]);
  }

  if (size % 2 != 0) {
    uint8_t *bptr = (uint8_t*)buffer;
    uint16_t last = bptr[size - 1];
    printf("%u (0x%04X)\n", last, last);
    hashadd(table, last);
  }

  for (size_t i = 0 ;  i < size/2 ; i++){
    uint32_t freq = hashgetfreq(table , ptr[i]);
    if (freq == 0){
      fprintf(stderr, "coudnt find a byte, recheck hashtable functions\n");
      return 1;
    }
  }



  free(compressed_buffer);
  hashdelete(table);
  free(buffer);
  fclose(f);
  return 0;
}
