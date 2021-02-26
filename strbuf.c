#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "strbuf.h"

#ifndef DEBUG
#define DEBUG 0
#endif

int sb_init(strbuf_t *L, size_t length){
  L->data = malloc(sizeof(char) * length+1);
  if (!L->data) return 1;

  L->length = length;
  L->used = 0;
  L->data[length]='\0';

  return 0;
}

void sb_destroy(strbuf_t *L){ free(L->data);}

int sb_append(strbuf_t *L, char item){ //adds to the end
  if (L->used == L->length) {
    size_t size = L->length * 2;
    char *p = realloc(L->data, sizeof(char) * size+1);

    if (!p) return 1;

    L->data = p;
    L->length = size;

    if (DEBUG) printf("Increased size to %lu\n", size);
  }

  L->data[L->used] = item;
  ++L->used;

  return 0;
}

int sb_remove(strbuf_t *L, char *item){
  return 0;
}


int sb_insert(strbuf_t *L, int index, char item){
  return 0;
}
