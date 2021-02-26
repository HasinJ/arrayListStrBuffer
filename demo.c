#include <stdio.h>
#include <stdlib.h>
#include "strbuf.h"

int cmp(const void *a, const void *b){
    int x = *(int*)a;
    int y = *(int*)b;
    if (x < y) return -1;
    if (x == y) return 0;
    return 1;
}

void test(strbuf_t *L, char* item){
  L->data[0]=item[0];
  L->data[1]='\0';

  printf("test: %c\n", item[0]);

  printf("test should be same: %s\n", L->data);

}

int main(int argc, char **argv){
    if (argc>2 || argc==1) {
      printf("Please enter 1 file name.\n");
      return EXIT_SUCCESS;
    }

    FILE *f;
    f = fopen(argv[1],"r");
    if (f==0) {
      printf("error\n");
      return EXIT_SUCCESS;
    }

    char choice[2];
    char item;
    int index;
    size_t i;
    strbuf_t S;
    sb_init(&S, 2);

    //sb_append(&S,'c');

    while(fscanf(f,"%s %c",choice, &item)!=EOF){
      if(choice[0]=='a') sb_append(&S, item);
      if(choice[0]=='r'){
        printf("removing\n");
        sb_remove(&S, &item);
      }
      if(choice[0]=='i') {
        fscanf(f,"%d",&index);
        sb_insert(&S, index, item);
      }
    }
    //qsort(S.data, S.used, sizeof(int), cmp);
    printf("\nfinal: \n");

    for (i = 0; i < S.used; ++i) {
      printf("%d ", S.data[i]);
      printf("\n");
    }
    printf("\n");


    printf("\nhidden stuff: \n");

    for (i = S.used; i<S.length; i++) {
      printf("%d ", S.data[i]);
      printf("\n");
    }
    printf("last used: %d\n",S.data[S.used-1]);

    for (i = 0; i < S.length+1; ++i) {
      if (S.data[i]=='\0'){
        printf("null terminator found at %ld\n",i);
      }
    }

    //printf("%s ", &S.data[0]);
    printf("\nData Printed: %s\n\n", S.data);

    printf("S.used %ld\n", S.used);
    printf("S.length %ld\n", S.length);
    //printf("S.data[0] %d\n", S.data[0]);
    sb_destroy(&S);

    return EXIT_SUCCESS;
}
