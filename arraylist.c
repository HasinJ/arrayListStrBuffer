#include <stdlib.h>
#include <stdio.h>
#include "arraylist.h"

#ifndef DEBUG
#define DEBUG 0
#endif

int al_init(arraylist_t *L, size_t length){
    L->data = malloc(sizeof(int) * length);
    if (!L->data) return 1;

    L->length = length;
    L->used   = 0;

    return 0;
}

void al_destroy(arraylist_t *L){
    free(L->data);
}

int al_append(arraylist_t *L, int item){ //adds to the end
    if (L->used == L->length) {
    	size_t size = L->length * 2;
    	int *p = realloc(L->data, sizeof(int) * size);

    	if (!p) return 1;

    	L->data = p;
    	L->length = size;

    	if (DEBUG) printf("Increased size to %lu\n", size);
    }

    L->data[L->used] = item;
    ++L->used;

    return 0;
}


int al_remove(arraylist_t *L, int *item){
    if (L->used == 0) return 1;
    --L->used;
    if (item) *item = L->data[L->used];
    return 1;
}

int al_insert(arraylist_t *L, int index, int item){
  if (L->length<index){
    size_t new_length;
    if(L->length*2<index) new_length=index;
    else new_length=L->length;
    if (DEBUG) printf("new_length %ld\n", new_length);

    
  }
  return 1;
}
