#include <stdio.h>
#include <stdlib.h>
#include "arraylist.h"

int cmp(const void *a, const void *b){
    int x = *(int*)a;
    int y = *(int*)b;
    if (x < y) return -1;
    if (x == y) return 0;
    return 1;
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
    int i, item;
    arraylist_t A;
    al_init(&A, 2);

    while(fscanf(f,"%s %d",choice, &item)!=EOF){
    	//al_append(&A, d);
      if(choice[0]=='a') al_append(&A, item);
      if(choice[0]=='i') printf("%d\n", item);
      //printf("choice: %s, item: %d\n", choice, item);
    }

    qsort(A.data, A.used, sizeof(int), cmp);


    for (i = 0; i < A.used; ++i) {
    	printf("%d\n", A.data[i]);
    }

    al_destroy(&A);

    return EXIT_SUCCESS;
}
