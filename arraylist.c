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
    L->used = 0;

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

//if it's full and add to the end
//if it's full and add to the beginning
//if it's full and add to the middle
//regular beginning, middle, and end
//empty beginning, middle, and end

int al_insert(arraylist_t *L, int index, int item){
  if (DEBUG) printf("item %d index %d \n", item, index);
  size_t new_length,i;
  if(L->length*2<=index) new_length=index+1;
  else new_length=L->length*2;

  if (index>L->length) {
    if (DEBUG) printf("no shift but realloc\n");
    int* data = malloc(sizeof(int) * new_length);
    if (!data) return 1;
    for (i = 0; i < L->used; i++) {
      data[i]=L->data[i];
    }
    al_destroy(L);
    L->data=data;
    L->used=new_length;
    L->length=new_length;
    L->data[index]=item;
    return 0;
  }

  else if (L->used<L->length && index>=L->used) {
    if (DEBUG) printf("no shift\n");
    int* data = malloc(sizeof(int) * L->length);
    for (i = 0; i < L->used; i++) {
      data[i]=L->data[i];
    }
    al_destroy(L);
    L->data=data;
    L->data[index]=item;
    ++L->used;
    if(index>L->used) L->used=index+1;
    return 0;
  }

  //shifting
  if (DEBUG) printf("shifting\n");
  if(L->used!=L->length && index<L->length) new_length=L->length;
  if (DEBUG) printf("new_length %ld\n", new_length);

  int* data = malloc(sizeof(int) * new_length);
  if (!data) return 1;

  for (i = 0; i < L->used; i++) {
    if(i>=index) data[i+1]=L->data[i];
    else data[i]=L->data[i];
  }

  if (DEBUG){
    printf("new data: \n");
    for (i = 0; i < new_length-1; ++i) printf("%d\n", data[i]);
    printf("\n");}

  data[index]=item;
  free(L->data);
  L->data=data;
  L->length=new_length;
  L->used++;
  if(index>L->used) L->used=index;
  //if (DEBUG) printf("L->data[0] %d\n", L->data[0]);

  return 0;
}
