#include <stdio.h>
#include "assert.h"
#include <unistd.h>

#define NZ 3
#pragma omp declare target
int colstat[NZ]={1,2,3};
#pragma omp end declare target

int main(){
#pragma omp target map(alloc:colstat[0:NZ])
  {
    colstat[1] = 1111;
  }
fprintf(stderr, "BEFORE colstat[0..2] %d %d %d \n", colstat[0], colstat[1], colstat[2]);
#pragma omp target update from(colstat)
  fprintf(stderr, "AFTER colstat[0..2] %d %d %d \n", colstat[0], colstat[1], colstat[2]);
  return (colstat[0] == 1 && colstat[1] == 1111 && colstat[2] == 2) ? 0 : 1 ;
}

