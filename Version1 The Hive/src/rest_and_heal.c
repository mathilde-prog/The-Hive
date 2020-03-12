#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "structure.h"

/* rest_and_heal: allows the player to rest and gain pv and pe (proportionate to his number of pa) */
void rest_and_heal(perso_t * player){
  int value = player->pa * 5;

  printf("Let's take some rest zzZZ\n"); sleep(1);
  player->pv += value;
  player->pe += value;
  printf("PV +%d\tPE +%d\n",value,value);
  sleep(2);
}
