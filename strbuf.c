#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "strbuf.h"

#ifndef DEBUG
#define DEBUG 0
#endif

int sb_init(strbuf_t *L, size_t length){
  L->data = malloc(sizeof(char) * length);
  if (!L->data) return 1;

  L->length = length;
  L->used = 0;

  return 0;
}

void sb_destroy(strbuf_t *L){ free(L->data);}

int sb_append(strbuf_t *L, int item){ //adds to the end

  if (L->length-L->used<strlen(item)) {
    size_t size;
    size = L->length * 2;
    if(size<strlen(item)) size=strlen(item);
    char *p = realloc(L->data, sizeof(char) * size+1);

    if (!p) return 1;

    p[size]='\0';
    L->data = p;
    L->length = size;

    if (DEBUG) printf("Increased size to %lu\n", size);
  }

  size_t i,j=0;
  if (DEBUG) printf("strlen(item): %ld\n", strlen(item));

  for (i=L->used; i<strlen(item); i++) {
    L->data[i]=item[j++];
  }

  L->used+=strlen(item);

  return 0;
}

int sb_remove(strbuf_t *L, char *item){
  return 0;
}


int sb_insert(strbuf_t *L, int index, char item){
  return 0;
}
