#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void main(){
  int ap=0;
  int en=71;
  int base=0;
  int top=0;
  base=en/20;
  if((en%20)>=10){
    ap+=base+1;
    printf("%d will be added.\n", base+1);
  }else{
    printf("%d will be added.\n", base);
    ap+=base;
  }
}
