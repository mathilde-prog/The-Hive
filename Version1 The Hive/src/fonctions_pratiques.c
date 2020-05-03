#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/structure.h"

void entree_pour_continuer(){
  while(getchar() != '\n');
  printf("   >>> Appuyer sur la touche entrée pour continuer ");
  while(getchar() != '\n');
}

void clrscr(){ // fonction pour clear l'output de terminal
    system("clear");
}

int range(int a,int b){ // generates random number in range
  return (rand()%(b-a+1))+a;
}

int rng(int prob){ // returns 0 or 1 with a given chance
  return (rand()%100)<prob;
}
