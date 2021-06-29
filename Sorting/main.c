#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<stack>

int main()
{
    stack c;

    clock_t t;
    t = clock();
    int i,j;
   //for(i=0;i<5;i++){
    //for(j=0;j<5;j++){
     //   printf("hello");
    //}

   printf("hello");
   t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("\nfun() took %f seconds to execute \n", time_taken);
    return 0;
}
