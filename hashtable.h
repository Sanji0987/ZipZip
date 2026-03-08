#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct hashmap{
  uint16_t key;
  uint32_t freq;
  bool occupied;
}hashmap;

typedef struct hashtable{
  hashmap *map;
  size_t size;
}hashtable;

void hashdelete(hashtable* table);
void hashinit(hashtable **table, size_t size);
uint32_t hashcalc (hashtable *table, uint16_t byte);
bool hashadd(hashtable* table, uint16_t byte);
uint32_t hashgetfreq(hashtable *table, uint16_t byte);

#endif
