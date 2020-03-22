#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"

#define RND_RANGE 1000

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int n = atoi(argv[1]);

    list *a = NULL, *b = NULL;

    // insert nodes with the given n
    for (int i = 0; i < n; i++) {
        int tmp = rand() % RND_RANGE;
        insert_node(&a, tmp);
        insert_node(&b, tmp);
    }

    struct timespec start, end;
    FILE *fp = fopen("experiment", "a");

    printf("the original list:\n");
    print_list(a);


    printf("the sorted list:\n");
    
    clock_gettime(CLOCK_REALTIME, &start);
    a = sort(a);
    clock_gettime(CLOCK_REALTIME, &end);
    
    print_list(a);
    fprintf(fp, "%lu ", end.tv_nsec - start.tv_nsec);

    clock_gettime(CLOCK_REALTIME, &start);
    b = sort_list(b);
    clock_gettime(CLOCK_REALTIME, &end);
    
    print_list(b);
    fprintf(fp, "%lu\n", end.tv_nsec - start.tv_nsec);

    delete_list(a);
    delete_list(b);
    fclose(fp);
    return 0;
}
