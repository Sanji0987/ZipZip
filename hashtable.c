#include "hashtable.h"
#include <string.h>

void hashdelete(hashtable* table){
  free(table->map);
  free(table);
}

void hashinit(hashtable **table, size_t size){
  (void)size;
  *table = (hashtable*)malloc(sizeof(hashtable));
  size_t table_size = 65536 * 2;
  (*table)->size = table_size;
  (*table)->map = (hashmap*)malloc(sizeof(hashmap) * table_size);
  memset((*table)->map, 0, sizeof(hashmap) * table_size);
}

uint32_t hashcalc(hashtable *table, uint16_t byte){
  uint32_t hash = (uint32_t)byte * 2654435761u;
  return hash % table->size;
}

// returns false if table is full and entry was lost
bool hashadd(hashtable* table, uint16_t byte){
  uint32_t i = hashcalc(table,byte);
  hashmap *map = table->map;
  size_t table_size = table->size;

  size_t checked = 0;
  while (checked < table_size) {
    if (map[i].occupied == false) {
      map[i].key = byte;
      map[i].freq = 1;
      map[i].occupied = true;
      return true;
    }
    else if (map[i].key == byte) {
      map[i].freq += 1;
      return true;
    }
    i = (i + 1) % table_size;
    checked++;
  }
  return false;
}

uint32_t hashgetfreq(hashtable *table, uint16_t byte){
  uint32_t i = hashcalc(table,byte);
  hashmap *map = table->map;
  size_t table_size = table->size;

  size_t checked = 0;
  while (checked < table_size) {
    if (map[i].occupied == false) {
      return 0;
    }
    if (map[i].key == byte) {
      return map[i].freq;
    }
    i = (i + 1) % table_size;
    checked++;
  }
  return 0;
}
