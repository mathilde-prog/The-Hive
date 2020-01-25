#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void main(){
  int t=4,c=0;

  c= t==1?1:t==2?2:t==3?3:t==4?4:0;
  printf("\n%d\n", c);
}
