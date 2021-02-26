#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "strbuf.h"

#ifndef DEBUG
#define DEBUG 0
#endif

void removeNullTerminator(strbuf_t *L){
  if (DEBUG) printf("removing null term\n\n");
  size_t i;
  char* data = malloc(sizeof(char)*L->length);
  for (i = 0; i < L->used; i++){
    if(L->data[i]=='\0'){
      printf("exiting...\n");
      return;
    }
    data[i]=L->data[i];
  }

  free(L->data);
  L->data=data;
}


void specialRemoveNullTerminator(strbuf_t *L){
  if (DEBUG) printf("removing null term\n\n");
  size_t i;
  char* data = malloc(sizeof(char)*L->length+1);
  for (i = 0; i < L->used; i++){
    if(L->data[i]=='\0'){
      printf("exiting...\n");
      return;
    }
    data[i]=L->data[i];
  }

  free(L->data);
  L->data=data;
}

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
    removeNullTerminator(L);
    size_t size = L->length * 2;
    char *p = realloc(L->data, sizeof(char) * size+1);

    if (!p) return 1;

    L->data = p;
    L->length = size;

    if (DEBUG) printf("Increased size to %lu\n", size);
  }

  L->data[L->used] = item;
  L->data[L->used+1] = '\0';
  ++L->used;
  if (DEBUG) printf("\n");
  return 0;
}

int sb_remove(strbuf_t *L, char *item){
  size_t i;
  if (L->used == 0) return 1;
  --L->used;
  if (item) *item = L->data[L->used];

  char* data = malloc(sizeof(char) * L->length+1);
  for (i = 0; i < L->used; i++) {
    data[i]=L->data[i];
  }
  sb_destroy(L);

  L->data=data;
  L->data[L->used]='\0';
  return 1;
}

int sb_insert(strbuf_t *L, int index, char item){
  if (DEBUG) printf("item %c index %d \n", item, index);
  size_t new_length,i;
  if(L->length*2<=index) new_length=index+1;
  else new_length=L->length*2;


  if (index>=L->length) {
    if (DEBUG) printf("no shift but realloc new_length: %ld but... %ld\n", new_length, new_length+1);

    removeNullTerminator(L);
    char* data = realloc(L->data,sizeof(char) * new_length+1);

    L->used=index+1;
    L->data=data;
    L->data[index]=item;
    L->data[L->used]='\0';
    L->length=new_length;
    return 0;
  }

  if (index>=L->used && index<L->length) {
    if (DEBUG) printf("no realloc no shift\n");
    specialRemoveNullTerminator(L);
    L->data[index]=item;
    L->used=index+1;
    L->data[L->used]='\0';
    return 0;
  }

  if (DEBUG) printf("shifting\n");
  if(L->used!=L->length && index<L->length) new_length=L->length;
  if (DEBUG) printf("new_length %ld\n", new_length);

  char* data = malloc(sizeof(char) * new_length+1);
  if (!data) return 1;

  for (i = 0; i < L->used; i++) {
    if(i>=index) data[i+1]=L->data[i];
    else data[i]=L->data[i];
  }
  sb_destroy(L);
  L->data=data;
  L->data[++L->used]='\0';
  L->data[index]=item;
  L->length=new_length;





  return 0;
}
