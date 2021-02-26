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
  if (DEBUG) printf("item: %c\n",item);
  if (DEBUG) printf("appending\n");

  if (L->used == L->length) {
    ++L->used;

    char holder;
    sb_remove(L,&holder);
    if (DEBUG) printf("holder %d\n",holder);
    size_t size = L->length * 2;
    char *p = realloc(L->data, sizeof(char) * size+1);

    if (!p) return 1;

    L->data = p;
    L->length = size;
    L->data[size]='\0';

    if (DEBUG) printf("Increased size to %lu\n", size);
  }

  L->data[L->used] = item;
  ++L->used;
  if (DEBUG) printf("\n");
  return 0;
}

int sb_remove(strbuf_t *L, char *item){
  size_t i;
  if (L->used == 0) return 1;
  --L->used;
  if (item) *item = L->data[L->used];

  //printf("L->length: %ld L->used: %ld\n", L->length, L->used);
  char* data = malloc(sizeof(char) * L->length+1);
  for (i = 0; i < L->used; i++) {
    data[i]=L->data[i];
  }
  sb_destroy(L);

  if (data[L->length]!='\0') data[L->length]='\0';
  L->data=data;
  //printf("%c\n", data[0]);
  return 1;
}

int sb_insert(strbuf_t *L, int index, char item){
  return 0;
}
